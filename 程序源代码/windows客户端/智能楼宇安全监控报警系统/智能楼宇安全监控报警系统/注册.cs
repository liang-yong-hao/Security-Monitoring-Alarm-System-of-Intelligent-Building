using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 注册 : Form
    {
        public 注册()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string username = textBox1.Text.Trim();


            string constr = "Data Source=STUDENT-PC\\SQLEXPRESS;Initial Catalog=RemoteUser;Persist Security Info=True;User ID=sa;Password=123456;";

            SqlConnection mycon = new SqlConnection(constr);
            mycon.Open();

            SqlCommand checkCmd = mycon.CreateCommand();
            string s = "select username from users where username='" + username + "'";
            checkCmd.CommandText = s;
            SqlDataAdapter check = new SqlDataAdapter();
            check.SelectCommand = checkCmd;
            DataSet checkData = new DataSet();
            int n = check.Fill(checkData, "users");
            if (n != 0)
            {
                MessageBox.Show("用户名存在");
                textBox1.Text = "";
                textBox2.Text = ""; textBox3.Text = "";
            }
            else if (textBox2.Text != textBox3.Text)
            {
                MessageBox.Show("两次密码不一致");
                textBox2.Text = "";
                textBox3.Text = "";

            }
            else
            {
                string s1 = "insert into users(username,password) values ('" + textBox1.Text + "','" + textBox2.Text + "')";

                SqlCommand mycom = new SqlCommand(s1, mycon);
                mycom.ExecuteNonQuery();
                mycon.Close();
                mycom = null;
                mycon.Dispose();
                MessageBox.Show("注册成功");
                主界面 form = new 主界面();
                form.ShowDialog();


            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.textBox1.Text = "";
            this.textBox2.Text = "";
            this.textBox3.Text = "";
        }

        private void 注册_Load(object sender, EventArgs e)
        {

        }
    }
}
