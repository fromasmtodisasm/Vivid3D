using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class NewMap : Form
    {
        public int MapW, MapH, MapD;
        public int TileW, TileH;
        public NewMap()
        {
            InitializeComponent();
            MapW = 0;
            MapH = 0;
            MapD = 0;
            TileW = 0;
            TileH = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1.Main.CancelNewMap();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MapW = (int)mMapW.Value;
            MapH = (int)mMapH.Value;
            MapD = (int)mMapD.Value;
            TileW = (int)mTileW.Value;
            TileH = (int)mTileH.Value;
            Form1.Main.CreateNewMapNow();
        }
    }
}
