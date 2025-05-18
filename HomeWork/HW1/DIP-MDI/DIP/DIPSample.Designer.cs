namespace DIP
{
    partial class DIPSample
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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.stStripLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.iPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rGBtoGrayToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.oFileDlg = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.antiWhiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stStripLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 437);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Padding = new System.Windows.Forms.Padding(1, 0, 19, 0);
            this.statusStrip1.Size = new System.Drawing.Size(876, 26);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // stStripLabel
            // 
            this.stStripLabel.Name = "stStripLabel";
            this.stStripLabel.Size = new System.Drawing.Size(151, 20);
            this.stStripLabel.Text = "toolStripStatusLabel1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.iPToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 3, 0, 3);
            this.menuStrip1.Size = new System.Drawing.Size(876, 30);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 24);
            this.fileToolStripMenuItem.Text = "&File";
            this.fileToolStripMenuItem.Click += new System.EventHandler(this.fileToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(128, 26);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // iPToolStripMenuItem
            // 
            this.iPToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.rGBtoGrayToolStripMenuItem,
            this.antiWhiteToolStripMenuItem});
            this.iPToolStripMenuItem.Name = "iPToolStripMenuItem";
            this.iPToolStripMenuItem.Size = new System.Drawing.Size(35, 24);
            this.iPToolStripMenuItem.Text = "&IP";
            // 
            // rGBtoGrayToolStripMenuItem
            // 
            this.rGBtoGrayToolStripMenuItem.Name = "rGBtoGrayToolStripMenuItem";
            this.rGBtoGrayToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.rGBtoGrayToolStripMenuItem.Text = "RGBtoGray";
            this.rGBtoGrayToolStripMenuItem.Click += new System.EventHandler(this.rGBtoGrayToolStripMenuItem_Click);
            // 
            // oFileDlg
            // 
            this.oFileDlg.FileName = "openFileDialog1";
            // 
            // antiWhiteToolStripMenuItem
            // 
            this.antiWhiteToolStripMenuItem.Name = "antiWhiteToolStripMenuItem";
            this.antiWhiteToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.antiWhiteToolStripMenuItem.Text = "AntiWhite";
            this.antiWhiteToolStripMenuItem.Click += new System.EventHandler(this.antiWhiteToolStripMenuItem_Click);
            // 
            // DIPSample
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(876, 463);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "DIPSample";
            this.Text = "DIPSample";
            this.Load += new System.EventHandler(this.DIPSample_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel stStripLabel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem iPToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog oFileDlg;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem rGBtoGrayToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem antiWhiteToolStripMenuItem;
    }
}