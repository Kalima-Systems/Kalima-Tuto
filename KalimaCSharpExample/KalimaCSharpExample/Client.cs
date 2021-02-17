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

            // Here we make 10 transactions with body "hello x" in cache path "/sensors", with the unique ID "key"
            // Because the id is the same for all transactions, "hello 1" will be replaced by "hello 2", then by "hello 3", etc, in memCaches
            // but all transactions are still present in blockchain
            // new KProps("10") set the ttl (time to live) to 10 seconds. So, the record will be automatically deleted in memCaches after 10 seconds
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
