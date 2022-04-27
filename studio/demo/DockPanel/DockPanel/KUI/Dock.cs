using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUI
{
    public class Dock : Control
    {
        public int selectIndex=0;
        public List<Panel> panels;

        public Dock(float width, float height) : base(width, height)
        {
        }
    }
}
