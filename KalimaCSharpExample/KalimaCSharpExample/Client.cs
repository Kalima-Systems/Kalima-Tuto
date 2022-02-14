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
                Console.Write("\nEnd of the console program...");
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
            ConsoleKeyInfo pressedKeyLeftExample = new ConsoleKeyInfo();
            string cachepath = "";
            // Global loop for the example
            do
            {
                ConsoleKeyInfo pressedKeyAskCachePathChoice = new ConsoleKeyInfo();
                ConsoleKeyInfo pressedKeyStayInCachePathChoice = new ConsoleKeyInfo();

                // Verify if this is the first loop in the example
                //Then if this is not the first ask if the user want to stay in the same cache path
                if (pressedKeyLeftExample.KeyChar == '\r')
                {
                    do
                    {
                        Console.WriteLine("\nDo you want to stay in the same cache path? y/n");
                        pressedKeyStayInCachePathChoice = Console.ReadKey();
                    } while (pressedKeyStayInCachePathChoice.KeyChar != 'Y' && pressedKeyStayInCachePathChoice.KeyChar != 'y' && pressedKeyStayInCachePathChoice.KeyChar != 'N' && pressedKeyStayInCachePathChoice.KeyChar != 'n');
                }
                if (pressedKeyStayInCachePathChoice.KeyChar != 'Y' && pressedKeyStayInCachePathChoice.KeyChar != 'y')
                {
                    Console.WriteLine("\nChoose a cache path");
                    cachepath = Console.ReadLine();
                }
                //Now the user will say if he wants to add or delete a data
                do
                {
                    Console.WriteLine("\nPress 'A' to add something to the cache path and 'D' to delete");
                    pressedKeyAskCachePathChoice = Console.ReadKey();
                } while (pressedKeyAskCachePathChoice.KeyChar != 'A' && pressedKeyAskCachePathChoice.KeyChar != 'a' && pressedKeyAskCachePathChoice.KeyChar != 'D' && pressedKeyAskCachePathChoice.KeyChar != 'd');

                string key = "";
                string body = "";
                do
                {
                    if (pressedKeyAskCachePathChoice.KeyChar == 'A' || pressedKeyAskCachePathChoice.KeyChar == 'a')
                    {
                        Console.WriteLine("\nEnter the key of the data you want to add");
                        key = Console.ReadLine();
                        Console.WriteLine("\nEnter the value of your data");
                        body = Console.ReadLine();
                    }
                    else if (pressedKeyAskCachePathChoice.KeyChar == 'D' || pressedKeyAskCachePathChoice.KeyChar == 'd')
                    {
                        Console.WriteLine("\nEnter the key of the data you want to delete");
                        key = Console.ReadLine();
                    }
                } while (key == "");

                //Send message to the blockchain with the cache path 
                KMsg kMsg = new KMsg(0);
                node.sendToNotaryNodes(kMsg.getMessage(node.getDevID(), KMessage.PUB, cachepath, key, body.getBytes(), new KProps("")));
                System.Threading.Thread.Sleep(1000);

                Console.WriteLine("\nPress ENTER to continue or 'E' to exit");
                pressedKeyLeftExample = Console.ReadKey();
            } while (pressedKeyLeftExample.KeyChar != 'e' && pressedKeyLeftExample.KeyChar != 'E');

            // Here we make 10 transactions with body "hello x" in cache path "/sensors", with key "keyx"
            // new KProps("10") set the ttl (time to live) to 10 seconds. So, the record will be automatically deleted in memCaches after 10 second
            // But of course, all transactions are still present in blockchain
            /*
                        for (int i = 0; i < 10; i++)
                        {
                            String body = "hello" + i;
                            KMsg kMsg = new KMsg(0);
                            node.sendToNotaryNodes(kMsg.getMessage(node.getDevID(), KMessage.PUB, "/sensors", "key" + i, body.getBytes(), new KProps("10")));
                            System.Threading.Thread.Sleep(1000);
                        }
            */
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
