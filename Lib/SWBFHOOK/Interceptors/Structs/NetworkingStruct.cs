using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors.Structs
{
    [StructLayout(LayoutKind.Sequential)]
    public struct NetworkingStruct
    {
        public IntPtr SendP2PPacket;

        public IntPtr PeekP2PPacket;

        public IntPtr IsP2PPacketAvailable;

        public IntPtr ReadP2PPacket;

        public IntPtr PopP2PPacket;

        public IntPtr GetPingWith; 
    }
}
