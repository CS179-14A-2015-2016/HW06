// PongGame.cpp : Pong game using c++ and openGL *sigh*.

#include "stdafx.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL/freeglut.h"
#pragma comment(lib, "OpenGL32.lib") //specify linker options

//key define
#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44
#define VK_F 0x46
#define VK_L 0x4C

using namespace std;

//window size and refresh rate
int width = 1000;
int height = 500;
int refresh = 1000 / 60;

//land specs
float land_width = 100;
float land_height = 50;

//tank specs
float tank_width = 20;
float tank_height = 10;
float tank_speedx1 = 1;
float tank_speedy1 = 0;
float tank_speedx2 = 1;
float tank_speedy2 = 0;

//tank position
float tank1_posx = land_width / 2;
float tank1_posy = land_height;
float tank2_posx = width - (land_width / 2) - 8;
float tank2_posy = land_height;

//powergauge
float p1gauge_posx = tank1_posx;
float p1gauge_posy = land_height * 3;

float gauge_height = 1;
float gauge_width = 10;
float gauge_maxheight = p1gauge_posy + 30;
float gauge_fill = 2;

//scoring
int p1score = 0;
int p2score = 0;
int p1life = 5;
int p2life = 5;

//bullet
float velocityOriginal;
float launchAngle;
float bulletX = tank1_posx + (tank_width / 2);
float bulletY = tank1_posy + (tank_width / 2);
bool bulletFire = false;
float bulletSize = 5;
int bullet_segments = 8;
float windVelocity = 0;
float t = 0;

//turns
bool player2 = false;
bool gameStart = false;

/*
//ball shenanigans
//ball1
float bulletX = width / 2 + 10;
float bulletY = height / 2;
float ball_dirx = -1.0;
float ball_diry = 1.0;

//ball2
float ball2_posx = width / 2 - 10;
float ball2_posy = height / 2;
float ball2_dirx = 1.0;
float ball2_diry = -1.0;

float ball_speedx1 = 4;
float ball_speedy1 = 0;
float ball_speedx2 = -4;
float ball_speedy2 = 0;
float ball_radius = 5;
int ball_segments = 8;
*/

//function functions

//int to string function
string inttostr(int x) {
	//converts an int to a string using sstream lib
	stringstream convs;
	convs << x;
	return convs.str();
}

/*
//clamp function
float clamp(float n, float lower, float upper) {
n = (n > lower) * n + !(n > lower) * lower;
return (n < upper) * n + !(n < upper) * upper;
}
*/

//void functions

//keyboard controls
void keyboard() {
	//gauge power
	if (GetAsyncKeyState(VK_W))
	{
		if (gauge_height <= gauge_maxheight)
		{
			gauge_height += gauge_fill;
		}
	}

	if (GetAsyncKeyState(VK_S))
	{
		if (gauge_height > 1)
		{
			gauge_height -= gauge_fill;
		}
	}

	/*
	if (GetAsyncKeyState(VK_S))
	{
		if ((leftpaddle_y) >= 0)
		{
		paddle_speedy1 = -6;
		leftpaddle_y += paddle_speedy1;
		paddle_speedy1 = 1; leftpaddle_y;
		}
	}

	//right paddle
	if (GetAsyncKeyState(VK_UP))
	{
		if ((rightpaddle_y + paddle_height) <= height)
		{
		paddle_speedy2 = 6;
		rightpaddle_y += paddle_speedy2;
		paddle_speedy2 = 1;
		}
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if ((rightpaddle_y) >= 0)
		{
		paddle_speedy2 = -6;
		rightpaddle_y += paddle_speedy2;
		paddle_speedy2 = 1;
		}
	}
	*/
}


//makes gl recognized 2d usage
void use2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//prints text on screen
void textDraw(float x, float y, string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

//draw paddles
void boxDraw(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

//draw the ball
void ballDraw(float cx, float cy, float r, int segments) {
	float theta = 2 * 3.1415926 / float(segments);
	//sin and cos calculation
	float cos = cosf(theta);
	float sin = sinf(theta);
	float t;

	float varx = r; //start at angle 0
	float vary = 0;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		glVertex2f(varx + cx, vary + cy); //outputs vertex

										  //apply rotation matrix
		t = varx;
		varx = cos * varx - sin * vary;
		vary = sin * t + cos * vary;
	}
	glEnd();
}

void boom()
{
	gameStart = false;
	if (player2 == true)
	{
		bulletX = tank1_posx + (tank_width / 2);
		bulletY = tank1_posy + (tank_height / 2);
		player2 = false;

	}
	else if (player2 == false)
	{
		bulletX = tank2_posx + (tank_width / 2);
		bulletY = tank2_posy + (tank_height / 2);
		player2 = true;

	}
}

void bulletMove()
{
	if (gameStart == true)
	{
		if (player2 == false)
		{
			bulletX += ((velocityOriginal + windVelocity)*t)*cos(launchAngle);
			bulletY += (velocityOriginal*t)*sin(launchAngle) - ((9.8*(t*t)) / 2);
		}
		else if (player2 == true)
		{
			bulletX -= ((velocityOriginal + windVelocity)*t)*cos(launchAngle);
			bulletY += (velocityOriginal*t)*sin(launchAngle) - ((9.8*(t*t)) / 2);
		}

	}


}

void collisionChecker() {
	//left wall collision
	if (bulletX < 0) {
		boom();
	}

	//right wall collision
	if (bulletX > width) {
		boom();
	}

	//top /bot wall collision
	if (bulletY > height - 20 || bulletY < 10)
	{
		boom();
	}
	if (gameStart = true)
	{
		if ((bulletX >= tank1_posx) &&
			(bulletX <= tank1_posx + tank_width) &&
			(bulletY <= tank1_posy + tank_height) &&
			(bulletY >= tank1_posy))
		{
			if (player2 == true)
			{
				p2score += 1;
			}
			p1life -= 1;
			boom();
		}
		if ((bulletX >= tank2_posx) &&
			(bulletX <= tank2_posx + tank_width) &&
			(bulletY <= tank2_posy + tank_height) &&
			(bulletY >= tank2_posy))
		{
			if (player2 == false)
			{
				p1score += 1;
			}
			p2life -= 1;
			boom();
		}
	}
}

//draw on screen
void draw() {
	//clearing the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//put draw codes below

	//ball display
	ballDraw(bulletX, bulletY, bulletSize, bullet_segments);
	//ballDraw(ball2_posx, ball2_posy, ball_radius, ball_segments);

	//land display
	boxDraw(0, 0, land_width, land_height);
	boxDraw(width - land_width - 8, 0, land_width, land_height);

	//tank draw
	boxDraw(tank1_posx, tank1_posy, tank_width, tank_height);
	boxDraw(tank2_posx, tank2_posy, tank_width, tank_height);

	//gauge draw
	boxDraw(p1gauge_posx, p1gauge_posy, gauge_width, gauge_height);


	//score display
	textDraw(width / 2 - 30, height - 30, inttostr(p1score) + " : " + inttostr(p2score));

	//swapping buffers
	glutSwapBuffers();
}

//screen update handler
void update(int upvalue) {
	//input
	keyboard();

	//ball movement
	bulletMove();

	if (gameStart == true)
	{
		t += 1;
	}
	//ball2Move();

	//calls update in millisecs
	glutTimerFunc(refresh, update, 0);

	//Redisplay Frame
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//initiliaze opengl using glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Le Pong");

	//uses the void functions
	glutDisplayFunc(draw);
	glutTimerFunc(refresh, update, 0);

	//setup the 2d and set draw color to black
	use2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	//program loop
	glutMainLoop();

	return 0;
}

//there's no god in coding
