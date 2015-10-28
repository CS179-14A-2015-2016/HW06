using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        bool turn, ballIsPlayed, launched;
        int px, px_prev, px_pprev, py, py_prev, py_pprev;
        int vx0, vy0, vwind;
        public Form1()
        {
            InitializeComponent();
            turn = true;
            ballIsPlayed = false;
            Random random = new Random();
            int randomX1 = random.Next(0, 200);
            int randomX2 = random.Next(275, 425);
            int randomY1 = random.Next(50, 250);
            int randomY2 = random.Next(50, 250);
            player1.Location = new System.Drawing.Point(randomX1, randomY1);
            player2.Location = new System.Drawing.Point(randomX2, randomY2);
            artillery1.Location = new System.Drawing.Point(player1.Location.X + 25, player1.Location.Y + 5);
            artillery2.Location = new System.Drawing.Point(player2.Location.X + 25, player2.Location.Y + 5);
            lineShape1.X1 = player1.Location.X + 25;
            lineShape1.Y1 = player1.Location.Y + 5;
            lineShape1.X2 = player1.Location.X;
            lineShape1.Y2 = player1.Location.Y;
            lineShape2.X1 = player2.Location.X + 25;
            lineShape2.Y1 = player2.Location.Y + 5;
            lineShape2.X2 = player2.Location.X;
            lineShape2.Y2 = player2.Location.Y;
            timer1.Enabled = true;
            vwind = random.Next(-100, 100);
            playerTurnText.Text = "Player 1 Turn.";
        }

        private void lineShape2_Click(object sender, EventArgs e)
        {
            launched = true;
            vx0 = -(PointToClient(Cursor.Position).X - artillery2.Location.X + vwind);
            vy0 = PointToClient(Cursor.Position).Y - artillery2.Location.Y;
        }

        private void lineShape1_Click(object sender, EventArgs e)
        {
            launched = true;
            vx0 = PointToClient(Cursor.Position).X - artillery1.Location.X + vwind;
            vy0 = PointToClient(Cursor.Position).Y - artillery1.Location.Y;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            windLabel.Text = "Wind: " + vwind.ToString() + " units.";
            int a1 = (PointToClient(Cursor.Position).X - lineShape1.X1);
            int o1 = (PointToClient(Cursor.Position).Y - lineShape1.Y1);
            double h1 = (Math.Sqrt(((a1 * a1) + (o1 * o1))));

            int a2 = (PointToClient(Cursor.Position).X - lineShape1.X1);
            int o2 = (PointToClient(Cursor.Position).Y - lineShape1.Y1);
            double h2 = (Math.Sqrt(((a2 * a2) + (o2 * o2))));

            if (turn == true && h1 <= 200)
            {
                ResetLineShape2();
                lineShape1.X2 = PointToClient(Cursor.Position).X;
                lineShape1.Y2 = PointToClient(Cursor.Position).Y;
            }
            if (turn == true && h1 > 200)
            {
                ResetLineShape2();
                lineShape1.X2 = PointToClient(Cursor.Position).X;
                lineShape1.Y2 = PointToClient(Cursor.Position).Y;
            }
            if (turn == false && h2 <= 200)
            {
                ResetLineShape1();
                lineShape2.X2 = PointToClient(Cursor.Position).X;
                lineShape2.Y2 = PointToClient(Cursor.Position).Y;
            }
            if (turn == false && h2 > 200)
            {
                ResetLineShape1();
                lineShape2.X2 = PointToClient(Cursor.Position).X;
                lineShape2.Y2 = PointToClient(Cursor.Position).Y;
            }

            if (launched == true && turn == true)
            {
                px = artillery1.Location.X;
                py = artillery1.Location.Y;

                px =  px + vx0/10;

                py += (vy0 + 10)/10;
                vy0 += 10;
                artillery1.Location = new System.Drawing.Point(px, py);
                if ((artillery1.Location.X >= player2.Location.X && artillery1.Location.X <= player2.Location.X + player2.Width && artillery1.Location.Y <= player2.Location.Y && artillery1.Location.Y <= player2.Location.Y + player2.Height))
                {
                    artillery1.Location = new System.Drawing.Point(0 ,0);
                    MessageBox.Show("Player 1 Wins!");
                    Close();
                }
                else if (artillery1.Location.Y >= 300 || artillery1.Location.X >= 500 || artillery1.Location.X <= 0)
                {
                    launched = false;
                    turn = false;
                    artillery1.Location = new System.Drawing.Point(player1.Location.X + 25, player1.Location.Y + 5);
                    Random randomizeWind = new Random();
                    vwind = randomizeWind.Next(-100, 100);
                    playerTurnText.Text = "Player 2 Turn.";
                }
            }

            if (launched == true && turn == false)
            {
                px = artillery2.Location.X;
                py = artillery2.Location.Y;

                px = px - vx0 / 10;

                py += (vy0 + 10) / 10;
                vy0 += 10;
                artillery2.Location = new System.Drawing.Point(px, py);
                if (artillery2.Location.X >= player1.Location.X && artillery2.Location.X <= player1.Location.X + player1.Width && artillery2.Location.Y <= player1.Location.Y && artillery2.Location.Y <= player1.Location.Y + player1.Height)
                {
                    artillery2.Location = new System.Drawing.Point(artillery2.Location.X, artillery2.Location.Y);
                    MessageBox.Show("Player 2 Wins!");
                    Close();
                }
                else if (artillery2.Location.Y >= 300 || artillery2.Location.X >= 500 || artillery2.Location.X <= 0)
                {
                    launched = false;
                    turn = true;
                    artillery2.Location = new System.Drawing.Point(player2.Location.X + 25, player2.Location.Y + 5);
                    Random randomizeWind = new Random();
                    vwind = randomizeWind.Next(-100, 100);
                    playerTurnText.Text = "Player 1 Turn.";
                }
            }
        }

        private void ResetLineShape1()
        {
            lineShape1.X1 = player1.Location.X + 25;
            lineShape1.Y1 = player1.Location.Y + 5;
            lineShape1.X2 = player1.Location.X;
            lineShape1.Y2 = player1.Location.Y;
        }

        private void ResetLineShape2()
        {
            lineShape2.X1 = player2.Location.X + 25;
            lineShape2.Y1 = player2.Location.Y + 5;
            lineShape2.X2 = player2.Location.X;
            lineShape2.Y2 = player2.Location.Y;
        }
    }
}
