using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KUI
{
    public class Label : Control
    {
        public Label(float width, float height) : base(width, height)
        {
        }

        public string Text { get; set; }
        public void OnRender(Rect rect)
        {
            //var headerPaint = new SKPaint { Color = SKColor.Parse("#333333"), TextSize = 50, IsAntialias = true };
            //canvas.DrawText("Hello from GLFW.NET + SkiaSharp!", 10, 60, headerPaint);
        }
    }
}
