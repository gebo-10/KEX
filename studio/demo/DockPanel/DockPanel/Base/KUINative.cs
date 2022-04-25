using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DockPanel.Base
{
    public class KUINative
    {
        [DllImport("user32.dll")]
        // GetCursorPos() makes everything possible
        static extern bool GetCursorPos(ref Point lpPoint);
    }
}
