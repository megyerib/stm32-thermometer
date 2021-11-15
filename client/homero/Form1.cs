using System;
using System.ComponentModel;
using System.Drawing;
using System.IO.Ports;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace homero
{
    public partial class Form1 : Form
    {
        bool connected = false; // Jelzi a portválasztónak, hogy csatlakoztunk-e
        string receivedString;  // A soros portról beolvasott sor
        int temp = 0, th = 0;   // Hőmérséklet, határ

        public Form1()
        {
            InitializeComponent();
            clear();
            getAvailablePorts();
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(getTemp);
        }

        void clear()
        {
            labelTemp.Text = labelTh.Text = "";
            labelTemp.ForeColor = labelTh.ForeColor = new Color(); // Szín visszaállítása
        }

        private void getTemp(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                receivedString = serialPort1.ReadLine();
                this.BeginInvoke(new EventHandler(DisplayText));
            }
            finally { }
        }

        private void DisplayText(object sender, EventArgs e)
        {
            lineToTemp(receivedString);

            labelTemp.Text = (temp/10).ToString() + "." + Math.Abs(temp%10).ToString() + "°C";
            labelTh.Text = "Threshold: "+(th / 10).ToString() + "." + Math.Abs(th % 10).ToString() + "°C";

            if (temp >= th)
                labelTemp.ForeColor = labelTh.ForeColor = Color.Red;
            else
                labelTemp.ForeColor = labelTh.ForeColor = new Color();
        }

        private void lineToTemp(string s)
        {
            string pattern = @"TEMP([+-]\d{3})([+-]\d{3})";
            Regex rgx = new Regex(pattern);
            Match match = rgx.Match(s);
            if (match.Success)
            {
                string[] names = rgx.GetGroupNames();
                Int32.TryParse(match.Groups[1].Value, out temp);
                Int32.TryParse(match.Groups[2].Value, out th);
            }
        }

        void getAvailablePorts()
        {
            string[] ports = SerialPort.GetPortNames();
            portComboBox.Items.Clear();
            portComboBox.Items.AddRange(ports);
            try { portComboBox.SelectedIndex = 0; } // Első elem kiválasztása
            catch (ArgumentOutOfRangeException) { /* Nincs port */ }
        }

        private void portOpenButton_Click(object sender, EventArgs e)
        {
            if (!connected)
            {
                try { serialPort1.PortName = portComboBox.Text; }
                catch (ArgumentException)
                {
                    MessageBox.Show("No COM port selected!");
                    return;
                }

                try { serialPort1.Open(); }
                catch
                {
                    MessageBox.Show("Port unavailable!");
                    return;
                }

                portComboBox.Enabled = false;
                portOpenButton.Text = "Close";
                connected = true;
            }
            else
            {
                serialPort1.Close();
                portComboBox.Enabled = true;
                portOpenButton.Text = "Open";
                connected = false;
                clear();
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            getAvailablePorts();
        }

        private void Form1_Closing(object sender, CancelEventArgs e)
        {
            serialPort1.Close();
        }
    }
}
