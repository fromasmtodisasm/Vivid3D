
namespace MapEditor
{
    partial class NewMap
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.mMapW = new System.Windows.Forms.NumericUpDown();
            this.mMapH = new System.Windows.Forms.NumericUpDown();
            this.mTileW = new System.Windows.Forms.NumericUpDown();
            this.mTileH = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.mMapD = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.mMapW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mMapH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mTileW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mTileH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mMapD)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Width";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(204, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "Height";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(204, 42);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 17);
            this.label3.TabIndex = 3;
            this.label3.Text = "TileH";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 42);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 17);
            this.label4.TabIndex = 2;
            this.label4.Text = "TileW";
            // 
            // mMapW
            // 
            this.mMapW.Increment = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.mMapW.Location = new System.Drawing.Point(62, 7);
            this.mMapW.Name = "mMapW";
            this.mMapW.Size = new System.Drawing.Size(120, 22);
            this.mMapW.TabIndex = 4;
            this.mMapW.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            // 
            // mMapH
            // 
            this.mMapH.Increment = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.mMapH.Location = new System.Drawing.Point(259, 9);
            this.mMapH.Name = "mMapH";
            this.mMapH.Size = new System.Drawing.Size(120, 22);
            this.mMapH.TabIndex = 5;
            this.mMapH.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            // 
            // mTileW
            // 
            this.mTileW.Increment = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.mTileW.Location = new System.Drawing.Point(62, 42);
            this.mTileW.Name = "mTileW";
            this.mTileW.Size = new System.Drawing.Size(120, 22);
            this.mTileW.TabIndex = 6;
            this.mTileW.Value = new decimal(new int[] {
            64,
            0,
            0,
            0});
            // 
            // mTileH
            // 
            this.mTileH.Increment = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.mTileH.Location = new System.Drawing.Point(259, 40);
            this.mTileH.Name = "mTileH";
            this.mTileH.Size = new System.Drawing.Size(120, 22);
            this.mTileH.TabIndex = 7;
            this.mTileH.Value = new decimal(new int[] {
            64,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(395, 12);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(46, 17);
            this.label5.TabIndex = 8;
            this.label5.Text = "Depth";
            // 
            // mMapD
            // 
            this.mMapD.Location = new System.Drawing.Point(447, 12);
            this.mMapD.Name = "mMapD";
            this.mMapD.Size = new System.Drawing.Size(120, 22);
            this.mMapD.TabIndex = 9;
            this.mMapD.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(307, 96);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(134, 23);
            this.button1.TabIndex = 10;
            this.button1.Text = "Create";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(448, 96);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(129, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // NewMap
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(589, 131);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.mMapD);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.mTileH);
            this.Controls.Add(this.mTileW);
            this.Controls.Add(this.mMapH);
            this.Controls.Add(this.mMapW);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "NewMap";
            this.Text = "New Map Properties";
            ((System.ComponentModel.ISupportInitialize)(this.mMapW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mMapH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mTileW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mTileH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mMapD)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown mMapW;
        private System.Windows.Forms.NumericUpDown mMapH;
        private System.Windows.Forms.NumericUpDown mTileW;
        private System.Windows.Forms.NumericUpDown mTileH;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown mMapD;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}