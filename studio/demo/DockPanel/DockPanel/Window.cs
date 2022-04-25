using System;
using System.Collections.Generic;
using System.Drawing;
using Facebook.Yoga;
using GLFW;
using SkiaSharp;
using System.Runtime.InteropServices;
using System.Numerics;

namespace KUI
{
    public class Window
    {
        public NativeWindow window;
        private SKCanvas canvas;
        private GRContext context;
        private SKSurface surface;

        public Control control;

        public static List<Control> controls = new List<Control>();

        bool mouseStay = false;
        Vector2 lastPress;

        Vector2 mousePosition;
        public Window()
        {
            control = new Control(100,100);
        }
        public void Open(int width, int height, string title, bool decorated=true)
        {
            Glfw.WindowHint(Hint.Decorated, decorated);
            window = new NativeWindow(width, height, title);
           
            context = GenerateSkiaContext(window);

            OnSize(new Size(width,height) );
            Render();
            SubscribeToWindowEvents();
            while (!Glfw.WindowShouldClose(window))
            {
                Glfw.WaitEvents();
            }
        }

        public void Close()
        {
            window.Close();
        }

        private void OnSize(Size size)
        {
            if(size.Width<=0 || size.Height<=0) return;
            control.layout.Width = size.Width;
            control.layout.Height = size.Height;
            Layout(size);
            if (surface != null)
            {
                surface.Dispose();
                canvas.Dispose();
            }
            surface = GenerateSkiaSurface(context, size);
            canvas = surface.Canvas;
            Render();
        }
        public void Layout(Size size)
        {
            control.layout.CalculateLayout();
        }
        public void Render()
        {
            canvas.Clear(SKColor.Parse("#F0F0F0"));

            var rect = new Rect();
            rect.x = 0;
            rect.y = 0;
            rect.width =control.layout.LayoutWidth;
            rect.height = control.layout.LayoutHeight;
            control.Render(canvas, rect);

            canvas.Flush();
            window.SwapBuffers();
        }

        private  void SubscribeToWindowEvents()
        {
            window.SizeChanged += OnWindowsSizeChanged;
            window.Refreshed += OnWindowRefreshed;
            window.KeyPress += OnWindowKeyPress;
            window.MouseMoved += OnWindowMouseMoved;
            window.MouseButton += OnMouseButton;
            window.MouseLeave += OnMouseLeave;
            window.Closed += Window_Closed;
        }

        private void Window_Closed(object? sender, EventArgs e)
        {
            Console.WriteLine("CLOSE");
            //opening = false;
        }

        private  GRContext GenerateSkiaContext(NativeWindow nativeWindow)
        {
            var nativeContext = GetNativeContext(nativeWindow);
            var glInterface = GRGlInterface.AssembleGlInterface(nativeContext, (contextHandle, name) => GLFW.Glfw.GetProcAddress(name));
            return GRContext.Create(GRBackend.OpenGL, glInterface);
        }


        private  object GetNativeContext(NativeWindow nativeWindow)
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                return GLFW.Native.GetWglContext(nativeWindow);
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                // XServer
                return GLFW.Native.GetGLXContext(nativeWindow);
                // Wayland
                //return Native.GetEglContext(nativeWindow);
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                return GLFW.Native.GetNSGLContext(nativeWindow);
            }

            throw new PlatformNotSupportedException();
        }

        private  SKSurface GenerateSkiaSurface(GRContext skiaContext, Size surfaceSize)
        {
            var frameBufferInfo = new GRGlFramebufferInfo((uint)new UIntPtr(0), GRPixelConfig.Rgba8888.ToGlSizedFormat());
            var backendRenderTarget = new GRBackendRenderTarget(surfaceSize.Width,
                                                                surfaceSize.Height,
                                                                0,
                                                                8,
                                                                frameBufferInfo);
            return SKSurface.Create(skiaContext, backendRenderTarget, GRSurfaceOrigin.BottomLeft, SKImageInfo.PlatformColorType);
        }

        #region Window Events Handlers

        private void OnWindowsSizeChanged(object sender, SizeChangeEventArgs e)
        {
            OnSize(e.Size);
        }

        private void OnWindowKeyPress(object sender, KeyEventArgs e)
        {
            
        }

        private void OnWindowMouseMoved(object sender, MouseMoveEventArgs e)
        {
            lastPress = Vector2.Zero;

            mousePosition.X = (float)e.X;
            mousePosition.Y = (float)e.Y;
            Event ent = new Event();
            ent.position = mousePosition;
            ent.type = Event.Type.PointMove;
            List<Control> currentControls = new List<Control>();
            
            control.DispitchEvent(ent, ref currentControls);

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

        private void OnWindowRefreshed(object sender, EventArgs e)
        {
           
        }
        private void OnMouseButton(object? sender, MouseButtonEventArgs e)
        {
            if (controls.Count <= 0)
            {
                return;
            }
            var hit = controls.Last();

            Event ent = new Event();
            ent.position = mousePosition;
            ent.button = (int)e.Button;

            if(e.Action== InputState.Press)
            {
                ent.type = Event.Type.PointDown;
                lastPress = mousePosition;
                mouseStay = true;
            }
            else if (e.Action == InputState.Release)
            {
                if(mouseStay && lastPress== mousePosition)
                {
                    ent.type = Event.Type.PointClick;
                    hit.OnEvent(ent);
                }
                lastPress = Vector2.Zero;
                ent.type = Event.Type.PointUp;
                mouseStay = false;
            }
            hit.OnEvent(ent);
        }
        private void OnMouseLeave(object? sender, EventArgs e)
        {
            controls.Clear();
        }
        #endregion

    }
}
