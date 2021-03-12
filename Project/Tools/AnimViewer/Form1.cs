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

namespace AnimViewer
{
    public partial class Form1 : Form
    {

        public List<Bitmap> maps = new List<Bitmap>();
        public string Anim = "";
        int frame = 0;
        int frames = 0;
        Bitmap curframe;

        public Form1()
        {
            InitializeComponent();
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            Anim = openFileDialog1.FileName;
            maps.Clear();

            FileStream fs = new FileStream(Anim, FileMode.Open, FileAccess.Read);
            BinaryReader r = new BinaryReader(fs);

            int w = r.ReadInt32();
            int h = r.ReadInt32();

            int fc = r.ReadInt32();
            frames = fc;

            Console.WriteLine("Reading Frames. W:" + w + " H:" + h+" Count:"+fc);

            for(int i = 0; i < fc; i++)
            {

                Bitmap bm = new Bitmap(w, h);

                Console.WriteLine("Reading Frame:" + i);

                byte[] data = r.ReadBytes(w * h * 4);

                int loc = 0;
                for(int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {

                        int cr = (int)data[loc++];
                        int cg = (int)data[loc++];
                        int cb = (int)data[loc++];
                        int ca = (int)data[loc++];

                        Color c = Color.FromArgb(ca, cr, cg, cb);

                        bm.SetPixel(x, y, c);
                    }
                }

                maps.Add(bm);

                Console.WriteLine("Read frame:" + i);

                GC.Collect();

            }

            r.Close();
            fs.Close();

        }

        private void button2_Click(object sender, EventArgs e)
        {
            frame = 0;
            curframe = maps[0];
            timer2.Enabled = true;
        }

        Image cimg;

        private void timer2_Tick(object sender, EventArgs e)
        {
            frame++;
            if (frame >= frames)
            {
                frame = 0;
                Console.WriteLine("!!!!!!!!!!!!!!!!!!!!!!!!!!");
            }
            curframe = maps[frame];
            panel1.Invalidate();

            //Bitmap nm = new Bitmap(curframe, new Size(panel1.Width, panel1.Height));


            //panel1.BackgroundImage = nm;
            //panel1.Invalidate();
            //cimg = new Image(nm);

            Console.WriteLine("frame:"+frame);

        }

        private void button3_Click(object sender, EventArgs e)
        {
            timer2.Enabled = false;
            curframe = maps[0];
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            if (curframe == null) return;
            e.Graphics.DrawImage(curframe, new Rectangle(0, 0, panel1.Width, panel1.Height));
        }
    }
}
