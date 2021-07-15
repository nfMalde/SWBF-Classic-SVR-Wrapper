using SWBFHOOK.Server;
using SWBFHOOK.Interceptors.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors
{
    class NetworkingInterceptor: INetworking
    {
        private readonly INetworking originalNetwork;
        private ServerInterface server;

        public NetworkingInterceptor(INetworking originalNetwork, string ipcChannel)
        {
            this.server = EasyHook.RemoteHooking.IpcConnectClient<ServerInterface>(ipcChannel);
            this.originalNetwork = originalNetwork;
        }

        public object GetConnectionType(object userID)
        {
            return this.originalNetwork.GetConnectionType(userID);
        }

        public object GetNatType()
        {
           return this.originalNetwork.GetNatType();
        }

        public int GetPingWith(object galaxyID)
        {
            return this.originalNetwork.GetPingWith(galaxyID);
        }

        public bool IsP2PPacketAvailable(uint outMsgSize, byte channel = 0)
        {
            return this.originalNetwork.IsP2PPacketAvailable(outMsgSize, channel);
        }

        public bool PeekP2PPacket(object dest, uint destSize, uint outMsgSize, object outGalaxyID, byte channel = 0)
        {
            return this.originalNetwork.IsP2PPacketAvailable(outMsgSize, channel);
        }

        public void PopP2PPacket(byte channel = 0)
        {
             this.originalNetwork.IsP2PPacketAvailable(channel);

        }

        public bool ReadP2PPacket(object dest, uint destSize, uint outMsgSize, object outGalaxyID, byte channel = 0)
        {
            return this.originalNetwork.ReadP2PPacket(dest,destSize, outMsgSize,outGalaxyID,channel);
        }

        public void RequestNatTypeDetection()
        {
            this.originalNetwork.RequestNatTypeDetection();
        }

        public bool SendP2PPacket(object galaxyID, object data, uint dataSize, object sendType, byte channel = 0)
        {
            return this.originalNetwork.SendP2PPacket(galaxyID, data, dataSize, sendType, channel);
        }
    }
}
