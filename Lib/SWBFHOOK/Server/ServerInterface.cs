using System;
using System.Collections.Generic;
using System.Text;

namespace SWBFHOOK.Server
{
    /// <summary>
    /// Provides an interface for communicating from the client (target) to the server (injector)
    /// </summary>
    public class ServerInterface : MarshalByRefObject
    {
         


        public void IsInstalled(int clientPID)
        {
            Console.WriteLine("[HOOK] FileMonitor has injected SWBFHOOK into process {0}.\r\n", clientPID);
        }

        

        /// <summary>
        /// Output messages to the console.
        /// </summary>
        /// <param name="clientPID"></param>
        /// <param name="fileNames"></param>
        public void ReportMessages(string[] messages)
        {
            for (int i = 0; i < messages.Length; i++)
            {
                Console.WriteLine($"[HOOK] {messages[i]}");
            }
        }

        public void ReportMessage(string message)
        {
            Console.WriteLine($"[HOOK] {message}"); 
        }

        /// <summary>
        /// Report exception
        /// </summary>
        /// <param name="e"></param>
        public void ReportException(Exception e)
        {
            Console.WriteLine("[HOOK] The target process has reported an error:\r\n" + e.ToString());

            var inner = e.InnerException;
            int depth = 0;
            while (inner != null)
            {
                depth++;
                string minuses = "";

                for(int i = 0; i<depth; i++)
                {
                    minuses += "-";
                }

                Console.WriteLine($"[HOOK]-{minuses}> INNER EXCEPTION:\r\n" + inner.ToString());

            }
        }

        /// <summary>
        /// Called to confirm that the IPC channel is still open / host application has not closed
        /// </summary>
        public void Ping()
        {
           // Console.WriteLine($"[HOOK] Pong!");
        }

        private Func<IntPtr> InfoAction;

        public void OnInfoCommand(Func<IntPtr> infoAction)
        {
            this.InfoAction = infoAction;
        }

        public IntPtr Info()
        {
            if (this.InfoAction != null)
            {
                return this.InfoAction();
            }

            return IntPtr.Zero;
        }


        private Dictionary<string, Func<object[], object>> commandListeners = new Dictionary<string, Func<object[], object>>();

        public void Exec(string command, Action<object> callback, params object[]args)
        {
            if (this.commandListeners.ContainsKey(command))
            {
                object result =  this.commandListeners[command](args);

                callback(result);
            }
        }

        public void OnCommand(string command, Func<object[], object> callback)
        {
            this.ReportMessage($"Command Listener for {command} added.");
            this.commandListeners.Add(command, callback);
        }

         
    }
}
