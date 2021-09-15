using EasyHook;
using SWBFHOOK.Server;
using SWBFHOOK.Helper;
using SWBFHOOK.Interceptors;
using SWBFHOOK.Interceptors.Interfaces;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using static SWBFHOOK.Interceptors.Delegates.NetworkingDelegates;
using static SWBFHOOK.Interceptors.Delegates.ListenerRegistrarDelegates;

namespace SWBFHOOK
{
    public class InjectionEntryPoint: EasyHook.IEntryPoint
    {
        /// <summary>
        /// Reference to the server interface within FileMonitor
        /// </summary>
        ServerInterface _server = null;

        /// <summary>
        /// Message queue of all files accessed
        /// </summary>
        Queue<string> _messageQueue = new Queue<string>();

        private string channelName = null;

        /// <summary>
        /// EasyHook requires a constructor that matches <paramref name="context"/> and any additional parameters as provided
        /// in the original call to <see cref="EasyHook.RemoteHooking.Inject(int, EasyHook.InjectionOptions, string, string, object[])"/>.
        /// 
        /// Multiple constructors can exist on the same <see cref="EasyHook.IEntryPoint"/>, providing that each one has a corresponding Run method (e.g. <see cref="Run(EasyHook.RemoteHooking.IContext, string)"/>).
        /// </summary>
        /// <param name="context">The RemoteHooking context</param>
        /// <param name="channelName">The name of the IPC channel</param>
        public InjectionEntryPoint(
            EasyHook.RemoteHooking.IContext context,
            string channelName)
        {
            this.channelName = channelName;
            // Connect to server object using provided channel name
            _server = EasyHook.RemoteHooking.IpcConnectClient<ServerInterface>(channelName);

            // If Ping fails then the Run method will be not be called
            _server.Ping();
        }




        /// <summary>
        /// The main entry point for our logic once injected within the target process. 
        /// This is where the hooks will be created, and a loop will be entered until host process exits.
        /// EasyHook requires a matching Run method for the constructor
        /// </summary>
        /// <param name="context">The RemoteHooking context</param>
        /// <param name="channelName">The name of the IPC channel</param>
        public void Run(
            EasyHook.RemoteHooking.IContext context,
            string channelName)
        {
            try
            {
                _server.IsInstalled(EasyHook.RemoteHooking.GetCurrentProcessId());

               
                
                _server.ReportMessage("Installing Hooks...");
                 
                /**
                IntPtr _dllhandle = IntPtr.Zero;

                var galaxy = NativeLibrary.GetLibraryPathname("Galaxy.dll");
 

                _dllhandle = NativeLibrary.LoadLibrary("Galaxy.dll");

                if (_dllhandle == IntPtr.Zero)
                {
                    throw new Exception("Module not found!!!");

                }

                var handle = NativeLibrary.GetProcAddress(_dllhandle, "?Matchmaking@api@galaxy@@YAPAVIMatchmaking@12@XZ");

                // Apply thread

                if (handle == IntPtr.Zero)
                {
                    throw new  Exception("Method not found!!!");
                }


           

                **/

                var sender = EasyHook.LocalHook.GetProcAddress("WS2_32.dll", "send");
                _server.ReportMessage($"Found Sender: {sender}");
                var sendhook = EasyHook.LocalHook.Create(sender, new Del_WS2_32_Send(WS2_32_Send_Hook), this);
                _server.ReportMessage("Hook for sender installed...");
                sendhook.ThreadACL.SetExclusiveACL(new Int32[] { 0 });


                _server.ReportMessage("Hooks installed");
                _server.ReportMessage("Alying Command Listeners...");
               
                _server.ReportMessage("Acitivating Process...");

                EasyHook.RemoteHooking.WakeUpProcess();

                try
                {
                    _server.ReportMessage("Trying to contact Networking Interface...");
                    try
                    {
                        //_server.ReportMessage("Waiting for Network Interface to be ready...");

                        //IntPtr n = IntPtr.Zero;

                        //while (n == IntPtr.Zero)
                        //{

                        //    n = Networking();
                        //    System.Threading.Thread.Sleep(2000);
                        //}

                        //_server.ReportMessage($"Network Interface is ready. {n}");
                        //_server.ReportMessage($"Generating struct for Networking...");
                        //IntPtr vtablePtr = Marshal.ReadIntPtr(n, 0);

                        //Interceptors.Structs.NetworkingStruct nTable = Marshal.PtrToStructure<Interceptors.Structs.NetworkingStruct>(vtablePtr);

                        //_server.ReportMessage("Follwing Networking Method Addresses were found:");
                        //_server.ReportMessage($"SendP2PPacket={nTable.SendP2PPacket}");
                        //_server.ReportMessage($"PeekP2PPacket={nTable.PeekP2PPacket}");
                        //_server.ReportMessage($"IsP2PPacketAvailable={nTable.IsP2PPacketAvailable}");
                        //_server.ReportMessage($"ReadP2PPacket={nTable.ReadP2PPacket}");
                        //_server.ReportMessage($"PopP2PPacket={nTable.PopP2PPacket}");
                        //_server.ReportMessage($"GetPingWith={nTable.GetPingWith}");

                        //SendP2PPacketDelegate sendp2pD = Marshal.GetDelegateForFunctionPointer<SendP2PPacketDelegate>(nTable.SendP2PPacket);

                        //_server.ReportMessage("Trying to reach out for ListenerRegistar to hook into network traffic...");

                        //IntPtr tbRegistrar = IntPtr.Zero;

                        //while (tbRegistrar == IntPtr.Zero)
                        //{
                        //    tbRegistrar = ListenerRegistrar();
                        //}

                        //_server.ReportMessage($"Listener Register found at address: {tbRegistrar}");
                        //_server.ReportMessage("Generating struct...");

                        //IntPtr vtableRegistrar = Marshal.ReadIntPtr(tbRegistrar, 0);


                        //Interceptors.Structs.ListenerRegistrarStruct listenerRegistrarStruct = Marshal.PtrToStructure<Interceptors.Structs.ListenerRegistrarStruct>(vtableRegistrar);

                        //_server.ReportMessage($"Struct generated with methods:");
                        //_server.ReportMessage($"Register(*listenerType, *listener) = {listenerRegistrarStruct.Register}");
                        //_server.ReportMessage($"Unregister(*listenerType, *listener) = {listenerRegistrarStruct.Unregister}");

                        //_server.ReportMessage($"Registering delegates...");

                        //RegisterDelegate regD = Marshal.GetDelegateForFunctionPointer<RegisterDelegate>(listenerRegistrarStruct.Register);
                        //NetworkingListener l = new NetworkingListener(this.channelName);
                        //IntPtr t = Marshal.AllocHGlobal(Marshal.SizeOf(ListenerType.NETWORKING));

                        //Marshal.StructureToPtr(ListenerType.NETWORKING, t, false);

                        //IntPtr lt = Marshal.AllocHGlobal(Marshal.SizeOf(l));
                        //Marshal.StructureToPtr(l, lt, false);
                        //_server.ReportMessage($"Converted to pointers: {t}, {lt}");

                        //regD(t, lt);

                        //_server.ReportMessage($"Delegate registered.");


                    }
                    catch (Exception ex)
                    {
                        _server.ReportException(ex);
                    }


                    // Loop until FileMonitor closes (i.e. IPC fails)
                    while (true)
                    {
                        System.Threading.Thread.Sleep(1500);

                        string[] queued = null;

                        lock (_messageQueue)
                        {
                            queued = _messageQueue.ToArray();
                            _messageQueue.Clear();
                        }

                        // Send newly monitored file accesses to FileMonitor
                        if (queued != null && queued.Length > 0)
                        {
                            _server.ReportMessages(queued);
                        }
                        else
                        {
                            _server.Ping();
                        }

                       
                    }
                }
                catch (Exception e)
                {
                    // Ping() or ReportMessages() will raise an exception if host is unreachable
                }


                // Remove hooks
               // hookLobby.Dispose(); 

                // Finalise cleanup of hooks
                EasyHook.LocalHook.Release();



            }
            catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                this._server.ReportMessage("Error during hook process:");
                this._server.ReportException(e);
                Console.ResetColor();
            }


        }

        #region Imported Methods
       

        [DllImport("Galaxy.dll",
          CharSet = CharSet.Unicode,
            EntryPoint = "?Matchmaking@api@galaxy@@YAPAVIMatchmaking@12@XZ",
          SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr Matchmaking();

        [DllImport("Galaxy.dll",
         CharSet = CharSet.Unicode,
           EntryPoint = "?Networking@api@galaxy@@YAPAVINetworking@12@XZ",
         SetLastError = true, CallingConvention = CallingConvention.Cdecl)]  
        static extern IntPtr Networking();

        [DllImport("Galaxy.dll",
        CharSet = CharSet.Unicode,
          EntryPoint = "?ListenerRegistrar@api@galaxy@@YAPAVIListenerRegistrar@12@XZ",
        SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr ListenerRegistrar();

        [DllImportAttribute("ws2_32.dll", EntryPoint = "send", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        static extern IntPtr EXT_WS2_32_Send(uint s, byte[] buf, int len, int flags);

        #endregion

        #region Delegates

        /// <summary>
        /// The CreateFile delegate, this is needed to create a delegate of our hook function <see cref="CreateFile_Hook(string, uint, uint, IntPtr, uint, uint, IntPtr)"/>.
        /// </summary>
        /// <param name="filename"></param>
        /// <param name="desiredAccess"></param>
        /// <param name="shareMode"></param>
        /// <param name="securityAttributes"></param>
        /// <param name="creationDisposition"></param>
        /// <param name="flagsAndAttributes"></param>
        /// <param name="templateFile"></param>
        /// <returns></returns>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl,
                    CharSet = CharSet.Unicode,
                    SetLastError = true)]
        delegate IntPtr MatchmakingD();
        [UnmanagedFunctionPointer(CallingConvention.Cdecl,
                    CharSet = CharSet.Unicode,
                    SetLastError = true)]
        delegate IntPtr NetworkingD();

        [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet = CharSet.Auto, SetLastError = true)]
        delegate IntPtr Del_WS2_32_Send(uint s, byte[] buf, int len, int flags);

        #endregion

        #region Method Hooks
 
        IntPtr Matchmaking_Hook()
        {
            lock (this._messageQueue)
            {
                if (this._messageQueue.Count < 1000)
                { 
                    // Add message to send to FileMonitor
                    //this._messageQueue.Enqueue($"P{EasyHook.RemoteHooking.GetCurrentProcessId()}/T{ EasyHook.RemoteHooking.GetCurrentThreadId()}: Intercepted Lobby Call");
                }
            }

            return Matchmaking();
        }


        IntPtr WS2_32_Send_Hook(uint s, byte[] buf, int len, int flags)
        {
            string ss = System.Text.Encoding.UTF8.GetString(buf);

            this._server.ReportMessage($"Sent Packet: S={s}//buf={buf.Length}=={ss}, len = {len}, flags={flags}");

            return EXT_WS2_32_Send(s, buf, len, flags);
        }
         

        #endregion
    }
}
