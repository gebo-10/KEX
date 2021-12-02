global using System;
global using System.Collections.Generic;
global using System.Linq;
global using System.Text;
global using System.Threading.Tasks;

namespace KStudio.Core
{
    public class Core
    {
        public PluginManager pluginManager= new PluginManager ();
        public static void hello()
        {
            Console.WriteLine("hello");
        }
    }
}
