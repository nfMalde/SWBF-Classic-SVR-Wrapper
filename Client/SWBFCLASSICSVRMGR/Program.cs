using Newtonsoft.Json;
using SWBFHOOK.Server;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

namespace SWBFCLASSICVRMGR
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine();
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.WriteLine(@"
 ____ _     ____ _____     ____ _    ____ ____ ____ _ ____ 
/ ___/ \  //  __/    /    /   _/ \  /  _ / ___/ ___/ /   _\
|    | |  || | /|  _______|  / | |  | / \|    |    | |  /  
\___ | |/\|| |_\| |  \____|  \_| |_/| |-|\___ \___ | |  \__
\____\_/  \\____\_/       \____\____\_/ \\____\____\_\____/
                                                           
");



            Console.ForegroundColor = ConsoleColor.White;

            Console.WriteLine("-------------------------------------------------------");
            Console.WriteLine("   Server  Hook to adance your server usage.");

            Console.WriteLine();
            Console.ResetColor();

            string injectionLibrary = Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), "SWBFHOOK.dll");

            if (System.IO.File.Exists(injectionLibrary))
            {

                Console.WriteLine($"Injection Hook found at {injectionLibrary}");
                Console.WriteLine("Starting Server Manager...");
                ServerManager();
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine($"The Hook Library SWBF-Hook.dll was not found at location {injectionLibrary}");
               
            }


            Console.ReadKey();
        }


        private static void SaveConfig(Models.ServerConfig config)
        {
            string configPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "SWBF-ServerMgr");

            string file = Path.Combine(configPath, "server.json");
            string contents = JsonConvert.SerializeObject(config);

            using (FileStream fs = new FileStream(file, FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.ReadWrite))
            {
                byte[] content = new UTF8Encoding(true).GetBytes(contents);
                fs.Write(content, 0, content.Length);
            }

        }

        private static void ServerManager()
        {
            string configPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "SWBF-ServerMgr");

            Console.WriteLine("Checking if Config Folder exists...");

            if (!Directory.Exists(configPath))
            {
                Console.WriteLine("Folder does not exists will create...");

                Directory.CreateDirectory(configPath);
            }

    
            Console.WriteLine("Scanning for config files...");

            string[] configFiles = new string[]
            {
                "server.json"
            };

            foreach(string file in configFiles)
            {
                bool exists = File.Exists(Path.Combine(configPath, file));

                Console.WriteLine($"{file}.. {(exists ? "FOUND" : "NOT FOUND")}");
            }


            Console.WriteLine("Config Check complete. Loading...");

            Console.WriteLine("Server Config will be loaded...");

            FileInfo fi = new FileInfo(Path.Combine(configPath, "server.json"));

            Models.ServerConfig serverConfig = null;

            if (!fi.Exists || fi.Length == 0)
            {
                fi = null;
                serverConfig = new Models.ServerConfig();

                serverConfig.AvailableMaps = DefaultMaps();
                serverConfig.DedicatedServers = new List<Models.SWBFServer>();

                Console.WriteLine("Creating Config Structure...");

                SaveConfig(serverConfig);
                

            }

            serverConfig = JsonConvert.DeserializeObject<Models.ServerConfig>(File.ReadAllText(Path.Combine(configPath, "server.json")));

            Console.WriteLine("Checking for executable...");

            if (string.IsNullOrEmpty(serverConfig.ExecutablePath))
            {
                bool exeFound = false;

                Console.ResetColor();

               
                while (!exeFound)
                {
                    Console.ForegroundColor = ConsoleColor.Green;

                    Console.WriteLine("Please enter the path of the  **FOLDER** where your battlefront.exe is located:");


                    string exePath = Console.ReadLine();

                    string p = Path.Combine(exePath, "Battlefront.exe");

                    if (!File.Exists(p))
                    {
                        Console.ForegroundColor = ConsoleColor.Red;

                        Console.WriteLine($"Cannot find Battlefront.exe at path {p}. Please try again...");
                        Console.ResetColor();
                        continue;
                    }

                    serverConfig.ExecutablePath = p;

                    SaveConfig(serverConfig);
                    exeFound = true;
                }

            }

            Console.WriteLine("Executable Path is: " + serverConfig.ExecutablePath);

            Console.WriteLine("Checking for existing dedicated servers...");

            if (!serverConfig.DedicatedServers.Any())
            {
                Console.WriteLine("No Servers found. Starting Wizard...");
                ServerWizard(serverConfig);
            }


            Models.SWBFServer server = null;

            Console.WriteLine("Configured Servers:");

            for(int si = 0; si<serverConfig.DedicatedServers.Count; si++)
            {
                var s = serverConfig.DedicatedServers[si];
                Console.WriteLine($"#{si} - {s.Name}");
                Console.WriteLine("-----------------------------------------");
                Console.WriteLine($"Max-Players: {s.MaxPlayers} - Bots: {s.BotCount} - Map List Count: {s.Maps.Count()}");
            }

            while (server == null)
            {
                Console.ResetColor();
                Console.WriteLine("Please Select your server by entering the number or enter 'new' to create new  one:");

                string idOrNew = Console.ReadLine();

                int id = 0;
                if (idOrNew.ToLower() == "new")
                {
                    server = ServerWizard(serverConfig);
                }
                else if (int.TryParse(idOrNew, out id))
                {
                    if (id >= serverConfig.DedicatedServers.Count)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine($"Id {id} does not exists.");
                        Console.ResetColor();
                        continue;
                    } else
                    {
                        server = serverConfig.DedicatedServers[id];
                        continue;
                    }
                } else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Invalid Id {idOrNew}.");
                    Console.ResetColor();
                    continue;
                }

            }

            Console.WriteLine("******************************************************");
            Console.WriteLine("Server will be launched:");
            Console.WriteLine($"** Name:  {server.Name}");
            Console.WriteLine($"** Max Players:  {server.MaxPlayers}");
            Console.WriteLine($"** Bots per Team:  {server.BotCount}");
            Console.WriteLine($"** Maps:  {string.Join(";", server.Maps.Select(x => $"{x.MapKey}_{x.ReeinformcentsTeamA}:{x.ReeinforcementsTeamB}"))}");
            Console.WriteLine($"** Additional Params:  {string.Join(" ", server.AdditionalParams ?? new string[0])}");
            Console.WriteLine("Saving Config...");
            SaveConfig(serverConfig);


            Console.WriteLine("Starting Battlefront.exe...");

            Launch(serverConfig, server);

        }


        private static Models.SWBFServer ServerWizard(Models.ServerConfig serverConfig)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("Welcome to the Server Wizard!");

            Console.WriteLine("What Name should your dedicated server have?");
            string servername = null;
            int maxPlayers = 0;
            int bots = -1;


            // Server Name
            while(servername == null)
            {
                string _n = Console.ReadLine();

                if (_n.Length > 20)
                {
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Error: Maximum length of server name exceeded by {_n.Length - 20} characters. Please try again...");
                    Console.ResetColor();
                } else
                {
                    servername = _n;
                }
            }

            // Player Count
            Console.WriteLine("How many players you want to host (min. 1, max. 33)?");
            while (maxPlayers == 0)
            {
                string _pc = Console.ReadLine();

                int _p = 0;

                if (!int.TryParse(_pc, out _p))
                {
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Error: Player Count must be an number gt zero. Please try again...");
                    Console.ResetColor();

                }
                else if (_p > 33 || _p < 1)
                {
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Error: GOG Version does not support player count over 33. I know that sucks but try again please...");
                    Console.ResetColor();
                }
                else
                {
                    maxPlayers = _p;
                }
            }

            Console.WriteLine("How many AI Team Mates should be there?");

            while (bots == -1)
            {
                string _pc = Console.ReadLine();

                int _b = 0;

                if (!int.TryParse(_pc, out _b))
                {
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Error: AI Count must be an number gt or eq zero. Please try again...");
                    Console.ResetColor();

                }
                else if (_b < 0)
                {
                    Console.ResetColor();
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine($"Error: AI Count must be an number gt or eq zero. Please try again...");
                    Console.ResetColor();
                }
                else
                {
                    bots = _b;
                }
            }

            Models.SWBFServer sWBFServer = new Models.SWBFServer();
            sWBFServer.Name = servername;
            sWBFServer.Maps = new List<Models.SWBFServerMap>().ToArray();
            sWBFServer.MaxPlayers = maxPlayers;
            sWBFServer.BotCount = bots;


            Console.WriteLine("This info have been saved. You can modify it later in the config file.");

            Console.WriteLine("Now tell us the map pool please. Type the number or the code of the map to add it. If youre finished just leave it blank and hit enter.");
            Console.WriteLine($"If you want to have your custom map available via number just add in to 'AvailableMaps' in  you server.json at " + Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "SWBF-ServerMgr"));
            Console.WriteLine("Displaying Default Maps from SWBF. For Adding a Custom Map enter the map key (eg. 'bes1a')");

            Models.SWBFMap[] maps = serverConfig.AvailableMaps ?? DefaultMaps();

            for(int mapIndex = 0; mapIndex < maps.Length; mapIndex++)
            {
                Console.WriteLine($"#{mapIndex} - {maps[mapIndex].Key} ({maps[mapIndex].Name})");
            }

            bool mapPoolComplete = false;
            List<Models.SWBFServerMap> serverMaps = new List<Models.SWBFServerMap>();

            while(!mapPoolComplete)
            {
                Console.WriteLine("Please enter the code of the map or the number. Leave blank for finishing.");

                string codeOrNumber = Console.ReadLine();

                if (string.IsNullOrEmpty(codeOrNumber))
                {
                    mapPoolComplete = true ;
                    continue;
                }

                int n = 0;

                bool isNumeric = int.TryParse(codeOrNumber, out n);

                Models.SWBFMap map = null;
                if (isNumeric)
                {
                    if (n >= maps.Length)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Error: Invalid Map number " + n);
                        Console.ResetColor();
                        continue;
                    } else
                    {
                        map = maps[n]; 
                    }
                } else
                {
                    map = maps.FirstOrDefault(x => x.Key.ToLower() == codeOrNumber.ToLower());

                    if (map == null)
                    {
                        bool decisonMade = false;
                        bool doAdd = false;

                        while (!decisonMade)
                        {
                            Console.ForegroundColor = ConsoleColor.Yellow;
                            Console.WriteLine($"WARN: Map {codeOrNumber} was not found in AvailableMaps. You want me to add it anyway? (This can cause the server to crash if this map is not installed)[Y/N]:");
                            Console.ResetColor();

                            ConsoleKeyInfo info = Console.ReadKey();

                            if (info.Key == ConsoleKey.Y || info.Key == ConsoleKey.N)
                            {
                                doAdd = info.Key == ConsoleKey.Y;
                                decisonMade = true;
                                continue;
                            }

                        }


                        if (!doAdd)
                        {
                            continue;
                        }

                    }



                }



                Console.WriteLine(($"Adding Map {map.Key} ({map.Name}"));



                int rA = 0;
                int rB = 0;

                while (rA == 0)
                {
                    Console.WriteLine($"Tell us the reinforcements please for TeamA (min. 1):");
                    string _rA = Console.ReadLine();
                    int __ra = 0;

                    if (!int.TryParse(_rA, out __ra))
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Error: Reeinforcments have to be greater than 0 and be valid number.");
                        continue;
                    }
                    else if (__ra < 1)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Error: Reeinforcments have to be greater than 0 and be valid number.");
                        continue;
                    }
                    else
                    {
                        rA = __ra;
                    }
                }

                while (rB == 0)
                {
                    Console.WriteLine($"Tell us the reinforcements please for TeamB (min. 1):");
                    string _rB = Console.ReadLine();
                    int __rb = 0;

                    if (!int.TryParse(_rB, out __rb))
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Error: Reeinforcments have to be greater than 0 and be valid number.");
                        continue;
                    }
                    else if (__rb < 1)
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Error: Reeinforcments have to be greater than 0 and be valid number.");
                        continue;
                    }
                    else
                    {
                        rB = __rb;
                    }
                }


                serverMaps.Add(new Models.SWBFServerMap()
                {
                    MapKey = map.Key,
                    ReeinformcentsTeamA = rA,
                    ReeinforcementsTeamB = rB
                });
            }


            sWBFServer.Maps = serverMaps.ToArray();


           

            serverConfig.DedicatedServers.Add(sWBFServer);

            return sWBFServer;
        }


        private static Models.SWBFMap[] DefaultMaps()
        {
            List<Models.SWBFMap> defaultMaps = new List<Models.SWBFMap>();


            defaultMaps.Add(new Models.SWBFMap() { Key = "bes1a", Name = "Bespin: Platforms GCW" });                
            defaultMaps.Add(new Models.SWBFMap() { Key = "bes1r", Name="Bespin: Platforms CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "bes2a", Name="Bespin: Cloud City GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "bes2r", Name="Bespin: Cloud City CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "end1a", Name="Endor: Bunker"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "geo1r", Name="Geonosis: Spire"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "hot1i", Name = "Hoth: Echo Base" });
            defaultMaps.Add(new Models.SWBFMap() { Key = "kam1c", Name="Kamino: Tipoca City"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "kas1c", Name="Kashyyyk: Islands CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "kas1i", Name="Kashyyyk: Islands GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "kas2c", Name="Kashyyyk: Docks CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "kas2i", Name="Kashyyyk: Docks GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "nab1c", Name="Naboo: Plains CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "nab1i", Name="Naboo: Plains GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "nab2a", Name="Naboo: Theed GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "nab2c", Name="Naboo: Theed CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "rhn1i", Name="Rhen Var: Harbor GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "rhn1r", Name="Rhen Var: Harbor CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "rhn2a", Name="Rhen Var: Citadel GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "rhn2c", Name="Rhen Var: Citadel CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat1i", Name="Tatooine: Dune Sea GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat1r", Name="Tatooine: Dune Sea CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat2i", Name="Tatooine: Mos Eisley GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat2r", Name="Tatooine: Mos Eisley CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "yav1c", Name="Yavin IV: Temple CW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "yav1i", Name="Yavin IV: Temple GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "yav2i", Name="Yavin IV: Arena GCW"});
            defaultMaps.Add(new Models.SWBFMap() { Key = "yav2r", Name = "Yavin IV: Arena CW" });
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat3c", Name = "Tatooine: Jabba's Palace CW" });
            defaultMaps.Add(new Models.SWBFMap() { Key = "tat3a", Name = "Tatooine: Jabba's Palace GCW" });

            return defaultMaps.ToArray();
        }


        private static void Launch(Models.ServerConfig config, Models.SWBFServer server)
        {
            string launchParam = GetLaunchParams(server);
            string pp = "/win /norender /noteamdamage /autonet dedicated /resolution 320 240 /nosound /noaim /tps 57 /gamename NoAI NoCP /playerlimit 12 /playercount 0 /bots 0 /difficulty 1 /throttle 3072 /spawn 5 bes2r 100 100 bes2a 100 100";
            string exe = config.ExecutablePath;
            ProcessStartInfo i = new ProcessStartInfo(exe);
            i.WorkingDirectory = Path.GetDirectoryName(exe);
            i.Arguments = launchParam;
            string channelName = null;
            string injectionLibrary = Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), "SWBFHOOK.dll");
    
            var commandline =  EasyHook.RemoteHooking.IpcCreateServer<ServerInterface>(ref channelName, System.Runtime.Remoting.WellKnownObjectMode.Singleton);
            var commander = EasyHook.RemoteHooking.IpcConnectClient<ServerInterface>(channelName);
            int pid = 0;
            EasyHook.RemoteHooking.CreateAndInject(
                   exe,          // executable to run
                   launchParam,                 // command line arguments for target
                   0,                  // additional process creation flags to pass to CreateProcess
                   EasyHook.InjectionOptions.DoNotRequireStrongName, // allow injectionLibrary to be unsigned
                   injectionLibrary,   // 32-bit library to inject (if target is 32-bit)
                   injectionLibrary,   // 64-bit library to inject (if target is 64-bit)
                   out pid,      // retrieve the newly created process ID
                   channelName         // the parameters to pass into injected library
                                       // ...
               );
          
            Console.WriteLine($"Hooked to process {pid}....");
            /**
            int seconds = 60;

            while (seconds > 0)
            {
                seconds--;

                Console.WriteLine($"Hooking begins in {seconds} Seconds...");
                Thread.Sleep(1000);
            }

            

            Console.WriteLine($"Hooking now to process id {p.Id}");
            EasyHook.RemoteHooking.IpcCreateServer<ServerInterface>(ref channelName, System.Runtime.Remoting.WellKnownObjectMode.Singleton);
            EasyHook.RemoteHooking.Inject(
                   p.Id,          // ID of process to inject into
                   injectionLibrary,   // 32-bit library to inject (if target is 32-bit)
                   injectionLibrary,   // 64-bit library to inject (if target is 64-bit)
                   channelName         // the parameters to pass into injected library
                                       // ...
               );
            **/
            bool close = false;
            
            while (!close)
            {
                Console.WriteLine("Please write your command....");
                var line = Console.ReadLine();


                if (line == "exit")
                {
                    close = true;
                    //p.Kill();
                    continue;
                }

                switch (line)
                {
                    case "info":
                        commander.Exec("info", (result) =>
                        {
                            Console.WriteLine("Info: " + result);
                        });
                       

                        break;


                    default:
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine($"Error: Command {line} unknown");
                        Console.ResetColor();
                        break;
                }

                // TODO: Write admin commands


            } 

        }

        private static string GetLaunchParams(Models.SWBFServer server)
        {
            List<string> p = new List<string>();

            // Default Params

            p.Add("/win");
            p.Add("/norender");
            p.Add("/noteamdamage");
            p.Add("/autonet dedicated");
            p.Add("/resolution 320 240");
            p.Add("/nosound");
            p.Add("/noaim");
            p.Add("/tps 57");
            p.Add("/playercount 0");
            p.Add("/throttle 3072");
            // Server Params

            p.Add($"/gamename {server.Name}");
            p.Add($"/playerlimit {server.MaxPlayers}");
            p.Add($"/bots {server.BotCount}");
            p.Add("/spawn 5");

            // Map Pool

            p.Add(string.Join(" ", server.Maps.Select(x => $"{x.MapKey} {x.ReeinformcentsTeamA} {x.ReeinforcementsTeamB}")));

            return string.Join(" ", p);
        }

    }
}
