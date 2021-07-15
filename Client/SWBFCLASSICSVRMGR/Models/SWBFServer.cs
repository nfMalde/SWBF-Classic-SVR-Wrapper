using System;
using System.Collections.Generic;
using System.Text;

namespace SWBFCLASSICVRMGR.Models
{
    public class SWBFServer
    {
        public string Name { get; set; }

        public int MaxPlayers { get; set; }

        public int BotCount { get; set; }

        public SWBFServerMap[] Maps { get; set; }


        public string[] AdditionalParams { get; set; }
    }
}
