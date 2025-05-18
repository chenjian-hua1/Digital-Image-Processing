using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace DIP
{
    public partial class DIPSample : Form
    {
        public DIPSample()
        {
            InitializeComponent();
        }

        [DllImport("dip_proc.dll", CallingConvention = CallingConvention.Cdecl)]
        unsafe public static extern void encode(int *f0,int w,int h,int *g0);

        [DllImport("B11023227.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void negative(int[] f, int w, int h, int[] g);

        Bitmap NpBitmap;
        int[] f;
        int[] g;
        int w, h;

        private void DIPSample_Load(object sender, EventArgs e)
        {
            this.IsMdiContainer = true;
            this.WindowState = FormWindowState.Maximized;
			this.stStripLabel.Text = "";
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            oFileDlg.CheckFileExists = true;
            oFileDlg.CheckPathExists = true;
            oFileDlg.Title = "Open File - DIP Sample";
            oFileDlg.ValidateNames = true;
            oFileDlg.Filter = "bmp files (*.bmp)|*.bmp";
            oFileDlg.FileName = "";

            if (oFileDlg.ShowDialog() == DialogResult.OK)
            {
                MSForm childForm = new MSForm();
                childForm.MdiParent = this;
                childForm.pf1 = stStripLabel;
                NpBitmap = bmp_read(oFileDlg);
                childForm.pBitmap = NpBitmap;
                w = NpBitmap.Width;
                h = NpBitmap.Height;
                childForm.Show();
            }
        }

        private Bitmap bmp_read(OpenFileDialog oFileDlg)
        {
            Bitmap pBitmap;
            string fileloc = oFileDlg.FileName;
            pBitmap = new Bitmap(fileloc);
            w = pBitmap.Width;
            h = pBitmap.Height;
            return pBitmap;
        }

        private int[] bmp2array(Bitmap myBitmap)
        {
            int[] ImgData = new int[myBitmap.Width * myBitmap.Height];
            BitmapData byteArray = myBitmap.LockBits(new Rectangle(0, 0, myBitmap.Width, myBitmap.Height),
                                          ImageLockMode.ReadWrite,
                                          myBitmap.PixelFormat);
            int ByteOfSkip = byteArray.Stride - byteArray.Width * (int)(byteArray.Stride / myBitmap.Width);
            unsafe
            {
                byte* imgPtr = (byte*)(byteArray.Scan0);
                for (int y = 0; y < byteArray.Height; y++)
                {
                    for (int x = 0; x < byteArray.Width; x++)
                    {
                        ImgData[x + byteArray.Height * y] = (int)*(imgPtr);
                        //ImgData[x, y] = (int)*(imgPtr + 1);
                        //ImgData[x, y] = (int)*(imgPtr + 2);
                        imgPtr += (int)(byteArray.Stride / myBitmap.Width);
                    }
                    imgPtr += ByteOfSkip;
                }
            }
            myBitmap.UnlockBits(byteArray);
            return ImgData;
        }

        private static Bitmap array2bmp(int[] ImgData)
        {
            int Width = (int)Math.Sqrt(ImgData.GetLength(0));
            int Height = (int)Math.Sqrt(ImgData.GetLength(0));
            Bitmap myBitmap = new Bitmap(Width, Height, PixelFormat.Format24bppRgb);
            BitmapData byteArray = myBitmap.LockBits(new Rectangle(0, 0, Width, Height),
                                           ImageLockMode.WriteOnly,
                                           PixelFormat.Format24bppRgb);
            //Padding bytes的長度
            int ByteOfSkip = byteArray.Stride - myBitmap.Width * 3;
            unsafe
            {                                   // 指標取出影像資料
                byte* imgPtr = (byte*)byteArray.Scan0;
                for (int y = 0; y < Height; y++)
                {
                    for (int x = 0; x < Width; x++)
                    {
                        *imgPtr = (byte)ImgData[x + Height * y];       //B
                        *(imgPtr + 1) = (byte)ImgData[x + Height * y]; //G 
                        *(imgPtr + 2) = (byte)ImgData[x + Height * y]; //R  
                        imgPtr += 3;
                    }
                    imgPtr += ByteOfSkip; // 跳過Padding bytes
                }
            }
            myBitmap.UnlockBits(byteArray);
            return myBitmap;
        }

        private void rGBtoGrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int []f;
            int []g;
            foreach (MSForm cF in MdiChildren)
			   {
					if (cF.Focused)
					{
					    f = bmp2array(cF.pBitmap);
			            g=new int[w*h];
                        unsafe
                        {
                            fixed (int* f0 = f) fixed (int* g0 = g)
                            {
                                encode(f0, w, h, g0);
                            }
                        } 
                        NpBitmap = array2bmp(g);
				        break;
				    }
			   }
			MSForm childForm = new MSForm();
	        childForm.MdiParent = this;
            childForm.pf1 = stStripLabel;
			childForm.pBitmap = NpBitmap; 
			childForm.Show();
        }

        private void antiWhiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int[] f;
            int[] g;
            foreach (MSForm cF in MdiChildren)
            {
                if (cF.Focused)
                {
                    f = bmp2array(cF.pBitmap);
                    g = new int[w * h];
                    //unsafe
                    //{
                        //fixed (int f0 = f) fixed (int* g0 = g)
                        //{
                    negative(f, w, h, g);
                        //}
                    //}
                    NpBitmap = array2bmp(g);
                    break;
                }
            }
            MSForm childForm = new MSForm();
            childForm.MdiParent = this;
            childForm.pf1 = stStripLabel;
            childForm.pBitmap = NpBitmap;
            childForm.Text = "負片";
            childForm.Show();
        }

        private void fileToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

    }
}
