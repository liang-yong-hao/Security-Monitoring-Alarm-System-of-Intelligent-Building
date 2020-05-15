using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.IO;
using System.Timers;
using System.Configuration;
using System.Data.SqlClient;
using System.Drawing.Imaging;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 主界面 : Form
    {
        public 主界面()
        {
            InitializeComponent();
        }
        /******************************************************************
         定义变量
         **************************************************************/
        Thread t1;
        public static Double tempurature = 0;//指定全局变量
        public static Double weit = 0;
        public static Double ludian = 0;
        public int color_h = 6280;
        public int color_l = 1;
        bool st1=false;
     
        private int HDRLEN = 50;
        private int SZOFS = 29;
      
        public static String picname1;
        public static String picname2;
        public static String picname3;
        public static String picname4;
        bool bsave = false;
        Image imageJt;
        private String server_ip1 = "192.168.1.192";//？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
        private int port1 = 7171;
        Thread tsense;
        public int capture1, capture2, capture3, capture4;
        public string temp, humi, dewPoint, qingXie,s1;
        int pic1;
       

        
        public float ke = 0;//cv

        void start1()
        {
            byte[] bytes;
            int recv;
            string s;
            using (Socket connection = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                
                try
                {
                    connection.Connect(server_ip1, port1);
                    while (true)
                    {
                        try
                        {
                            bytes = new byte[1024];
                            recv = connection.Receive(bytes);
                            
                            if (recv != 0)
                            {
                               
                                s = Encoding.ASCII.GetString(bytes);                              
                                /*temp=lblTemp.Text = s.Substring(0, 5) + "℃";//温度
                                if (String.Compare(temp, "50") > 0)
                                    lblTemp.ForeColor = Color.Red;
                                else lblTemp.ForeColor = Color.Black;
                                humi=lblHumi.Text = s.Substring(12, 5);//湿度
                                dewPoint=lblDewPoint.Text = s.Substring(24, 5) + "℃";//露点*/
                               

                                if (s.Substring(46, 1) == "1")
                                {
                                    MessageBox.Show("警告，警告，你当前的烟雾浓度大于安全值，请查看是否着火");
                                    string str = string.Format("insert into 传感器信息(温度,湿度,露点,烟雾,日期) values ('" + temp + "','" + humi + "','" + dewPoint + "','" + "异常" + "','" + qingXie + "','" + System.DateTime.Now + "')");
                                    using (SqlConnection conn = new SqlConnection("Data Source=STUDENT-PC\\SQLEXPRESS;Initial Catalog=RemoteUser;Persist Security Info=True;User ID=sa;Password=123456"))
                                    {
                                        conn.Open();
                                        SqlCommand cmd = new SqlCommand(str, conn);
                                        int a = cmd.ExecuteNonQuery();
                                        conn.Close();
                                    }
                                }
                                if (s.Substring(42, 1) == "0")//防盗
                                {
                                    //lblIrst.Text = "正常";
                                    //lblIrst.ForeColor = Color.Black;
                                    bsave = false;
                                }
                                else
                                {
                                    capture2 = 2;
                                    //lblIrst.Text = "";
                                    //lblIrst.Text = "异常";
                                }

                                //double d1 = Convert.ToDouble(qingXie);
                                //if (d1 >= 75.0 || d1 <= -75.0)
                                //{
                                //    MessageBox.Show("警告，警告，当前倾斜过于严重，请调整倾斜角度，防止侧翻！");
                                //    string str = string.Format("insert into 传感器信息(温度,湿度,露点,烟雾,倾角，日期) values ('" + temp + "','" + humi + "','" + dewPoint + "','" + "正常" + "','" + qingXie + "','" + System.DateTime.Now + "')");
                                //    using (SqlConnection conn = new SqlConnection("Data Source=STUDENT-PC\\SQLEXPRESS;Initial Catalog=RemoteUser;Persist Security Info=True;User ID=sa;Password=123456"))
                                //    {
                                //        conn.Open();
                                //        SqlCommand cmd = new SqlCommand(str, conn);
                                //        int a = cmd.ExecuteNonQuery();
                                //        conn.Close();
                                //    }

                                //}
                            
                      
                              
                                
                            }
                        }
                        catch (Exception ex)
                        {

                        }
                    }
                    try
                    {
                        connection.Close();
                    }
                    catch (IOException e)
                    {

                    }
                }
                catch (Exception ex)
                {
                    //MessageBox.Show(ex.ToString());
                }

            }
        }
     
        public int[] GetHisogram(Bitmap img)
        {

            BitmapData data = img.LockBits(new System.Drawing.Rectangle(0, 0, img.Width, img.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            int[] histogram = new int[256];

            unsafe
            {

                byte* ptr = (byte*)data.Scan0;

                int remain = data.Stride - data.Width * 3;

                for (int i = 0; i < histogram.Length; i++)

                    histogram[i] = 0;

                for (int i = 0; i < data.Height; i++)
                {

                    for (int j = 0; j < data.Width; j++)
                    {

                        int mean = ptr[0] + ptr[1] + ptr[2];

                        mean /= 3;

                        histogram[mean]++;

                        ptr += 3;

                    }

                    ptr += remain;

                }

            }

            img.UnlockBits(data);

            return histogram;

        }
        public float GetAbs(int firstNum, int secondNum)
        {
            float abs = Math.Abs((float)firstNum - (float)secondNum);
            float result = Math.Max(firstNum, secondNum);
            if (result == 0)
                result = 1;
            return abs / result;
        }
        public float GetResult(int[] firstNum, int[] scondNum)
        {

            if (firstNum.Length != scondNum.Length)
            {

                return 0;

            }

            else
            {

                float result = 0;

                int j = firstNum.Length;

                for (int i = 0; i < j; i++)
                {

                    result += 1 - GetAbs(firstNum[i], scondNum[i]);

                    Console.WriteLine(i + "----" + result);

                }

                return result / j;

            }

        }
        public void start(PictureBox picture, string jkip, string jkport)
        {
            bool running = false;
            bool m_stop = false;
            int switchImage = 0;
            int portmy = Convert.ToInt32(jkport); //端口号为int32
            m_stop = false;
            NetworkStream sin = null;
            if (picture == pictureBox1) switchImage = 1;

            using (Socket connection = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                try
                {
                    
                    connection.Connect(jkip, portmy);
                    
                    sin = new NetworkStream(connection, true);
                }
                catch (Exception ex)
                {
                    m_stop = true;
                    MessageBox.Show("连接失败");
                }
                //byte[] buffer0 = new byte[1024 * 1024];
                byte[] buffer = new byte[512 * 1024];
                while (!m_stop)
                {
                    byte[] b = Encoding.ASCII.GetBytes("O" + "K" + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0);
                    int n = 0;
                    int siz = 0;
                    try
                    {
                        connection.Send(b);
                        //n = connection.Receive(buffer);
                        n = sin.Read(buffer, 0, HDRLEN);//HDRLEN=50;
                    }
                    catch (Exception ex)
                    {
                        m_stop = true;
                    }
                    if (n < HDRLEN)
                    {
                        if (n <= 0)
                            m_stop = true;
                        continue;
                    }
                    else
                    {
                        int ssz = SZOFS;//SZOFS=29
                        siz += unsignedByteToInt(buffer[ssz + 3]) << 24;
                        siz += unsignedByteToInt(buffer[ssz + 2]) << 16;
                        siz += unsignedByteToInt(buffer[ssz + 1]) << 8;
                        siz += unsignedByteToInt(buffer[ssz]);
                        n = HDRLEN;
                        if (buffer[0] != 'S' || buffer[1] != 'P' || buffer[2] != 'C' || buffer[3] != 'A')
                        {
                            continue;
                        }
                        else if (siz <= 0 || siz > (512 * 1024))
                        {
                            siz = 0;
                            try
                            {
                                sin.Read(buffer, n, buffer.Length);
                                //connection.Receive(buffer);

                            }
                            catch (Exception ex)
                            {

                            }
                            continue;
                        }
                        else
                        {
                            do
                            {
                                int r = 0;
                                try
                                {
                                    // r = in.read(buffer, n, HDLREN + siz - n);
                                    r = sin.Read(buffer, n, buffer.Length - n);
                                }
                                catch (Exception ex)
                                {
                                    //e.printStackTrace();
                                }

                                n += r;
                            }
                            while (n < (siz + HDRLEN));
                        }

                    }
                    byte[] buffer2 = new byte[n];
                    // int height;
                    for (int i = 0; i < n; i++)
                        buffer2[i] = buffer[i + HDRLEN];//****************************************************图像数据存储在了buffer2[]中
                    try
                    {
                        using (MemoryStream ms = new MemoryStream(buffer2))
                        {

                            try
                            {
                                Bitmap img = new Bitmap(ms);
                                imageJt = img;
                                switch(switchImage)
                                {
                                    case 1:
                                        if(capture1==1)
                                        {
                                        picname1= @"D:\截图保存\监控点1\";
                                        picname1 = picname1 + "-" + DateTime.Now.Year + "-" + DateTime.Now.Month + "-" + DateTime.Now.Day + "-" + DateTime.Now.Hour + "-" + DateTime.Now.Minute + "-" + DateTime.Now.Second + "-" + "报警" + ".jpg";
                                        imageJt.Save(picname1);
                                        capture1=0;
                                        }
                                         break ;
                                   
                                         break;
                                    default: break; 
                                }
                               
                               
                                if (picture.Equals(pictureBox1) == true)
                                {
                                    picture.Image = img;
                                }
                               

                               
                            }

                            catch (Exception ex)
                            {
                                ex.Message.ToString();
                            }
                        }
                    }
                    catch (IOException e)
                    {

                    }
                }// while

                try
                {
                    connection.Close();
                }
                catch (IOException e)
                {

                }
            }
            m_stop = true;
            running = true;

        }

        public static int unsignedByteToInt(byte b)
        {
            return (int)b & 0xff;
        }

        





        //监控点1--------------------------------------------------------------------------------------------------------启用
       

       

        private void 主界面_Load(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false;
            tsense = new Thread(start1); tsense.Start();
            pic1 = 0;
         
        }

        private void 主界面_FormClosing(object sender, FormClosingEventArgs e)
        {
            tsense.Abort(); 
            if(st1==true)
                t1.Abort();
            
        }


        private void 监控配置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            监控配置 form = new 监控配置(); 
            form.ShowDialog();
        }

      


        void start()
        {
            登陆 form = new 登陆();
            form.ShowDialog();
        }

        private void 注销ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Thread t1;
            t1=new Thread(delegate() { start(); });
            t1.Start();
            this.Close();
        }

        private void lblTemp_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            capture1 = 1;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            capture2= 1;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            capture3= 1;

        }

        private void button4_Click(object sender, EventArgs e)
        {
            capture4 = 1;
        }

        private void 环境监测ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            环境异常 form1 = new 环境异常();
            form1.Show();
        }

       
       
        private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (pic1 == 0)
            {
                pictureBox1.Height = 360;
                pictureBox1.Width = 480;
                label1.Location = new System.Drawing.Point(300, 550);
              
                pic1 = 1;
            }
            else
            {
                pictureBox1.Height = 180;
                pictureBox1.Width = 240;
                label1.Location = new System.Drawing.Point(120,310);
              

                pic1 = 0;
            }
        }

      

      

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void 登陆ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void 温度ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (温度ToolStripMenuItem.Checked)
            {
                pictureBox7.Visible = true;
                pictureBox3.Visible = false;

            }
            else
            {
                pictureBox3.Visible = true;
                pictureBox7.Visible = false;
            }
        }

        private void 监控ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string jkip1 = ConfigurationManager.AppSettings["jkip1"].ToString();
            string jkport1 = ConfigurationManager.AppSettings["jkport1"].ToString();
            if (监控ToolStripMenuItem.Checked == true)
            {
                if (st1 == false)
                {

                    t1 = new Thread(delegate () { start(pictureBox1, jkip1, jkport1); });
                    t1.Start();
                    st1 = true;
                    pictureBox6.Visible = true;
                    pictureBox2.Visible = false;
                }
            }
            else
            {
                if (st1 == true)
                {
                    t1.Abort();
                    st1 = false;
                    pictureBox2.Visible = true;
                    pictureBox6.Visible = false;
                    pictureBox1.Image = global::基于移动物联网技术的智能安防监控系统.Properties.Resources.断开链接;


                }
            }

        }

        private void 露点ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (露点ToolStripMenuItem.Checked)
            {
                pictureBox8.Visible = true;
                pictureBox4.Visible = false;

            }
            else
            {
                pictureBox4.Visible = true;
                pictureBox8.Visible = false;
            }
        }

        private void 闯入ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (闯入ToolStripMenuItem.Checked)
            {
                pictureBox9.Visible = true;
                pictureBox5.Visible = false;

            }
            else
            {
                pictureBox5.Visible = true;
                pictureBox9.Visible = false;
            }
        }

    

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void 注销ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            Thread t1;
            t1 = new Thread(delegate () { start(); });
            t1.Start();
            this.Close();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {

        }


        private void count_people_Click(object sender, EventArgs e)
        {

        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void lblQingxie_Click(object sender, EventArgs e)
        {

        }

        private void lblIrst_Click(object sender, EventArgs e)
        {

        }

    }
}
