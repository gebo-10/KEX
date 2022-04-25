using KUI;
using Facebook.Yoga;
var w = new Window();

w.control.layout.Wrap = YogaWrap.Wrap;
w.control.layout.FlexDirection = YogaFlexDirection.Row;
//w.control.layout.StyleDirection = YogaDirection.LTR;
for (int i = 0; i < 2; i++)
{
    var c1 = new Control(40+i*5, 40 + i * 5);
    w.control.AddChild(c1);
    c1.id = i+1;
    //c1.layout.Wrap = YogaWrap.Wrap;
    c1.layout.AlignItems = YogaAlign.Center;
    c1.layout.JustifyContent = YogaJustify.Center;
    //c1.layout.FlexDirection = YogaFlexDirection.Row;
    c1.layout.Margin = 10;
    {
        var c2 = new Control(50, 50);
        c2.id = i + 1 + 100;
        c1.AddChild(c2);

        var c21 = new Control(20, 20);
        c2.id = i + 1 + 100+2000;
        c2.AddChild(c21);
    }
    {
        var c2 = new Control(10, 10);
        c2.id = i + 1 + 100 + 1000;
        c1.AddChild(c2);

        //c2.layout.Display = YogaDisplay.None;
    }

}
w.Open(500, 500, "haha");

//namespace Glfw.Skia
//{
//    using System;
//    using System.Drawing;
//    using System.Runtime.InteropServices;
//    using Facebook.Yoga;
//    using GLFW;
//    using SkiaSharp;

//    class Program
//    {
//        private static NativeWindow window;
//        private static SKCanvas canvas;

//        private static Keys? lastKeyPressed;
//        private static Point? lastMousePosition;

//        //----------------------------------
//        //NOTE: On Windows you must copy SharedLib manually (https://github.com/ForeverZer0/glfw-net#microsoft-windows)
//        //----------------------------------

//        private static YogaConfig config;
//        private static YogaNode root;

//        static void Main(string[] args)
//        {
//            using (Program.window = new NativeWindow(1800, 600, "Skia Example"))
//            {
//                Program.SubscribeToWindowEvents();

//                using (var context = Program.GenerateSkiaContext(Program.window))
//                {
//                    using (var skiaSurface = Program.GenerateSkiaSurface(context, Program.window.ClientSize))
//                    {
//                        Program.canvas = skiaSurface.Canvas;
//                        YogaLayout();
//                        while (!Program.window.IsClosing)
//                        {
//                            Program.Render();
//                            Glfw.WaitEvents();
//                        }
//                    }
//                }
//            }
//        }

//        private static void SubscribeToWindowEvents()
//        {
//            Program.window.SizeChanged += Program.OnWindowsSizeChanged;
//            Program.window.Refreshed += Program.OnWindowRefreshed;
//            Program.window.KeyPress += Program.OnWindowKeyPress;
//            Program.window.MouseMoved += Program.OnWindowMouseMoved;
//        }

//        private static GRContext GenerateSkiaContext(NativeWindow nativeWindow)
//        {
//            var nativeContext = Program.GetNativeContext(nativeWindow);
//            var glInterface = GRGlInterface.AssembleGlInterface(nativeContext, (contextHandle, name) => Glfw.GetProcAddress(name));
//            return GRContext.Create(GRBackend.OpenGL, glInterface);
//        }

//        private static object GetNativeContext(NativeWindow nativeWindow)
//        {
//            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
//            {
//                return GLFW.Native.GetWglContext(nativeWindow);
//            }
//            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
//            {
//                // XServer
//                return GLFW.Native.GetGLXContext(nativeWindow);
//                // Wayland
//                //return Native.GetEglContext(nativeWindow);
//            }
//            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
//            {
//                return GLFW.Native.GetNSGLContext(nativeWindow);
//            }

//            throw new PlatformNotSupportedException();
//        }

//        private static SKSurface GenerateSkiaSurface(GRContext skiaContext, Size surfaceSize)
//        {
//            var frameBufferInfo = new GRGlFramebufferInfo((uint)new UIntPtr(0), GRPixelConfig.Rgba8888.ToGlSizedFormat());
//            var backendRenderTarget = new GRBackendRenderTarget(surfaceSize.Width,
//                                                                surfaceSize.Height,
//                                                                0,
//                                                                8,
//                                                                frameBufferInfo);
//            return SKSurface.Create(skiaContext, backendRenderTarget, GRSurfaceOrigin.BottomLeft, SKImageInfo.PlatformColorType);
//        }

//        private static void Render()
//        {
//            Program.canvas.Clear(SKColor.Parse("#F0F0F0"));

//            RenderYoga();

//            //var headerPaint = new SKPaint { Color = SKColor.Parse("#333333"), TextSize = 50, IsAntialias = true };
//            //Program.canvas.DrawText("Hello from GLFW.NET + SkiaSharp!", 10, 60, headerPaint);

//            //var inputInfoPaint = new SKPaint { Color = SKColor.Parse("#F34336"), TextSize = 18, IsAntialias = true };
//            //Program.canvas.DrawText($"Last key pressed: {Program.lastKeyPressed}", 10, 90, inputInfoPaint);
//            //Program.canvas.DrawText($"Last mouse position: {Program.lastMousePosition}", 10, 120, inputInfoPaint);

//            //var exitInfoPaint = new SKPaint { Color = SKColor.Parse("#3F51B5"), TextSize = 18, IsAntialias = true };
//            //Program.canvas.DrawText("Press Enter to Exit.", 10, 160, exitInfoPaint);

//            Program.canvas.Flush();
//            Program.window.SwapBuffers();
//        }

//        #region Window Events Handlers

//        private static void OnWindowsSizeChanged(object sender, SizeChangeEventArgs e)
//        {
//            root.Width= e.Size.Width;
//            root.Height= e.Size.Height;
//            root.CalculateLayout();
//            Program.Render();
//        }

//        private static void OnWindowKeyPress(object sender, KeyEventArgs e)
//        {
//            Program.lastKeyPressed = e.Key;
//            if (e.Key == Keys.Enter || e.Key == Keys.NumpadEnter)
//            {
//                Program.window.Close();
//            }
//        }

//        private static void OnWindowMouseMoved(object sender, MouseMoveEventArgs e)
//        {
//            Program.lastMousePosition = e.Position;
//        }

//        private static void OnWindowRefreshed(object sender, EventArgs e)
//        {
//            Program.Render();
//        }

//        #endregion


//        private static void YogaLayout()
//        {
//            config = new YogaConfig();

//            root = new YogaNode(config);
//            root.Wrap = YogaWrap.Wrap;
//            root.Height = 100;


//            YogaNode root_child0 = new YogaNode(config);
//            root_child0.Width = 30;
//            root_child0.Height = 30;
//            root.Insert(0, root_child0);

//            YogaNode root_child1 = new YogaNode(config);
//            root_child1.Width = 30;
//            root_child1.Height = 30;
//            root.Insert(1, root_child1);

//            YogaNode root_child2 = new YogaNode(config);
//            root_child2.Width = 30;
//            root_child2.Height = 30;
//            root.Insert(2, root_child2);

//            YogaNode root_child3 = new YogaNode(config);
//            root_child3.Width = 30;
//            root_child3.Height = 30;
//            root.Insert(3, root_child3);
//            root.StyleDirection = YogaDirection.LTR;
//            root.CalculateLayout();
//        }

//        private static void RenderYoga()
//        {
//            var headerPaint = new SKPaint { Color = SKColor.Parse("#333333"), Style = SKPaintStyle.Stroke, IsAntialias = true };
//            Program.canvas.DrawRect(root.LayoutX, root.LayoutY, root.LayoutWidth, root.LayoutHeight, headerPaint);

//            for(int i = 0; i < root.Count; i++)
//            {
//                var child = root[i];
//                Program.canvas.DrawRect(child.LayoutX, child.LayoutY, child.LayoutWidth, child.LayoutHeight, headerPaint);
//            }
//        }
//    }
//}