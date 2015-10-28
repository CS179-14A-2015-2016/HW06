namespace WindowsFormsApplication2
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
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.shapeContainer1 = new Microsoft.VisualBasic.PowerPacks.ShapeContainer();
            this.artillery2 = new Microsoft.VisualBasic.PowerPacks.OvalShape();
            this.artillery1 = new Microsoft.VisualBasic.PowerPacks.OvalShape();
            this.lineShape2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape1 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.player1 = new Microsoft.VisualBasic.PowerPacks.RectangleShape();
            this.player2 = new Microsoft.VisualBasic.PowerPacks.RectangleShape();
            this.windLabel = new System.Windows.Forms.Label();
            this.playerTurnText = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 15;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // shapeContainer1
            // 
            this.shapeContainer1.Location = new System.Drawing.Point(0, 0);
            this.shapeContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.shapeContainer1.Name = "shapeContainer1";
            this.shapeContainer1.Shapes.AddRange(new Microsoft.VisualBasic.PowerPacks.Shape[] {
            this.player2,
            this.player1,
            this.artillery2,
            this.artillery1,
            this.lineShape2,
            this.lineShape1});
            this.shapeContainer1.Size = new System.Drawing.Size(484, 261);
            this.shapeContainer1.TabIndex = 0;
            this.shapeContainer1.TabStop = false;
            // 
            // artillery2
            // 
            this.artillery2.FillColor = System.Drawing.SystemColors.Control;
            this.artillery2.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.artillery2.Location = new System.Drawing.Point(240, 128);
            this.artillery2.Name = "artillery2";
            this.artillery2.Size = new System.Drawing.Size(5, 5);
            // 
            // artillery1
            // 
            this.artillery1.FillColor = System.Drawing.SystemColors.Control;
            this.artillery1.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.artillery1.Location = new System.Drawing.Point(84, 120);
            this.artillery1.Name = "artillery1";
            this.artillery1.Size = new System.Drawing.Size(5, 5);
            // 
            // lineShape2
            // 
            this.lineShape2.BorderColor = System.Drawing.SystemColors.Control;
            this.lineShape2.Name = "lineShape2";
            this.lineShape2.X1 = 359;
            this.lineShape2.X2 = 434;
            this.lineShape2.Y1 = 162;
            this.lineShape2.Y2 = 185;
            this.lineShape2.Click += new System.EventHandler(this.lineShape2_Click);
            // 
            // lineShape1
            // 
            this.lineShape1.BorderColor = System.Drawing.SystemColors.Control;
            this.lineShape1.Name = "lineShape1";
            this.lineShape1.X1 = 90;
            this.lineShape1.X2 = 165;
            this.lineShape1.Y1 = 143;
            this.lineShape1.Y2 = 166;
            this.lineShape1.Click += new System.EventHandler(this.lineShape1_Click);
            // 
            // player1
            // 
            this.player1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.player1.FillColor = System.Drawing.SystemColors.Control;
            this.player1.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.player1.Location = new System.Drawing.Point(43, 162);
            this.player1.Name = "player1";
            this.player1.Size = new System.Drawing.Size(50, 10);
            // 
            // player2
            // 
            this.player2.BackColor = System.Drawing.SystemColors.ControlDark;
            this.player2.FillColor = System.Drawing.SystemColors.Control;
            this.player2.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.player2.Location = new System.Drawing.Point(211, 102);
            this.player2.Name = "player2";
            this.player2.Size = new System.Drawing.Size(50, 10);
            // 
            // windLabel
            // 
            this.windLabel.AutoSize = true;
            this.windLabel.Location = new System.Drawing.Point(225, 0);
            this.windLabel.Name = "windLabel";
            this.windLabel.Size = new System.Drawing.Size(85, 13);
            this.windLabel.TabIndex = 1;
            this.windLabel.Text = "[wind goes here]";
            // 
            // playerTurnText
            // 
            this.playerTurnText.AutoSize = true;
            this.playerTurnText.Location = new System.Drawing.Point(225, 248);
            this.playerTurnText.Name = "playerTurnText";
            this.playerTurnText.Size = new System.Drawing.Size(62, 13);
            this.playerTurnText.TabIndex = 2;
            this.playerTurnText.Text = "[player turn]";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 261);
            this.Controls.Add(this.playerTurnText);
            this.Controls.Add(this.windLabel);
            this.Controls.Add(this.shapeContainer1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private Microsoft.VisualBasic.PowerPacks.ShapeContainer shapeContainer1;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape2;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape1;
        private Microsoft.VisualBasic.PowerPacks.OvalShape artillery2;
        private Microsoft.VisualBasic.PowerPacks.OvalShape artillery1;
        private Microsoft.VisualBasic.PowerPacks.RectangleShape player1;
        private Microsoft.VisualBasic.PowerPacks.RectangleShape player2;
        private System.Windows.Forms.Label windLabel;
        private System.Windows.Forms.Label playerTurnText;
    }
}

