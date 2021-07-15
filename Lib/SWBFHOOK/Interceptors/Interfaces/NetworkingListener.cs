using SWBFHOOK.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors.Interfaces
{
    public  class NetworkingListener
    {
        private ServerInterface server;

        public NetworkingListener(string channel)
        {
            //this.server = EasyHook.RemoteHooking.IpcConnectClient<ServerInterface>(channel);
        }

        public void OnP2PPacketAvailable(UInt32 msgSize, byte channel)
        {
           // this.server.ReportMessage($"Package Available: {msgSize}, {channel}");
        }


    }
}
