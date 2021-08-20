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
        private KalimaClientCallBack kalimaClientCallback;
        private ClonePreferences clonePreferences;

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
            Console.WriteLine("GO");

            // Here we make 10 transactions with body "hello x" in cache path "/sensors", with key "keyx"
            // new KProps("10") set the ttl (time to live) to 10 seconds. So, the record will be automatically deleted in memCaches after 10 second
            // But of course, all transactions are still present in blockchain
            for (int i = 0; i < 10; i++)
            {
                String body = "hello" + i;
                KMsg kMsg = new KMsg(0);
                node.sendToNotaryNodes(kMsg.getMessage(node.getDevID(), KMessage.PUB, "/sensors", "key" + i, body.getBytes(), new KProps("10")));
                System.Threading.Thread.Sleep(1000);
            }
        }

        public void initComponents()
        {
            node = new Node(clonePreferences.getLoadConfig());
            clone = new Clone(clonePreferences, node);

            kalimaClientCallback = new KalimaClientCallBack(this);

            node.connect(null, kalimaClientCallback);
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
