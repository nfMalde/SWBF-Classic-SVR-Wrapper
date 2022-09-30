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
using SWBFHOOK.Models;

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

             
                _server.ReportMessage("Registering Hook: ::Init...");
                var galaxy_init = EasyHook.LocalHook.GetProcAddress("Galaxy.dll", "?Init@api@galaxy@@YAXABUInitOptions@12@@Z");
                _server.ReportMessage($"Found Init Function: {galaxy_init}");
                var galaxy_init_hook = EasyHook.LocalHook.Create(galaxy_init, new DInit(Init_Hook), this);
                _server.ReportMessage("Registering Hook: ::Init Completed");
                galaxy_init_hook.ThreadACL.SetExclusiveACL(new Int32[] { 0 });


                _server.ReportMessage("Hooks installed"); 
               
                _server.ReportMessage("Acitivating Process...");

                EasyHook.RemoteHooking.WakeUpProcess();

                try
                {
                   


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
          EntryPoint = "?Init@api@galaxy@@YAXABUInitOptions@12@@Z",
        SetLastError = true, CallingConvention = CallingConvention.Cdecl)]
        static extern void GalaxyOrigInit(GalaxyInitOptions initOptions);
         

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
        delegate void DInit([MarshalAs(UnmanagedType.Struct)] GalaxyInitOptions initOptions);
        
        
        
        #endregion

        #region Method Hooks
        void Init_Hook(GalaxyInitOptions initOptions)
        {
            string getClientId = Marshal.PtrToStringAnsi(initOptions.clientID);

            _server.ReportMessage($"Init is called with params: clientID={getClientId}, secret=...");
            _server.ReportMessage("Server Init complete. Registering listeners...");
            GalaxyOrigInit(initOptions);
        } 

        #endregion
    }
}
