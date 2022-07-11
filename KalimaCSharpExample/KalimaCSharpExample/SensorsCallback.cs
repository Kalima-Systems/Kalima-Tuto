using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using org.kalima.kalimamq.nodelib;
using org.kalima.cache.lib;
using org.kalima.kalimamq.message;

namespace KalimaCSharpExample
{
    class SensorsCallback : MemCacheCallback
    {

        private String address;
        private Clone clone;

        public SensorsCallback(String address, Clone clone)
        {
            this.address = address;
            this.clone = clone;
        }
        public string getAddress()
        {
            return address;
        }

        public void putData(KMessage kMessage)
        {
            KMsg msg = KMsg.setMessage(kMessage);
            String key = msg.getKey();
            String body = System.Text.Encoding.Default.GetString(msg.getBody());
            Console.WriteLine("new sensor value key=" + key + " body=" + body);
            if(key.Equals("temperature"))
            {
                int temperature = (int) Int64.Parse(body);
                if(temperature >= 100)
                {
                    clone.put("/alarms/fire", "temperature", Encoding.ASCII.GetBytes("Temperature too high: " + temperature + " °C"));
                }
            }
        }

        public void removeData(KMessage kMessage)
        {
            
        }
    }
}
