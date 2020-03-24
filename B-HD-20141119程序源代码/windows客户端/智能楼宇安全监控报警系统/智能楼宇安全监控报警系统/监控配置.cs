using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Configuration;

namespace 基于移动物联网技术的智能安防监控系统
{
    public partial class 监控配置 : Form
    {
        public 监控配置()
        {
            InitializeComponent();
        }
        private static void UpdateAppConfig(string newKey, string newValue)
        {
            bool isModified = false;
            foreach (string key in ConfigurationManager.AppSettings)
            {
                if (key == newKey)
                {
                    isModified = true;
                }
            }       // Open App.Config of executable      
            Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);      // You need to remove the old settings object before you can replace it      
            if (isModified)
            {
                config.AppSettings.Settings.Remove(newKey);
            }          // Add an Application Setting.      
            config.AppSettings.Settings.Add(newKey, newValue);         // Save the changes in App.config file.      
            config.Save(ConfigurationSaveMode.Modified);      // Force a reload of a changed section.      
            ConfigurationManager.RefreshSection("appSettings");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            UpdateAppConfig("jkip1", textBox1.Text);
           

            this.Close();

        }

        private void 配置_Load(object sender, EventArgs e)
        {
            string jkip1 = ConfigurationManager.AppSettings["jkip1"].ToString();
            string jkport1 = ConfigurationManager.AppSettings["jkport1"].ToString();
            string jknote1 = ConfigurationManager.AppSettings["jknote1"].ToString();
            string jkip2 = ConfigurationManager.AppSettings["jkip2"].ToString();
            string jkport2 = ConfigurationManager.AppSettings["jkport2"].ToString();
            string jknote2 = ConfigurationManager.AppSettings["jknote2"].ToString();
            string jkip3 = ConfigurationManager.AppSettings["jkip3"].ToString();
            string jkport3 = ConfigurationManager.AppSettings["jkport3"].ToString();
            string jknote3 = ConfigurationManager.AppSettings["jknote3"].ToString();
            string jkip4 = ConfigurationManager.AppSettings["jkip4"].ToString();
            string jkport4 = ConfigurationManager.AppSettings["jkport4"].ToString();
            string jknote4 = ConfigurationManager.AppSettings["jknote4"].ToString();

            textBox1.Text = jkip1;
           
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
