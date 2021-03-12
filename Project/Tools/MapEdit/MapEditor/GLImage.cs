using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System.Drawing;
namespace MapEditor
{
    public class GLImage
    {
        int ID = 0;
        public GLImage(string path)
        {
            GL.Enable(EnableCap.Texture2D);
            ID = GL.GenTexture();

            GL.BindTexture(TextureTarget.Texture2D, ID);
         
            Bitmap bm = new Bitmap(path);

            byte[] dat = new byte[bm.Width * bm.Height * 4];

            int loc = 0;
            for(int y = 0; y < bm.Height; y++)
            {
                for(int x = 0; x < bm.Width; x++)
                {
                    var pix = bm.GetPixel(x, y);

                    dat[loc++] = pix.R;
                    dat[loc++] = pix.G;
                    dat[loc++] = pix.B;
                    dat[loc++] = pix.A;

                }
            }

            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, bm.Width, bm.Height, 0, PixelFormat.Rgba, PixelType.UnsignedByte, dat);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.Repeat);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.Repeat);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);
            GL.BindTexture(TextureTarget.Texture2D, 0);
            GL.Disable(EnableCap.Texture2D);

        }

        public void Bind(int unit)
        {

            GL.ActiveTexture(TextureUnit.Texture0 + unit);
            GL.Enable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D, ID);
        }

        public void Release(int unit)
        {
            GL.ActiveTexture(TextureUnit.Texture0 + unit);
            GL.Disable(EnableCap.Texture2D);
            GL.BindTexture(TextureTarget.Texture2D,0);

        }

    }
}
