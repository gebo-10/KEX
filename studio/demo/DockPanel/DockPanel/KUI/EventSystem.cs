using GLFW;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace KUI
{
    public class Event
    {
        //public int Id { get; set; }
        public enum Type
        {
            PointMove,
            PointIn,
            PointLeave,
            PointDown,
            PointUp,
            PointClick,
        }
        public Type type;
        public Vector2 position;
        public int button;
    }
    public class EventSystem
    {
        public Window window;


        public static List<Control> controls = new List<Control>();

        // bool mouseStay = false;
        Vector2 lastPress;

        Vector2 mousePosition;

        public void OnWindowsSizeChanged(object sender, SizeChangeEventArgs e)
        {
            window.OnSize(e.Size);
        }

        public void OnWindowKeyPress(object sender, KeyEventArgs e)
        {

        }

        public void OnWindowMouseMoved(object sender, MouseMoveEventArgs e)
        {
            lastPress = Vector2.Zero;

            mousePosition.X = (float)e.X;
            mousePosition.Y = (float)e.Y;
            Event ent = new Event();
            ent.position = mousePosition;
            ent.type = Event.Type.PointMove;
            List<Control> currentControls = new List<Control>();

            window.control.DispitchEvent(ent, ref currentControls);

            Event leaveEvent = new Event();
            leaveEvent.position = mousePosition;
            leaveEvent.type = Event.Type.PointLeave;
            var leave = controls.Except(currentControls);
            foreach (Control c in leave)
            {
                c.OnEvent(leaveEvent);
            }

            Event inEvent = new Event();
            inEvent.position = mousePosition;
            inEvent.type = Event.Type.PointIn;
            var inControls = currentControls.Except(controls);
            foreach (Control c in inControls)
            {
                c.OnEvent(inEvent);
            }

            controls = currentControls;

            //Render();
        }

        public void OnWindowRefreshed(object sender, EventArgs e)
        {

        }
        public void OnMouseButton(object? sender, MouseButtonEventArgs e)
        {
            if (controls.Count <= 0)
            {
                return;
            }
            var hit = controls.Last();

            Event ent = new Event();
            ent.position = mousePosition;
            ent.button = (int)e.Button;

            if (e.Action == InputState.Press)
            {
                ent.type = Event.Type.PointDown;
                lastPress = mousePosition;
            }
            else if (e.Action == InputState.Release)
            {
                if (lastPress != Vector2.Zero && lastPress == mousePosition)
                {
                    ent.type = Event.Type.PointClick;
                    hit.OnEvent(ent);
                }
                lastPress = Vector2.Zero;
                ent.type = Event.Type.PointUp;
            }
            hit.OnEvent(ent);
        }
        public void OnMouseLeave(object? sender, EventArgs e)
        {
            controls.Clear();
        }

        public void OnClose(object? sender, EventArgs e)
        {
            Console.WriteLine("CLOSE");
            //opening = false;
        }
    }
}
