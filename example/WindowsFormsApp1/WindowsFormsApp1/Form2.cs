using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        public string s1;
        public Form1 f1;

        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            f1.textBox1.Text =  textBox1.Text;
            this.Close();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            textBox1.Text = s1;
        }
    }
}
