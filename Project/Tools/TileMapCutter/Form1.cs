using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileMapCutter
{
    public partial class Form1 : Form
    {
        public string TileSheetPath = "";
        public int TileW, TileH;
        public string OutputPath = "";
        public string OutputFile = "";
        public Form1()
        {
            InitializeComponent();
            TileW = 64;
            TileH = 64;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            textBox1.Text = openFileDialog1.FileName;
            TileSheetPath = openFileDialog1.FileName;
        }

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            TileH = (int)numericUpDown2.Value;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.ShowDialog();
            textBox2.Text = folderBrowserDialog1.SelectedPath;
            OutputPath = textBox2.Text;
            OutputPath = OutputPath + "\\";
       

        }

        private void button3_Click(object sender, EventArgs e)
        {

            if (OutputPath == "") return;
            if (TileSheetPath == "") return;
            if (OutputFile == "") return;
            Bitmap bit = new Bitmap(TileSheetPath);
            if(bit==null)
            {
                MessageBox.Show("Unable to open tile sheet.");
            }

            int sx, sy;
            sx = 0;
            sy = 0;

            int outc = 0;
            while (true)
            {

                Bitmap ntile = new Bitmap(TileW, TileH);

                for (int ty = sy; ty < sy + TileH; ty++)
                {
                    for (int tx = sx; tx < sx + TileW; tx++)
                    {
                        int nx = tx - sx;
                        int ny = ty - sy;

                        var pix = bit.GetPixel(tx, ty);

                        ntile.SetPixel(nx, ny, pix);


                    }
                }
                ntile.Save(OutputPath + OutputFile + outc + ".png", System.Drawing.Imaging.ImageFormat.Png);

                outc++;
                sx += TileW;
                if (sx >= bit.Width)
                {
                    sx = 0;
                    sy += TileH;
                    if (sy >= bit.Height)
                    {
                        break;
                    }
                }

            }
            MessageBox.Show("Tiles generated. Count:" + outc);

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            OutputFile = textBox3.Text;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            OutputPath = textBox2.Text;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            TileSheetPath = textBox1.Text;
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            TileW = (int)numericUpDown1.Value;
        }
    }
}
