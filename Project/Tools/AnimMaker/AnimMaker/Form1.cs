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
namespace AnimMaker
{
    public partial class Form1 : Form
    {
        public string FolderPath = "";
        public string FileName = "";
        public int Start, End;
        public string Output = "";
        public bool HalfRes = false;
        public Form1()
        {
            InitializeComponent();
            Start = End = 0;
        
        }

        string GetNum(int num)
        {
            string f = num.ToString();

            int zc = 4-f.Length;

            string fin = "";
            for(int i = 0; i < zc; i++)
            {
                fin = fin + "0";
            }
            fin = fin + f;
            return fin;


        }

        string GetName(int num)
        {
            if (checkBox2.Checked)
            {
                return FileName + GetNum(num) + ".png";
            }
            return FileName + num.ToString() + ".png";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            FileName = fileNameBox.Text;
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            Start = int.Parse(textBox3.Text);

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            End = int.Parse(textBox4.Text);
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            Output = FolderPath + textBox5.Text + ".anim";

        }

        private void button2_Click(object sender, EventArgs e)
        {

            FileStream fs = new FileStream(Output, FileMode.Create, FileAccess.Write);
            BinaryWriter w = new BinaryWriter(fs);

            Bitmap fm = new Bitmap(FolderPath + GetName(Start));

            int fw = fm.Width;
            int fh = fm.Height;

            if (HalfRes)
            {
                w.Write(fw / 2);
                w.Write(fh / 2);
            }
            else
            {

                w.Write(fw);
                w.Write(fh);
            }
            w.Write(End - Start);

            byte[] data;
            if (HalfRes)
            {
                data = new byte[(fw / 2) * (fh / 2) * 4];
            }
            else
            {


                data = new byte[fw * fh * 4];
            }
            for(int f = Start; f < End; f++)
            {
                Console.WriteLine("Writing Frame:" + f + " Which is Frame:" + (f - Start));
                fm = new Bitmap(FolderPath + GetName(f));

                if (HalfRes)
                {
                    fm = new Bitmap(fm, new Size(fw / 2, fh / 2));
                }

                int loc = 0;

                int ww = fw;
                int hh = fh;

                if (HalfRes)
                {
                    ww = ww / 2;
                    hh = hh / 2;
                }

                for(int y = 0; y < hh; y++)
                {
                    for(int x = 0; x < ww; x++)
                    {

                        var pix = fm.GetPixel(x, y);
                        data[loc++] = pix.R;
                        data[loc++] = pix.G;
                        data[loc++] = pix.B;
                        data[loc++] = pix.A;

                    }
                }

                w.Write(data);

                Console.WriteLine("Wrote Frame:" + f + "/" + End);

                GC.Collect();
            }

            w.Flush();
            fs.Flush();
            w.Close();
            fs.Close();


        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            HalfRes = checkBox1.Checked;
        }

        private void button1_Click(object sender, EventArgs e)
        {

            folderBrowserDialog1.ShowDialog();
            FolderPath = folderBrowserDialog1.SelectedPath+"\\";
            textBox1.Text = FolderPath;
            Console.WriteLine("Selected path:" + FolderPath);
        }
    }
}
