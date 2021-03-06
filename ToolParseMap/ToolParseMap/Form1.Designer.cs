﻿namespace ToolParseMap
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
            this.ButtonParse = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonBrowse = new System.Windows.Forms.Button();
            this.labelFilename = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxlevel = new System.Windows.Forms.ComboBox();
            this.groupBoxStep1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBoxStep2 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxOrder = new System.Windows.Forms.TextBox();
            this.buttonRandom = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxTotal = new System.Windows.Forms.TextBox();
            this.radioButtonDefault = new System.Windows.Forms.RadioButton();
            this.radioButtonCustom = new System.Windows.Forms.RadioButton();
            this.radioButtonRandom = new System.Windows.Forms.RadioButton();
            this.textBoxSuper = new System.Windows.Forms.TextBox();
            this.textBoxHeavy = new System.Windows.Forms.TextBox();
            this.textBoxLight = new System.Windows.Forms.TextBox();
            this.textBoxMedium = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBoxStep3 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBoxStep1.SuspendLayout();
            this.groupBoxStep2.SuspendLayout();
            this.groupBoxStep3.SuspendLayout();
            this.SuspendLayout();
            // 
            // ButtonParse
            // 
            this.ButtonParse.Location = new System.Drawing.Point(6, 36);
            this.ButtonParse.Name = "ButtonParse";
            this.ButtonParse.Size = new System.Drawing.Size(220, 23);
            this.ButtonParse.TabIndex = 0;
            this.ButtonParse.Text = "Parse";
            this.ButtonParse.UseVisualStyleBackColor = true;
            this.ButtonParse.Click += new System.EventHandler(this.buttonParse_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Choose file:";
            // 
            // buttonBrowse
            // 
            this.buttonBrowse.Location = new System.Drawing.Point(74, 21);
            this.buttonBrowse.Name = "buttonBrowse";
            this.buttonBrowse.Size = new System.Drawing.Size(75, 23);
            this.buttonBrowse.TabIndex = 2;
            this.buttonBrowse.Text = "Browse...";
            this.buttonBrowse.UseVisualStyleBackColor = true;
            this.buttonBrowse.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // labelFilename
            // 
            this.labelFilename.Location = new System.Drawing.Point(74, 52);
            this.labelFilename.Name = "labelFilename";
            this.labelFilename.Size = new System.Drawing.Size(155, 13);
            this.labelFilename.TabIndex = 3;
            this.labelFilename.Text = "fileName";
            this.labelFilename.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "TextFile|*.txt";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "txt";
            this.saveFileDialog1.Filter = "Text file|*.txt";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Choose level:";
            // 
            // comboBoxlevel
            // 
            this.comboBoxlevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxlevel.Enabled = false;
            this.comboBoxlevel.FormattingEnabled = true;
            this.comboBoxlevel.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.comboBoxlevel.Location = new System.Drawing.Point(100, 71);
            this.comboBoxlevel.Name = "comboBoxlevel";
            this.comboBoxlevel.Size = new System.Drawing.Size(92, 21);
            this.comboBoxlevel.TabIndex = 5;
            this.comboBoxlevel.SelectedIndexChanged += new System.EventHandler(this.comboBoxlevel_SelectedIndexChanged);
            // 
            // groupBoxStep1
            // 
            this.groupBoxStep1.Controls.Add(this.label5);
            this.groupBoxStep1.Controls.Add(this.label1);
            this.groupBoxStep1.Controls.Add(this.buttonBrowse);
            this.groupBoxStep1.Controls.Add(this.labelFilename);
            this.groupBoxStep1.Location = new System.Drawing.Point(12, 12);
            this.groupBoxStep1.Name = "groupBoxStep1";
            this.groupBoxStep1.Size = new System.Drawing.Size(235, 74);
            this.groupBoxStep1.TabIndex = 6;
            this.groupBoxStep1.TabStop = false;
            this.groupBoxStep1.Text = "Step 1: Choose map file";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(6, 52);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(62, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "File name:";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBoxStep2
            // 
            this.groupBoxStep2.Controls.Add(this.label8);
            this.groupBoxStep2.Controls.Add(this.textBoxOrder);
            this.groupBoxStep2.Controls.Add(this.buttonRandom);
            this.groupBoxStep2.Controls.Add(this.label7);
            this.groupBoxStep2.Controls.Add(this.textBoxTotal);
            this.groupBoxStep2.Controls.Add(this.radioButtonDefault);
            this.groupBoxStep2.Controls.Add(this.radioButtonCustom);
            this.groupBoxStep2.Controls.Add(this.radioButtonRandom);
            this.groupBoxStep2.Controls.Add(this.textBoxSuper);
            this.groupBoxStep2.Controls.Add(this.textBoxHeavy);
            this.groupBoxStep2.Controls.Add(this.textBoxLight);
            this.groupBoxStep2.Controls.Add(this.textBoxMedium);
            this.groupBoxStep2.Controls.Add(this.label9);
            this.groupBoxStep2.Controls.Add(this.label11);
            this.groupBoxStep2.Controls.Add(this.label6);
            this.groupBoxStep2.Controls.Add(this.label4);
            this.groupBoxStep2.Controls.Add(this.comboBoxlevel);
            this.groupBoxStep2.Controls.Add(this.label2);
            this.groupBoxStep2.Location = new System.Drawing.Point(12, 92);
            this.groupBoxStep2.Name = "groupBoxStep2";
            this.groupBoxStep2.Size = new System.Drawing.Size(235, 266);
            this.groupBoxStep2.TabIndex = 7;
            this.groupBoxStep2.TabStop = false;
            this.groupBoxStep2.Text = "Step 2: Generate Enemy Tank";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(29, 240);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(33, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "Order";
            // 
            // textBoxOrder
            // 
            this.textBoxOrder.Location = new System.Drawing.Point(123, 237);
            this.textBoxOrder.MaxLength = 4;
            this.textBoxOrder.Name = "textBoxOrder";
            this.textBoxOrder.ReadOnly = true;
            this.textBoxOrder.Size = new System.Drawing.Size(56, 20);
            this.textBoxOrder.TabIndex = 23;
            this.textBoxOrder.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // buttonRandom
            // 
            this.buttonRandom.Location = new System.Drawing.Point(68, 43);
            this.buttonRandom.Name = "buttonRandom";
            this.buttonRandom.Size = new System.Drawing.Size(75, 23);
            this.buttonRandom.TabIndex = 22;
            this.buttonRandom.Text = "Random";
            this.buttonRandom.UseVisualStyleBackColor = true;
            this.buttonRandom.Click += new System.EventHandler(this.buttonRandom_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 110);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 13);
            this.label7.TabIndex = 21;
            this.label7.Text = "Total";
            // 
            // textBoxTotal
            // 
            this.textBoxTotal.Location = new System.Drawing.Point(123, 107);
            this.textBoxTotal.MaxLength = 2;
            this.textBoxTotal.Name = "textBoxTotal";
            this.textBoxTotal.ReadOnly = true;
            this.textBoxTotal.Size = new System.Drawing.Size(33, 20);
            this.textBoxTotal.TabIndex = 20;
            this.textBoxTotal.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // radioButtonDefault
            // 
            this.radioButtonDefault.AutoSize = true;
            this.radioButtonDefault.Location = new System.Drawing.Point(149, 19);
            this.radioButtonDefault.Name = "radioButtonDefault";
            this.radioButtonDefault.Size = new System.Drawing.Size(59, 17);
            this.radioButtonDefault.TabIndex = 19;
            this.radioButtonDefault.Text = "Default";
            this.radioButtonDefault.UseVisualStyleBackColor = true;
            this.radioButtonDefault.CheckedChanged += new System.EventHandler(this.radioButtonDefault_CheckedChanged);
            // 
            // radioButtonCustom
            // 
            this.radioButtonCustom.AutoSize = true;
            this.radioButtonCustom.Checked = true;
            this.radioButtonCustom.Location = new System.Drawing.Point(83, 19);
            this.radioButtonCustom.Name = "radioButtonCustom";
            this.radioButtonCustom.Size = new System.Drawing.Size(60, 17);
            this.radioButtonCustom.TabIndex = 18;
            this.radioButtonCustom.TabStop = true;
            this.radioButtonCustom.Text = "Custom";
            this.radioButtonCustom.UseVisualStyleBackColor = true;
            this.radioButtonCustom.CheckedChanged += new System.EventHandler(this.radioButtonCustom_CheckedChanged);
            // 
            // radioButtonRandom
            // 
            this.radioButtonRandom.AutoSize = true;
            this.radioButtonRandom.Location = new System.Drawing.Point(12, 20);
            this.radioButtonRandom.Name = "radioButtonRandom";
            this.radioButtonRandom.Size = new System.Drawing.Size(65, 17);
            this.radioButtonRandom.TabIndex = 17;
            this.radioButtonRandom.Text = "Random";
            this.radioButtonRandom.UseVisualStyleBackColor = true;
            this.radioButtonRandom.CheckedChanged += new System.EventHandler(this.radioButtonRandom_CheckedChanged);
            // 
            // textBoxSuper
            // 
            this.textBoxSuper.Location = new System.Drawing.Point(123, 211);
            this.textBoxSuper.MaxLength = 2;
            this.textBoxSuper.Name = "textBoxSuper";
            this.textBoxSuper.ReadOnly = true;
            this.textBoxSuper.Size = new System.Drawing.Size(33, 20);
            this.textBoxSuper.TabIndex = 16;
            this.textBoxSuper.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // textBoxHeavy
            // 
            this.textBoxHeavy.Location = new System.Drawing.Point(123, 185);
            this.textBoxHeavy.MaxLength = 2;
            this.textBoxHeavy.Name = "textBoxHeavy";
            this.textBoxHeavy.ReadOnly = true;
            this.textBoxHeavy.Size = new System.Drawing.Size(33, 20);
            this.textBoxHeavy.TabIndex = 15;
            this.textBoxHeavy.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // textBoxLight
            // 
            this.textBoxLight.Location = new System.Drawing.Point(123, 159);
            this.textBoxLight.MaxLength = 2;
            this.textBoxLight.Name = "textBoxLight";
            this.textBoxLight.ReadOnly = true;
            this.textBoxLight.Size = new System.Drawing.Size(33, 20);
            this.textBoxLight.TabIndex = 14;
            this.textBoxLight.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // textBoxMedium
            // 
            this.textBoxMedium.Location = new System.Drawing.Point(123, 133);
            this.textBoxMedium.MaxLength = 2;
            this.textBoxMedium.Name = "textBoxMedium";
            this.textBoxMedium.ReadOnly = true;
            this.textBoxMedium.Size = new System.Drawing.Size(33, 20);
            this.textBoxMedium.TabIndex = 13;
            this.textBoxMedium.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMedium_KeyPress);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(29, 214);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(94, 13);
            this.label9.TabIndex = 12;
            this.label9.Text = "SuperHeavy Tank";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(29, 188);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(66, 13);
            this.label11.TabIndex = 10;
            this.label11.Text = "Heavy Tank";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(29, 162);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(58, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "Light Tank";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 136);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Medium Tank";
            // 
            // groupBoxStep3
            // 
            this.groupBoxStep3.Controls.Add(this.label3);
            this.groupBoxStep3.Controls.Add(this.ButtonParse);
            this.groupBoxStep3.Location = new System.Drawing.Point(12, 364);
            this.groupBoxStep3.Name = "groupBoxStep3";
            this.groupBoxStep3.Size = new System.Drawing.Size(235, 73);
            this.groupBoxStep3.TabIndex = 8;
            this.groupBoxStep3.TabStop = false;
            this.groupBoxStep3.Text = "Step 3: Parse map";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Parse map:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(255, 444);
            this.Controls.Add(this.groupBoxStep3);
            this.Controls.Add(this.groupBoxStep2);
            this.Controls.Add(this.groupBoxStep1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "ToolParseMap";
            this.groupBoxStep1.ResumeLayout(false);
            this.groupBoxStep1.PerformLayout();
            this.groupBoxStep2.ResumeLayout(false);
            this.groupBoxStep2.PerformLayout();
            this.groupBoxStep3.ResumeLayout(false);
            this.groupBoxStep3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ButtonParse;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonBrowse;
        private System.Windows.Forms.Label labelFilename;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxlevel;
        private System.Windows.Forms.GroupBox groupBoxStep1;
        private System.Windows.Forms.GroupBox groupBoxStep2;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBoxStep3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.RadioButton radioButtonDefault;
        private System.Windows.Forms.RadioButton radioButtonCustom;
        private System.Windows.Forms.RadioButton radioButtonRandom;
        private System.Windows.Forms.TextBox textBoxSuper;
        private System.Windows.Forms.TextBox textBoxHeavy;
        private System.Windows.Forms.TextBox textBoxLight;
        private System.Windows.Forms.TextBox textBoxMedium;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxTotal;
        private System.Windows.Forms.Button buttonRandom;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxOrder;
    }
}

