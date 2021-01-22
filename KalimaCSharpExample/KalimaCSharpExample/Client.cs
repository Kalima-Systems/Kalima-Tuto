using System;
using org.kalima.kalimamq.nodelib;
using org.kalima.kalimamq.message;
using org.kalima.kalimamq.crypto;
using org.kalima.util;
using org.kalima.cache.lib;
using ikvm.extensions;

namespace KalimaCSharpExample
{
    public class Client : KalimaNode
    {

        private Node node;
        private Clone clone;
        private Logger logger;
        private KalimaServerCallBack kalimaServerCallback;
        private KalimaClientCallBack kalimaClientCallback;
        private ClonePreferences clonePreferences;
        private byte[] devId;

        public static void Main(string[] args)
        {
            try
            {
                Client client = new Client(args);
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }

        public Client(string[] args)
        {
            clonePreferences = new ClonePreferences(args[0]);
            logger = clonePreferences.getLoadConfig().getLogger();
            initComponents();
            System.Threading.Thread.Sleep(2000);

            // Ici on envoit 10 messages "hello x" dans le channel "/sensors" avec l'id unique "key"
            // Comme l'id unique reste le meme, "hello 1" sera ecrase par "hello2" et ainsi de suite
            // Cependant toutes les valeurs persisteront dans l'historique
            // new KProps("10") place le ttl (time to live) a 10 seconde. ce qui signifie que le message sera supprimé dans 10 secondes
            for (int i = 0; i < 10; i++)
            {
                String body = "hello" + i;
                KMsg kMsg = new KMsg(0);
                node.sendToNotaryNodes(kMsg.getMessage(devId, KMessage.PUB, "/sensors", "key" + i, body.getBytes(), new KProps("10")));
                System.Threading.Thread.Sleep(1000);
            }
        }

        public void initComponents()
        {
            byte[] key = new byte[] {
                (byte)0x20, (byte)0xf7, (byte)0xdf, (byte)0xe7,
                (byte)0x18, (byte)0x26, (byte)0x0b, (byte)0x85,
                (byte)0xff, (byte)0xc0, (byte)0x9d, (byte)0x54,
                (byte)0x28, (byte)0xff, (byte)0x10, (byte)0xe9
            };

            devId = KKeyStore.setDevId(clonePreferences.getLoadConfig(), key, logger);

            node = new Node(clonePreferences.getLoadConfig());
            node.setDevID(devId);
            clone = new Clone(clonePreferences, node);

            kalimaServerCallback = new KalimaServerCallBack();
            kalimaClientCallback = new KalimaClientCallBack(this);

            node.connect(kalimaServerCallback, kalimaClientCallback);
        }

        public Node getNode()
        {
            return node;
        }

        public Logger getLogger()
        {
            return logger;
        }

        public Clone getClone()
        {
            return clone;
        }

    }
}
