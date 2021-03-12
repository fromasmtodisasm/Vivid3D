using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace MapEditor
{
    public class G
    {

        public static void DrawImage(int x,int y,int w,int h,GLImage img,float r= 1,float g=1,float b=1,float a=1)
        {
            GL.Color4(r, g, b, a);
            img.Bind(0);
            GL.Begin(BeginMode.Quads);

            GL.TexCoord2(0, 0);
            GL.Vertex2(x, y);
            GL.TexCoord2(1, 0);
            GL.Vertex2(x + w, y);
            GL.TexCoord2(1, 1);
            GL.Vertex2(x + w, y + h);
            GL.TexCoord2(0, 1);
            GL.Vertex2(x, y + h);
            GL.End();
            img.Release(0);

            

        }

    }
}
