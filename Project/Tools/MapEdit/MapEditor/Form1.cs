using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;
using System.IO;
namespace MapEditor
{
    public partial class Form1 : Form
    {
        public enum EditMode
        {
            Paste,Line,Rect,Fill,Clear,SmartRect,SmartPaste
        }
        public static EditMode EMode = EditMode.Paste;
        public static Form1 Main;
        public static NewMap NewMapForm;
        public static GameMap CurMap = null;
        public static string ContentPath = "C:\\Content\\";
        public List<ContentEntry> Contents = new List<ContentEntry>();
        public ContentEntry ActiveEntry = null;
        public bool MoveMap = false;
        Bitmap FolderImg, FileImg;
        GLImage FolderI, FileI;
        public Form1()
        {
            InitializeComponent();
            Main = this;
            FolderImg = new Bitmap("data/content/foldericon.png");
            FileImg = new Bitmap("data/content/fileicon.png");

            ScanContent();
            Invalidate();
            toolStrip1.Invalidate();
        }



        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }

        public void UpdateStatusBar()
        {
            string st = "Edit Mode:";

            switch (EMode)
            {
                case EditMode.Paste:
                    st = st + "Paste";
                    break;
                case EditMode.Line:
                    st = st + "Line";
                    break;
                case EditMode.Rect:
                    st = st + "Rect";
                    break;
                case EditMode.Clear:
                    st = st + "Clear";
                    break;
                case EditMode.Fill:
                    st = st + "Fill";
                    break;
                case EditMode.SmartRect:
                    st = st + "Smart Rect";
                    break;
                case EditMode.SmartPaste:
                    st = st + "Smart Paste";
                    break;
            }

            status1.Text = st;
            status1.Invalidate();
        }

        private void glControl1_Load_1(object sender, EventArgs e)
        {
            glControl1.MakeCurrent();
            GL.Disable(EnableCap.Blend);
            GL.Disable(EnableCap.ScissorTest);
            GL.Disable(EnableCap.CullFace);
            GL.Viewport(0, 0, glControl1.Width, glControl1.Height);
        }

        private void glControl1_Paint_1(object sender, PaintEventArgs e)
        {
            glControl1.MakeCurrent();
            GL.ClearColor(1, 0, 0, 1);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            //base.OnPaint(e);

            GL.LoadIdentity();
            GL.Ortho(0, glControl1.Width, glControl1.Height, 0, -1, 1);

            if (CurMap != null)
            {

                CurMap.Render();

            }

            glControl1.SwapBuffers();
            glControl1.Invalidate();
        }

        private void glControl1_Resize(object sender, EventArgs e)
        {
            GL.Viewport(0, 0, glControl1.Width, glControl1.Height);
        }

        void CreateNewMap()
        {
            NewMapForm = new NewMap();
            NewMapForm.Show();

        }

        public void CancelNewMap()
        {

            NewMapForm.Close();
            NewMapForm = null;

        }

        public void CreateNewMapNow()
        {
            CurMap = new GameMap(NewMapForm.MapW, NewMapForm.MapH, NewMapForm.MapD, NewMapForm.TileW, NewMapForm.TileH);
            NewMapForm.Close();
            NewMapForm = null;

        }


        private void newMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CreateNewMap();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            CreateNewMap();
        }

        private void glControl1_MouseDown(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {

                MoveMap = true;
                FirstMove = true;

            }
        }

        private void glControl1_MouseUp(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Right)
            {
                MoveMap = false;
            }
        }

        private void glControl1_MouseMove(object sender, MouseEventArgs e)
        {
            if (CurMap == null) return;
            if (MoveMap)
            {
                if (FirstMove)
                {
                    FirstMove = false;
                    LastX = e.X;
                    LastY = e.Y;
                }
                CurMap.CamX -= e.X - LastX;
                CurMap.CamY -= e.Y - LastY;
                LastX = e.X;
                LastY = e.Y;


            }

            MapInfo info = CurMap.GetInfoAt(e.X, e.Y);
            if (info == null) return;
            CurMap.ClearHighlight();
            CurMap.SetHighlight(info.TileX, info.TileY);

        }

        public int LastX, LastY;

        private void toolStripButton7_Click(object sender, EventArgs e)
        {
            EMode = EditMode.Paste;
            UpdateStatusBar();
        }

        private void toolStripButton8_Click(object sender, EventArgs e)
        {
            EMode = EditMode.Line;
            UpdateStatusBar();
        }

        private void toolStripButton9_Click(object sender, EventArgs e)
        {
            EMode = EditMode.Rect;
            UpdateStatusBar();
        }

        private void toolStripButton10_Click(object sender, EventArgs e)
        {
            EMode = EditMode.Fill;
            UpdateStatusBar();
        }

        private void toolStripButton11_Click(object sender, EventArgs e)
        {
            EMode = EditMode.Clear;
            UpdateStatusBar();
        }

        private void toolStripButton12_Click(object sender, EventArgs e)
        {
            EMode = EditMode.SmartRect;
            UpdateStatusBar();
        }

    
        public void ScanContent()
        {
            Contents.Clear();
            foreach(var folder in new DirectoryInfo(ContentPath).GetDirectories())
            {

                var ne = new ContentEntry();
                ne.FullPath = folder.FullName;
                ne.LocalPath = folder.Name;
                ne.Folder = true;
                Contents.Add(ne);


            }
            foreach(var file in new DirectoryInfo(ContentPath).GetFiles())
            {
                var ne = new ContentEntry();
                ne.FullPath = file.FullName;
                ne.LocalPath = file.Name;
                Contents.Add(ne);
            }

            //contentBrowser2.Invalidate();
            //  contentBrowser2.Refresh();
            glControl2.Refresh();
            
        }

      

        private void contentBrowser2_MouseMove(object sender, MouseEventArgs e)
        {
            int rx, ry;
            rx = 5;
            ry = 5;
            //ActiveEntry = null;
            ContentEntry pe = ActiveEntry;
            ActiveEntry = null;
            foreach (var en in Contents)
            {

                if (e.X >= rx && e.X <= (rx + 64) && e.Y >= ry && e.Y <= (ry + 64))
                {
                    if (en != pe)
                    {
                        ActiveEntry = en;
                        contentBrowser2.Refresh();
                        //contentBrowser2.Invalidate();

                        return;
                    }
                    //Form1.Main.Invalidate();
                    //contentBrowser2.Invalidate();
                    //Console.WriteLine("Invalidated!");
                    

                }

                rx = rx + 64;
                if (rx >= contentBrowser2.Width - 64)
                {
                    rx = 5;
                    ry = ry + 64;
                }

            }
            //contentBrowser2.Invalidate();
          //  contentBrowser2.Refresh();

        }

        Bitmap ContentBM = null;
        private void contentBrowser2_Paint(object sender, PaintEventArgs e)
        {
            if (ContentBM == null || ContentBM.Width != contentBrowser2.Width || ContentBM.Height !=contentBrowser2.Height)
            {

                ContentBM = new Bitmap(contentBrowser2.Width, contentBrowser2.Height);

            }
            else
            {
                
            }

            int rx, ry;
            rx = 5;
            ry = 5;


            using (Graphics gr = Graphics.FromImage(ContentBM))
            {
                gr.FillRectangle(Brushes.DarkGray, new Rectangle(0, 0, ContentBM.Width, ContentBM.Height));
                foreach (var en in Contents)
                {
                    if (en == ActiveEntry)
                    {

                        gr.DrawRectangle(Pens.White, new Rectangle(rx, ry, 64, 64));

                    }
                    if (en.Folder)
                    {

                        gr.DrawImage(FolderImg, new Rectangle(rx, ry, 44, 44));

                    }
                    else
                    {
                        gr.DrawImage(FileImg, new Rectangle(rx, ry, 44, 44));
                    }

                    gr.DrawString(en.LocalPath, SystemFonts.DefaultFont, Brushes.White, rx, ry + 45);

                    rx = rx + 64;
                    if (rx >= contentBrowser2.Width - 64)
                    {
                        rx = 5;
                        ry = ry + 64;
                    }

                }
            }
            //    contentBrowser2.Invalidate();
            e.Graphics.DrawImage(ContentBM, new Point(0, 0));
        }

        private void contentBrowser2_Load(object sender, EventArgs e)
        {
            ScanContent();
            DoubleBuffered = true;
        }

        private void contentBrowser2_Resize(object sender, EventArgs e)
        {
            contentBrowser2.Refresh();
        }

        private void contentBrowser2_DoubleClick(object sender, EventArgs e)
        {
            if (ActiveEntry != null)
            {
                if (ActiveEntry.Folder)
                {

                    ContentPath = ActiveEntry.FullPath;
                    ScanContent();


                }
            }
        }

        private void glControl2_Load(object sender, EventArgs e)
        {
            glControl2.MakeCurrent();
            FolderI = new GLImage("data/content/foldericon.png");
            FileI = new GLImage("data/content/fileicon.png");
            ScanContent();
            glControl2.Invalidate();
        }

        private void glControl2_MouseMove(object sender, MouseEventArgs e)
        {
            int rx = 5;
            int ry = 5;

            //GL.Begin(BeginMode.Quads);
            ContentEntry pe = ActiveEntry;

            foreach (var entry in Contents)
            {

                if(e.X>=rx && e.X<=(rx+64) && e.Y>=ry && e.Y <= (ry + 64))
                {

                    ActiveEntry = entry;

                }

                rx = rx + 64;
                if (rx > glControl2.Width - 64)
                {
                    rx = 5;
                    ry = ry + 64;
                }

            }
          

                glControl2.Invalidate();
            glControl2.Invalidate();
            glControl2.Refresh();

        }

        private void glControl2_Resize(object sender, EventArgs e)
        {
            glControl2.Invalidate();
            glControl2.Refresh();
        }

        private void glControl2_Paint(object sender, PaintEventArgs e)
        {

            int rx = 5;
            int ry = 5;

            glControl2.MakeCurrent();

            GL.ClearColor((float)0.25f, 0.25f,0.25f, 1);

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            GL.LoadIdentity();
            GL.Ortho(0, glControl2.Width, glControl2.Height, 0, -1, 1);
            GL.Viewport(0, 0, glControl2.Width, glControl2.Height);
            GL.Disable(EnableCap.ScissorTest);
            GL.Enable(EnableCap.Blend);
            GL.BlendFunc(BlendingFactor.SrcAlpha, BlendingFactor.OneMinusSrcAlpha);
            //GL.Begin(BeginMode.Quads);


            foreach (var entry in Contents)
            {

                if (entry.Folder)
                {


                    if(entry == ActiveEntry)
                    {
                        Console.WriteLine("Folder!");

                        G.DrawImage(rx - 2, ry -2, 52, 52, FolderI);

                    }
                    G.DrawImage(rx, ry, 48, 48, FolderI);

                }
                else
                {
                    if(entry == ActiveEntry)
                    {

                        G.DrawImage(rx - 2, ry - 2, 52, 52, FileI);

                    }

                    G.DrawImage(rx, ry, 48,48, FileI);

                }

                rx = rx + 64;
                if (rx > glControl2.Width - 64)
                {
                    rx = 5;
                    ry = ry + 64;
                }

            }

            //GL.End();

            glControl2.SwapBuffers();
            glControl2.Invalidate();
            glControl2.Invalidate();
            this.Invalidate();
        }

        private void contentBrowser1_Paint(object sender, PaintEventArgs e)
        {

        }

        bool FirstMove = true;
    }
}
