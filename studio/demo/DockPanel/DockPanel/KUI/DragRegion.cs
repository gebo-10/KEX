using GLFW;
using System.Numerics;
namespace KUI
{
    public class DragRegion : Control
    {
        bool drag;
        Vector2 offset = new Vector2();
        public DragRegion()
        {
            OnEvent += (Event e) =>
            {
                if(e.type== Event.Type.PointDown)
                {
                    drag = true;
                    offset = context.window.Position - KUINative.GetScreenCursorPos();
                    Thread t = new Thread(() =>
                    {
                        while (drag)
                        {
                            var pos = KUINative.GetScreenCursorPos();
                            context.window.Position = pos + offset; //Thread.Sleep(10);
                            if(Glfw.GetMouseButton(context.window.nativeWindow, MouseButton.Left)!= InputState.Press)
                            {
                                drag=false;
                            }
                        }
                    });
                    t.Start();
                }
                else if(e.type== Event.Type.PointUp)
                {
                    drag = false;
                }
            };
        }
    }
}
