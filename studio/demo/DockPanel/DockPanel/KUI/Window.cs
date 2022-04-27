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
        public NativeWindow nativeWindow;
        private SKCanvas canvas;
        private GRContext context;
        private SKSurface surface;

        public Control control;
        public EventSystem eventSystem;
        public Window()
        {
            control = new Control();
            control.context = new Context();
            control.context.window = this;

            eventSystem = new EventSystem();
            eventSystem.window = this;
        }
        public void Open(int width, int height, string title, bool decorated=true,bool transparent=false)
        {
            //Glfw.WindowHint(Hint.ContextVersionMajor, 3);
            //Glfw.WindowHint(Hint.ContextVersionMinor, 3);
            //Glfw.WindowHint(Hint.OpenglProfile, Profile.Core);
            Glfw.WindowHint(Hint.Resizable, 1);
            Glfw.WindowHint(Hint.TransparentFramebuffer, transparent);
            Glfw.WindowHint(Hint.Decorated, decorated);
            nativeWindow = new NativeWindow(width, height, title);
           
            context = GenerateSkiaContext(nativeWindow);

            OnSize(new Size(width,height) );
            Render();
            SubscribeToWindowEvents();
            while (!Glfw.WindowShouldClose(nativeWindow))
            {
                Glfw.WaitEvents();
            }
        }
        public void Close()
        {
            nativeWindow.Close();
        }
        public void OnSize(Size size)
        {
            if(size.Width<=0 || size.Height<=0) return;
            control.layout.Width = (float)size.Width;
            control.layout.Height = (float)size.Height;
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
            control.layout.CalculateLayout(size.Width,size.Height);
        }
        public void Render()
        {
            canvas.Clear(SKColor.Parse("#00000000"));

            var rect = new Rect();
            rect.x = 0;
            rect.y = 0;
            rect.width =control.layout.LayoutWidth;
            rect.height = control.layout.LayoutHeight;
            control.Render(canvas, rect);

            canvas.Flush();
            
            nativeWindow.SwapBuffers();
        }
        private  void SubscribeToWindowEvents()
        {
            nativeWindow.SizeChanged += eventSystem.OnWindowsSizeChanged;
            nativeWindow.Refreshed += eventSystem.OnWindowRefreshed;
            nativeWindow.KeyPress += eventSystem.OnWindowKeyPress;
            nativeWindow.MouseMoved += eventSystem.OnWindowMouseMoved;
            nativeWindow.MouseButton += eventSystem.OnMouseButton;
            nativeWindow.MouseLeave += eventSystem.OnMouseLeave;
            nativeWindow.Closed += eventSystem.OnClose;
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


        public Vector2 Position
        {
            get
            {
                int x, y;
                Glfw.GetWindowPosition(nativeWindow, out x, out y);
                return new Vector2((float)x, (float)y);
            }
            set
            {
                Glfw.SetWindowPosition(nativeWindow, (int)(value.X), (int)(value.Y));
            }
        }
    }
}
