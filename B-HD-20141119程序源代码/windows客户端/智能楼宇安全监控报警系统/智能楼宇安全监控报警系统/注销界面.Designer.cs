namespace 基于移动物联网技术的智能安防监控系统
{
    partial class 注销界面
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
            this.切换用户 = new System.Windows.Forms.Button();
            this.注销 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("楷体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.ForeColor = System.Drawing.SystemColors.Highlight;
            this.label1.Location = new System.Drawing.Point(113, 28);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(171, 21);
            this.label1.TabIndex = 1;
            this.label1.Text = "注销与切换用户";
            // 
            // 切换用户
            // 
            this.切换用户.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.切换用户.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.切换用户.Location = new System.Drawing.Point(237, 218);
            this.切换用户.Name = "切换用户";
            this.切换用户.Size = new System.Drawing.Size(91, 31);
            this.切换用户.TabIndex = 6;
            this.切换用户.Text = "切换用户";
            this.切换用户.UseVisualStyleBackColor = true;
            this.切换用户.Click += new System.EventHandler(this.切换用户_Click);
            // 
            // 注销
            // 
            this.注销.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.注销.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.注销.Location = new System.Drawing.Point(72, 218);
            this.注销.Name = "注销";
            this.注销.Size = new System.Drawing.Size(91, 31);
            this.注销.TabIndex = 7;
            this.注销.Text = "注销";
            this.注销.UseVisualStyleBackColor = true;
            this.注销.Click += new System.EventHandler(this.注销_Click_1);
            // 
            // 注销界面
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(472, 323);
            this.Controls.Add(this.注销);
            this.Controls.Add(this.切换用户);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "注销界面";
            this.Text = "注销监控";
            this.Load += new System.EventHandler(this.注销监控_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button 切换用户;
        private System.Windows.Forms.Button 注销;
    }
}