using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using org.kalima.kalimamq.message;
using org.kalima.kalimamq.nodelib;
using org.kalima.cache.lib;


namespace KalimaCSharpExample
{
    class AlarmsCallback : MemCacheCallback
    {

        private String address;

        public AlarmsCallback(String address)
        {
            this.address = address;
        }
        public string getAddress()
        {
            return address;
        }

        public void putData(string key, KMessage kMessage)
        {
            KMsg kMsg = KMsg.setMessage(kMessage);
            Console.WriteLine("new alarm key=" + key + " body=" + System.Text.Encoding.Default.GetString(kMsg.getBody()));
        }

        public void removeData(string str)
        {
           
        }
    }
}
