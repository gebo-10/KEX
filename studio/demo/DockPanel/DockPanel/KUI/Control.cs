using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Facebook.Yoga;
using System.Drawing;
using SkiaSharp;
using System.Numerics;
using GLFW;
using System.Runtime.InteropServices;

namespace KUI
{
	public delegate void RenderFunc(SKCanvas canvas, Rect rect);
	public delegate void EventProcesser(Event e);
	public class Control
	{
		public int id=0;
		public bool active;
		public bool visible;
		
        public Context context;
		public YogaNode layout;

		public RenderFunc? OnRender;
		public EventProcesser? OnCatch;
		public EventProcesser? OnBubbling;
		public EventProcesser? OnEvent;

		bool catched = false;
		Vector2 absPosition;


		public Control()
        {
			//id= Guid.NewGuid();
			layout = new YogaNode(Env.yogaConfig);
			layout.Left = 0;
			layout.Right = 0;
			layout.Top = 0;
			layout.Bottom = 0;
			DefaultSetting();
		}

		public Control(float width, float height)
        {
			layout = new YogaNode(Env.yogaConfig);
			layout.Width = width;
			layout.Height = height;
			DefaultSetting();
		}

		private void DefaultSetting()
		{
			layout.Control = this;
			OnRender += (SKCanvas canvas, Rect rect) =>
			{
				//if (catched)
				//{
				//    var p = new SKPaint { Color = SKColor.Parse("#3399EE"), Style = SKPaintStyle.Fill, IsAntialias = true };
				//    canvas.DrawRect(rect.x, rect.y, rect.width, rect.height, p);
				//}
				//else
				//{
				//    var p = new SKPaint { Color = SKColor.Parse("#FFFFFF"), Style = SKPaintStyle.Fill, IsAntialias = true };
				//    canvas.DrawRect(rect.x, rect.y, rect.width, rect.height, p);
				//}
				var headerPaint = new SKPaint { Color = SKColor.Parse("#FF99EE"), Style = SKPaintStyle.Stroke, IsAntialias = true };
				canvas.DrawRect(rect.x, rect.y, rect.width, rect.height, headerPaint);
			};

			OnCatch += (Event e) =>
			{
				//Console.WriteLine("catch" + id); 
			};
			OnBubbling += (Event e) =>
			{
				//Console.WriteLine("bubbling" + id); 
			};
			OnEvent += (Event e) => { };
		}
		
		public virtual void AddChild(Control control)
		{
            control.context = context;
			layout.AddChild(control.layout);
		}

		public virtual void RemoveChild(Control control)
		{
			layout.RemoveChild(control.layout);
		}

		public void Render(SKCanvas canvas,Rect rect)
		{
			
			Rect r = new Rect();
            r.x = layout.LayoutX+rect.x;
            r.y = layout.LayoutY + rect.y;
            r.width = layout.LayoutWidth;
            r.height = layout.LayoutHeight;
			absPosition.X = r.x;
			absPosition.Y = r.y;
			if (OnRender != null) OnRender(canvas, r);
			for (int i = 0; i < layout.Count; i++)
			{
				var c = layout[i].Control;
				c.Render(canvas, r);
			}
		}

		public bool DispitchEvent(Event e, ref List<Control> controls)//,List<Control> controls
		{
			if (e.position.X > absPosition.X && e.position.X < absPosition.X + layout.LayoutWidth && e.position.Y > absPosition.Y && e.position.Y < absPosition.Y + layout.LayoutHeight)
			{
				controls.Add(this);
				OnCatch(e);
				bool pass = false;
				for (int i = layout.Count-1; i >0; i--)
				{
					pass=pass || layout[i].Control.DispitchEvent(e, ref controls);
				}
				if(!pass)
                {
					OnEvent(e);
				}
                else
                {
					OnBubbling(e);
                }
				return true;
            }
            else
            {
				return false;
            }
		}

	}
}
