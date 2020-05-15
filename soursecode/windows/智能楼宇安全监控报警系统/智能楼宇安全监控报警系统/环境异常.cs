using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 环境异常 : Form
    {
        public 环境异常()
        {
            InitializeComponent();
        }

        private void 环境异常_Load(object sender, EventArgs e)
        {
            SqlConnection connect = new SqlConnection("Data Source=STUDENT-PC\\SQLEXPRESS;Initial Catalog=RemoteUser;Persist Security Info=True;User ID=sa;Password=123456");
            SqlCommand cmd = connect.CreateCommand();
            connect.Open();
            cmd.CommandText = "select * from 传感器信息";
            SqlDataReader dr = cmd.ExecuteReader();
            SqlDataAdapter sda = new SqlDataAdapter(cmd);

            DataTable dt = new DataTable();
            dt.Load(dr);
            this.dataGridView1.DataSource = dt;
            connect.Close();
        }
        
    }
}
