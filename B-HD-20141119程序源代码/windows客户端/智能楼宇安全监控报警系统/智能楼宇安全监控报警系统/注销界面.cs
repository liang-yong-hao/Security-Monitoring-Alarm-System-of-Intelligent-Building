using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 注销界面 : Form
    {
        public 注销界面()
        {
            InitializeComponent();
        }

        private void 注销监控_Load(object sender, EventArgs e)
        {

        }


        private void 切换用户_Click(object sender, EventArgs e)
        {
            Thread t1;
            t1 = new Thread(delegate() { start(); });
            t1.Start();
            this.Close();
        }
        void start()
        {
            登陆 form = new 登陆();
            form.ShowDialog();
        }
        private void 注销_Click_1(object sender, EventArgs e)
        {
            Thread t1;
            t1 = new Thread(delegate() { start(); });
            t1.Start();
            this.Close();
            
        }
    }
}
