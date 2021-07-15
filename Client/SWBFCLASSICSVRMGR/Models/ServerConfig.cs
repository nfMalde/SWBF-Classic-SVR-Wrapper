using System;
using System.Collections.Generic;
using System.Text;

namespace SWBFCLASSICVRMGR.Models
{
    public class ServerConfig
    {

        public string ExecutablePath { get; set; }

        public SWBFMap[] AvailableMaps { get; set; }

        public List<SWBFServer> DedicatedServers { get; set; }
        
    }
}
