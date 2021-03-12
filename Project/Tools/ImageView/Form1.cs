using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace ImageView
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            string path = openFileDialog1.FileName;

            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            BinaryReader r = new BinaryReader(fs);

            int w = r.ReadInt32();
            int h = r.ReadInt32();
            int alpha = r.ReadByte();
            bool al = false;
            if (alpha == 1)
            {
                al = true;
            }
            int bpp = 3;
            if (al)
            {
                bpp = 4;
            }

            int bl = w * h * bpp;
            byte[] dat = r.ReadBytes(bl);

            Bitmap lm = new Bitmap(w, h);
            for(int y = 0; y < h; y++)
            {
                for(int x = 0; x < w; x++)
                {
                    int loc = (y * w * bpp) + x * bpp;
                    byte cr = dat[loc++];
                    byte cg = dat[loc++];
                    byte cb = dat[loc++];
                    if (al)
                    {
                        loc++;
                    }
                    lm.SetPixel(x, y, Color.FromArgb(cr, cg, cb));
                }
            }

            //Bitmap nm = new Bitmap(path);

            Bitmap nm = new Bitmap(lm, new Size(panel1.Width, panel1.Height));
            panel1.BackgroundImage = nm;



        }
    }
}
