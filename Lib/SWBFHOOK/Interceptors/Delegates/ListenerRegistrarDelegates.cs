using SWBFHOOK.Interceptors.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Interceptors.Delegates
{
    public class ListenerRegistrarDelegates
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool RegisterDelegate(IntPtr listenerType, IntPtr listener);

    }
}
