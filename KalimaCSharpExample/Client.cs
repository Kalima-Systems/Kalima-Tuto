using System;
using org.kalima.kalimamq.nodelib;
using org.kalima.kalimamq.message;
using org.kalima.util;
using org.kalima.cache.lib;
using ikvm.extensions;
using System.Text;

namespace KalimaCSharpExample
{
    public class Client
    {
        private Clone clone;
        private Logger logger;
        public static String USERNAME = "...";

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
            ClonePreferences clonePreferences = new ClonePreferences(args[0]);
            logger = clonePreferences.getLoadConfig().getLogger();
            clone = new Clone(clonePreferences);
            KalimaClientCallBack kalimaClientCallback = new KalimaClientCallBack(this);
            clone.connect(kalimaClientCallback);

            Boolean stop = false;
            while (!stop)
            {
                menu();
                ConsoleKey choice = Console.ReadKey().Key;
                Console.WriteLine();
                switch (choice)
                {
                    case ConsoleKey.NumPad1:
                    case ConsoleKey.D1:
                        printAddresses();
                        break;

                    case ConsoleKey.NumPad2:
                    case ConsoleKey.D2:
                        Console.WriteLine("Enter address:");
                        printContentOfAddress(Console.ReadLine());
                        break;

                    case ConsoleKey.NumPad3:
                    case ConsoleKey.D3:
                        printContentOfAllAddresses();
                        break;

                    case ConsoleKey.NumPad4:
                    case ConsoleKey.D4:
                        Console.WriteLine("Enter tempareture (int):");
                        String temperatureStr = Console.ReadLine();
                        try
                        {
                            putTemperature((int)Int64.Parse(temperatureStr));
                        }
                        catch (Exception)
                        {
                            Console.WriteLine("You must enter an integer");
                        }
                        break;

                    case ConsoleKey.NumPad5:
                    case ConsoleKey.D5:
                        stop = true;
                        break;
                }
            }
            Environment.Exit(0);
        }

        public Logger getLogger()
        {
            return logger;
        }

        public Clone getClone()
        {
            return clone;
        }

        private void menu()
        {
            Console.WriteLine("1- print all addresses");
            Console.WriteLine("2- print content of address");
            Console.WriteLine("3- print content of all addresses");
            Console.WriteLine("4- put a temperature");
            Console.WriteLine("5- close");
        }

        private void printAddresses()
        {
            foreach (String addr in clone.getAddresses())
            {
                Console.WriteLine(addr);
            }
        }

        private void printContentOfAddress(String address)
        {
            MemCache memCache = (MemCache)clone.getMemCache(address);
            if(memCache == null)
            {
                Console.WriteLine("Address " + address + " not found");
                return;
            }

            memCache.navigate(new PrintKmsg());
        }

        private void printContentOfAllAddresses()
        {
            foreach(String addr in clone.getAddresses())
            {
                Console.WriteLine("*** " + addr + " ***");
                printContentOfAddress(addr);
                Console.WriteLine(addr);
            }
        }

        private void putTemperature(int temperature)
        { 
            clone.put("/" + Client.USERNAME + "/addr1", "temperature", Encoding.ASCII.GetBytes(temperature.toString()));
        }

        public class PrintKmsg : MemCache.NextKMsg
        {
            public void invoke(KMsg kmsg)
            {
                Console.WriteLine("KEY=" + kmsg.getKey() + " BODY=" + System.Text.Encoding.Default.GetString(kmsg.getBody()));
            }
        }
    }
}
