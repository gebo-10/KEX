using Facebook.Yoga;
using SkiaSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
namespace KUI
{
    public class DockRegion :Control
    {
        Rect DrawRegion=new Rect();
        int direction = 0;
        public DockRegion()
        {
            OnRender += (SKCanvas canvas, Rect rect) =>
             {
                 var p = new SKPaint { Color = SKColor.Parse("#3399EE"), Style = SKPaintStyle.Fill, IsAntialias = true };
                 canvas.DrawRect(rect.x+ DrawRegion.x*rect.width, rect.y+DrawRegion.y * rect.height, rect.width * DrawRegion.width, rect.height * DrawRegion.height, p);
             };
            OnEvent += (Event e) => { 
                if(e.type == Event.Type.PointMove)
                {
                    var layoutPosition=new Vector2(layout.LayoutX, layout.LayoutY);
                    var relaPos = e.position - layoutPosition;
                    relaPos = relaPos / new Vector2(layout.LayoutWidth, layout.LayoutHeight);
                    relaPos -= new Vector2(0.5f, 0.5f);
                    if(relaPos.X < -0.15f)
                    {
                        DrawRegion.x = 0;
                        DrawRegion.width = 0.35f;
                        DrawRegion.y = 0;
                        DrawRegion.height = 1;
                    }
                    else if(relaPos.X > 0.15f)
                    {
                        DrawRegion.x = 0.65f;
                        DrawRegion.width = 0.35f;
                        DrawRegion.y = 0;
                        DrawRegion.height = 1;
                    }else if(relaPos.Y < -0.15f)
                    {
                        DrawRegion.x = 0;
                        DrawRegion.width = 1;
                        DrawRegion.y = 0;
                        DrawRegion.height = 0.35f;
                    }
                    else if(relaPos.Y >0.15)
                    {
                        DrawRegion.x = 0;
                        DrawRegion.width = 1;
                        DrawRegion.y = 0.65f;
                        DrawRegion.height = 0.35f;
                    }
                    else
                    {
                        DrawRegion.x = 0;
                        DrawRegion.width = 1f;
                        DrawRegion.y = 0;
                        DrawRegion.height = 1f;
                    }
                }
                context.window.Render();
            };
        }

       //void InitContent()
       // {
       //     var content = new Control();
       //     content.layout.Height = YogaValue.Auto();
       //     content.layout.Width = YogaValue.Auto();
       //     content.layout.FlexGrow = 1;
       //     content.layout.Margin = 5;
       //     //content.layout.BorderWidth = 5;
       //     content.layout.FlexDirection = YogaFlexDirection.Row;
       //     content.layout.PositionType = YogaPositionType.Absolute;

       //     var region= new Control();
       //     region.layout.Height = YogaValue.Auto();
       //     region.layout.Width = YogaValue.Auto();
       //     region.layout.PositionType = YogaPositionType.Absolute;
       // }
    }
}
