using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SWBFHOOK.Models
{
	[StructLayout(LayoutKind.Sequential)]
	public struct GalaxyInitOptions
	{
		public IntPtr clientID;
		public IntPtr clientSecret;
		public IntPtr configFilePath;
		public IntPtr storagePath;
		public IntPtr host;
		public IntPtr port;
	}

}
