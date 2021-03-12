using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public class GameTile
    {
        public GLImage Image;
        public bool CastShadows = false;
        public bool Collider = false;
        public GameTile(GLImage img)
        {

            Image = img;

        }

    }
}
