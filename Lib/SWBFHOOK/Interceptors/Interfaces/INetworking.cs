using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors.Interfaces
{
    public interface INetworking
    {
        bool SendP2PPacket(object galaxyID, object data, UInt32 dataSize, object sendType, byte channel = 0);

        bool PeekP2PPacket(object dest, UInt32 destSize, UInt32 outMsgSize, object outGalaxyID, byte channel = 0);

        bool IsP2PPacketAvailable(UInt32 outMsgSize, byte channel = 0);

        bool ReadP2PPacket(object dest, UInt32 destSize, UInt32 outMsgSize, object outGalaxyID, byte channel = 0);

        void PopP2PPacket(byte channel = 0);

        int GetPingWith(object galaxyID);

        void RequestNatTypeDetection();

        object GetNatType();

        object GetConnectionType(object userID);
    }
}
