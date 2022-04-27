using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace KUI
{
    public class KUINative
    {
        [DllImport("user32.dll")]
        static extern bool GetCursorPos(ref Point lpPoint);
        public static Vector2 GetScreenCursorPos()
        {
            Point pos= new Point();
            GetCursorPos(ref pos);
            return new Vector2((float)pos.X, (float)pos.Y);
        }
    }
}
