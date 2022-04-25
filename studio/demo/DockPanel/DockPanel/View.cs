using Facebook.Yoga;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
namespace KUI
{
    public class View : Control
    {
        YogaNode root;
		Vector2 offset;
		public View()
        {
			root = new YogaNode();
			//OnRender = (Rect rect) => { };
		}
		public virtual void AddChild(Control control)
		{
			root.AddChild(control.layout);
		}

		public virtual void RemoveChild(Control control)
		{
			root.RemoveChild(control.layout);
		}
	}
}
