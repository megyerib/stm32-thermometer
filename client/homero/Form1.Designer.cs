namespace homero
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.portComboBox = new System.Windows.Forms.ComboBox();
            this.portOpenButton = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.labelTemp = new System.Windows.Forms.Label();
            this.labelTh = new System.Windows.Forms.Label();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(39, 12);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(152, 21);
            this.portComboBox.TabIndex = 0;
            // 
            // portOpenButton
            // 
            this.portOpenButton.Location = new System.Drawing.Point(197, 11);
            this.portOpenButton.Name = "portOpenButton";
            this.portOpenButton.Size = new System.Drawing.Size(75, 23);
            this.portOpenButton.TabIndex = 1;
            this.portOpenButton.Text = "Open";
            this.portOpenButton.UseVisualStyleBackColor = true;
            this.portOpenButton.Click += new System.EventHandler(this.portOpenButton_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            // 
            // labelTemp
            // 
            this.labelTemp.AutoSize = true;
            this.labelTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 32F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.labelTemp.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelTemp.Location = new System.Drawing.Point(3, 36);
            this.labelTemp.Name = "labelTemp";
            this.labelTemp.Size = new System.Drawing.Size(130, 51);
            this.labelTemp.TabIndex = 2;
            this.labelTemp.Text = "0.0°C";
            this.labelTemp.Click += new System.EventHandler(this.label1_Click);
            // 
            // labelTh
            // 
            this.labelTh.AutoSize = true;
            this.labelTh.Location = new System.Drawing.Point(9, 87);
            this.labelTh.Name = "labelTh";
            this.labelTh.Size = new System.Drawing.Size(86, 13);
            this.labelTh.TabIndex = 3;
            this.labelTh.Text = "Threshold: 0.0°C";
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Image = ((System.Drawing.Image)(resources.GetObject("buttonRefresh.Image")));
            this.buttonRefresh.Location = new System.Drawing.Point(11, 11);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(23, 23);
            this.buttonRefresh.TabIndex = 4;
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 108);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.labelTh);
            this.Controls.Add(this.labelTemp);
            this.Controls.Add(this.portOpenButton);
            this.Controls.Add(this.portComboBox);
            this.Name = "Form1";
            this.Text = "Nucleo thermometer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox portComboBox;
        private System.Windows.Forms.Button portOpenButton;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label labelTemp;
        private System.Windows.Forms.Label labelTh;
        private System.Windows.Forms.Button buttonRefresh;
    }
}

