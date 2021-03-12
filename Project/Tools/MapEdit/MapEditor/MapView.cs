using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;
namespace MapEditor
{
    public class MapView : GLControl
    {
        protected override void OnLoad(EventArgs e)
        {
            //base.OnLoad(e);
            GL.Disable(EnableCap.Blend);
            GL.Disable(EnableCap.ScissorTest);
            GL.Disable(EnableCap.CullFace);
            GL.Viewport(0, 0, Width, Height);

        }
        protected override void OnPaint(PaintEventArgs e)
        {
            GL.ClearColor(1, 0, 0, 1);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            //base.OnPaint(e);
            SwapBuffers();

        }
    }
}
