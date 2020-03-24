using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Threading;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 登陆 : Form
    {

        public 登陆()
        {
            InitializeComponent();
        }

        void start()
        {
            主界面 form = new 主界面();
            form.ShowDialog();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string username = LoginName.Text.Trim();
            string password = textBox1.Text.Trim();



            string connsql = "Data Source=STUDENT-PC\\SQLEXPRESS;Initial Catalog=RemoteUser;Persist Security Info=True;User ID=sa;Password=123456;";

            //string sql="select * from users where username='"+username+
            string sql = "select * from users where username='" + username + "'and password='" + password + "'";

            SqlConnection con = new SqlConnection(connsql);
            con.Open();

            SqlCommand com = new SqlCommand(sql, con);

            SqlDataReader sread = com.ExecuteReader();

            try
            {
                if (sread.Read())
                {
                    MessageBox.Show("登录成功");
                    Thread t1;
                    t1 = new Thread(delegate() { start(); });
                    t1.Start();
                    this.Close();
                }
                else
                {
                    MessageBox.Show("请输入正确的用户名和密码");
                }
            }
            catch (Exception msg)
            {
                throw new Exception(msg.ToString());

            }
            finally
            {
                con.Close();
                con.Dispose();
                sread.Dispose();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            注册 form = new 注册();
            form.ShowDialog();
        }

        private void PassWord_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
