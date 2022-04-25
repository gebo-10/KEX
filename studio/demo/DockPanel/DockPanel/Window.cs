using System;
using System.Collections.Generic;
using System.Drawing;
using Facebook.Yoga;
using GLFW;
using SkiaSharp;
using System.Runtime.InteropServices;
namespace KUI
{
    public class Window
    {
        public NativeWindow window;
        private SKCanvas canvas;
        private GRContext context;
        private SKSurface surface;

        public Control control;
        private bool opening=false;

        public static List<Control> controls = new List<Control>();
        public Window()
        {
            control = new Control(100,100);
        }
        public void Open(int width, int height, string title)
        {
            Glfw.WindowHint(Hint.Decorated, false);
            window = new NativeWindow(width, height, title);
           
            context = GenerateSkiaContext(window);

            OnSize(new Size(width,height) );
            Render();
            SubscribeToWindowEvents();
            opening = true;
            while (opening)
            {
                Glfw.WaitEvents();
            }
        }

        public void Close()
        {
            window.Close();
            opening = false;
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
            //layout.Width = size.Width;
            //layout.Height=size.Height;
            //layout.CalculateLayout();
            control.layout.CalculateLayout();
            //control.Layout(size.Width, size.Height);
            
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
           // RenderYoga(layout);

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
            opening = false;
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

        private SKSurface GenerateSkiaSurface2(GRContext skiaContext, Size surfaceSize)
        {
            //var glInfo = new GRGlTextureInfo(0, 0);
            //var backendRenderTarget = new GRBackendTexture(surfaceSize.Width,
            //                                                    surfaceSize.Height,
            //                                                    false,
            //                                                    glInfo);
            //return SKSurface.Create(skiaContext, backendRenderTarget, GRSurfaceOrigin.BottomLeft, SKImageInfo.PlatformColorType);
            return SKSurface.Create(surfaceSize.Width, surfaceSize.Height, SKColorType.Rgba8888,SKAlphaType.Opaque);
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
            Env.x = (float)e.X;
            Env.y = (float)e.Y;
            Event ent = new Event();
            ent.x = (float)e.X;
            ent.y = (float)e.Y;
            ent.type = Event.Type.PointMove;
            List<Control> currentControls = new List<Control>();
            
            control.DispitchEvent(ent, ref currentControls);

            Event leaveEvent = new Event();
            leaveEvent.x = (float)e.X;
            leaveEvent.y = (float)e.Y;
            leaveEvent.type = Event.Type.PointLeave;
            var leave = controls.Except(currentControls);
            foreach (Control c in leave)
            {
                c.OnEvent(leaveEvent);
            }

            Event inEvent = new Event();
            inEvent.x = (float)e.X;
            inEvent.y = (float)e.Y;
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
            
            Event ent = new Event();
            ent.x = Env.x;
            ent.y = Env.x;
            ent.type = Event.Type.PointDown;
            ent.button = (int)e.Button;
            ent.action = (Event.PointAction)e.Action;
            if(controls.Count <= 0)
            {
                return;
            }
            var c=controls.Last();
            c.OnEvent(ent);
        }
        private void OnMouseLeave(object? sender, EventArgs e)
        {
            controls.Clear();
        }
        #endregion


        //private void YogaLayout()
        //{
        //    config = new YogaConfig();

        //    layout = new YogaNode(config);
        //    layout.Wrap = YogaWrap.Wrap;
        //    layout.Height = 100;


        //    YogaNode root_child0 = new YogaNode(config);
        //    root_child0.Width = 30;
        //    root_child0.Height = 30;
        //    layout.Insert(0, root_child0);

        //    YogaNode root_child1 = new YogaNode(config);
        //    root_child1.Width = 30;
        //    root_child1.Height = 30;
        //    layout.Insert(1, root_child1);
        //    layout.CalculateLayout();
        //    Console.WriteLine(root_child1.LayoutY);
        //    Console.WriteLine(root_child1.LayoutX);


        //    YogaNode root_child2 = new YogaNode(config);
        //    root_child2.Width = 30;
        //    root_child2.Height = 30;
        //    layout.Insert(2, root_child2);

        //    YogaNode root_child3 = new YogaNode(config);
        //    root_child3.Width = 30;
        //    root_child3.Height = 30;
        //    layout.Insert(3, root_child3);

        //    for (int i = 4; i < 20; i++)
        //    {
        //        YogaNode c = new YogaNode(config);
        //        c.Width = 30;
        //        c.Height = 30;

        //        layout.AddChild(c);
        //        YogaNode c1 = new YogaNode(config);
        //        c1.Width = 12;
        //        c1.Height = 12;
        //        c.AddChild(c1);

                
        //    }

        //    layout.StyleDirection = YogaDirection.LTR;
        //    layout.CalculateLayout();
        //}

        //private void RenderYoga(YogaNode layout)
        //{
        //    var headerPaint = new SKPaint { Color = SKColor.Parse("#3399EE"), Style = SKPaintStyle.Stroke, IsAntialias = true };
        //    canvas.DrawRect(layout.LayoutX, layout.LayoutY, layout.LayoutWidth, layout.LayoutHeight, headerPaint);

        //    for (int i = 0; i < layout.Count; i++)
        //    {
        //        var child = layout[i];
        //        RenderYoga(child);
        //    }
        //}

    }
}
