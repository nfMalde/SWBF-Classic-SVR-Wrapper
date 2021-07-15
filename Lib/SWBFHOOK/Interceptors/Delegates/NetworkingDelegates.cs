using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors.Delegates
{
    public static class NetworkingDelegates
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool SendP2PPacketDelegate(IntPtr galaxyId, IntPtr data, IntPtr dataSize, IntPtr sendType, IntPtr channel);
        
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool IsP2PPacketAvailableDelegate(IntPtr msgSize, IntPtr channel);
    }
}
