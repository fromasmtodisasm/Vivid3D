using System;
using OpenTK.Windowing.Desktop;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using OpenTK.Windowing.Common;
using System.IO;
namespace AnimPreview
{

    public class PreviewAnim : OpenTK.Windowing.Desktop.GameWindow
    {
        string Path = "C:\\Assets\\Top_Down_Survivor\\rifle\\idle\\idle1.anim";

        public PreviewAnim(GameWindowSettings ws,NativeWindowSettings nw) : base(ws,nw)
        {
         

        }
        int frames;
        int[] tex;
        protected override void OnLoad()
        {
            //base.OnLoad();

            GL.Disable(EnableCap.CullFace);
            GL.Disable(EnableCap.ScissorTest);
            GL.Disable(EnableCap.Blend);
            GL.Viewport(0, 0, this.Size.X, this.Size.Y);

            FileStream fs = new FileStream(Path, FileMode.Open, FileAccess.Read);
            BinaryReader r = new BinaryReader(fs);

            int w = r.ReadInt32();
            int h = r.ReadInt32();

            int fc = r.ReadInt32();
            int frames = fc;

            tex = new int[frames];

            Console.WriteLine("Reading Frames. W:" + w + " H:" + h + " Count:" + fc);

            for (int i = 0; i < fc; i++)
            {

                //Bitmap bm = new Bitmap(w, h);

                Console.WriteLine("Reading Frame:" + i);

                byte[] data = r.ReadBytes(w * h * 4);

                int loc = 0;

                GL.Enable(EnableCap.Texture2D);
                tex[i]=GL.GenTexture();
                GL.BindTexture(TextureTarget.Texture2D, tex[i]);

                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Nearest);
                GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter,(int) TextureMagFilter.Nearest);

                GL.TexImage2D<byte>(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, w, h, 0, PixelFormat.Rgba, PixelType.UnsignedByte, data);

                GL.BindTexture(TextureTarget.Texture2D, 0);

                /*
                for (int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {

                        int cr = (int)data[loc++];
                        int cg = (int)data[loc++];
                        int cb = (int)data[loc++];
                        int ca = (int)data[loc++];

                       // Color c = Color.FromArgb(ca, cr, cg, cb);

                        //bm.SetPixel(x, y, c);
                    }
                }
                */
                //maps.Add(bm);


                Console.WriteLine("Read frame:" + i);

                GC.Collect();

            }

            r.Close();
            fs.Close();


        }

        int fn = 0;
        int lt = Environment.TickCount;
        protected override void OnRenderFrame(FrameEventArgs args)
        {
            //base.OnRenderFrame(args);
            GL.ClearColor(0, 1, 1, 1);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            int nt = Environment.TickCount;

            if (nt > (lt + 35))
            {
                lt = nt;
                fn += 1;
                if (fn >= tex.Length)
                {
                    fn = 0;
                }
            }

            //GL.Color4(255, 1, 1, 1);


            GL.Enable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D, tex[fn]);
            //tex[0]




            GL.Color4((float)1, 1, 1, 1);
            
            GL.LoadIdentity();

            GL.Ortho(0, Size.X, Size.Y, 0, -1, 1);

            GL.Begin(BeginMode.Quads);

            GL.TexCoord2(0, 0);
            GL.Vertex2(0, 0);

            GL.TexCoord2(1, 0);
            GL.Vertex2(Size.X, 0);

            GL.TexCoord2(1, 1);
            GL.Vertex2(Size.X, Size.Y);

            GL.TexCoord2(0, 1);
            GL.Vertex2(0, Size.Y);

            GL.End();
            
            SwapBuffers();


        }

    } 

    class Program
    {

        public 

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            GameWindowSettings ws = GameWindowSettings.Default;
            NativeWindowSettings nw = NativeWindowSettings.Default;
            nw.API = ContextAPI.OpenGL;

            //nw.APIVersion = new Version20();
            nw.AutoLoadBindings = true;
            nw.Flags = ContextFlags.Debug;
            nw.Profile = ContextProfile.Compatability;
            //nw.

            nw.Size = new OpenTK.Mathematics.Vector2i(800, 600);
            var app = new PreviewAnim(ws, nw);

            app.Run();

        }
    }
}
