using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace MapEditor
{
    public class MapInfo
    {
        public int TileX, TileY;
        public List<GameTile> Tiles = new List<GameTile>();
    }
    public class GameMap
    {

        public int Width, Height, Depth;
        public int TileW, TileH;
        GLImage NoTile;

        public float CamX, CamY;

        public bool[,] Highlight;


        public GameMap(int w,int h,int d,int tw,int th)
        {
            CamX = CamY = 0;
            Width = w;
            Height = h;
            Depth = d;
            TileW = tw;
            TileH = th;
            NoTile = new GLImage("data/map/notile.png");
            Highlight = new bool[Width, Height];
            for(int y = 0; y < Height; y++)
            {
                for(int x = 0; x < Width; x++)
                {

                    Highlight[x, y] = false;

                }
            }
        }
        public void ClearHighlight()
        {
            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {

                    Highlight[x, y] = false;

                }
            }

        }

        public void SetHighlight(int x,int y)
        {

            Highlight[x, y] = true;

        }

        public MapInfo GetInfoAt(int mx,int my)
        {

            MapInfo info = new MapInfo();

            for (int y = 0; y < Height; y++)
            {
                for (int x = 0; x < Width; x++)
                {

                    int rX = x * TileW;
                    int rY = y * TileH;

                    rX = rX - (int)CamX;
                    rY = rY - (int)CamY;

                    if(mx>=rX && mx<=(rX+TileW) && my>=rY && my <= (rY + TileH))
                    {

                        info.TileX = x;
                        info.TileY = y;

                        return info;

                    }
                 


                }
            }

            return null;
        }

        public void Render()
        {

            NoTile.Bind(0);

            GL.Begin(BeginMode.Quads);

            GL.Color4((float)1, (float)1, (float)1, (float)1);

            for(int y = 0; y < Height; y++)
            {
                for(int x = 0; x < Width; x++)
                {

                    int rX = x * TileW;
                    int rY = y * TileH;

                    rX = rX - (int)CamX;
                    rY = rY - (int)CamY;

                    if(Highlight[x,y])
                    {
                        GL.Color4((float)1, 0, 0, 1);
                    }
                    else
                    {
                        GL.Color4((float)1, 1, 1, 1);
                    }

                    GL.TexCoord2((float)0, 0);
                    GL.Vertex2(rX, rY);
                    GL.TexCoord2((float)1, 0);
                    GL.Vertex2(rX + TileW, rY);
                    GL.TexCoord2((float)1, 1);
                    GL.Vertex2(rX + TileW, rY + TileH);
                    GL.TexCoord2((float)0, 1);
                    GL.Vertex2(rX, rY + TileH);


                }
            }

            GL.End();

            NoTile.Release(0);

        }

    }
}
