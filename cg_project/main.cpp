#include<stdio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include"Library\freeglut\freeglut.h"
#include"Library\freeglut\glut.h"
#include"Library\soil\soil.h"//is a special library used to load images
int winner = 0, count = 0, player = 1, done = 0, clear = 0, selected = 1, go = 0;//various flags used to follow user's moves
GLuint texture[25];//used to store the id of the images loaded
int	matrix[3][3] = { { 10, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
int select1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, xs[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, cs[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int mainx[10] = { 0, 150, 250, 350, 150, 250, 350, 150, 250, 350 };
int mainy[10] = { 0, 350, 350, 350, 250, 250, 250, 150, 150, 150 };// different arrays are used to calculate the different aspects in the game
int current_window = 1;
void init_window()// used to inittialize the game
{
	winner = 0, count = 0, player = 1, done = 0, clear = 0, selected = 1, go = 0;
	for (int i = 0; i < 10; i++)
	{
		select1[i] = 0;
		xs[i] = 0;
		cs[i] = 0;
	}
	int temp[3][3] = { { 10, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
			matrix[i][j] = temp[i][j];
	}

	int temp1[10] = { 0, 150, 250, 350, 150, 250, 350, 150, 250, 350 };
	for (int i = 0; i < 9; i++)
	{

		mainx[i] = temp1[i];
	}
	int temp2[10] = { 0, 350, 350, 350, 250, 250, 250, 150, 150, 150 };
	for (int i = 0; i < 9; i++)
	{

		mainy[i] = temp2[i];
	}
	current_window = 1;
}
void disptex(GLuint tex,int xmin,int xmax,int ymin,int ymax)//used to display the texture loaded
{
	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);       glVertex2f(xmin,ymin);
	glTexCoord2f(0, 1);   glVertex2f(xmin, ymax);
	glTexCoord2f(1, 1);      glVertex2f(xmax, ymax);
	glTexCoord2f(1, 0);      glVertex2f(xmax, ymin);
	glEnd();
	glDisable(GL_BLEND); 
	glDisable(GL_TEXTURE_2D);
}
void calc(int tile, int p)//this function contains the main logic to calculate the winner 
{
	int row = 0, i, j;
	int col = 0;
	if (winner == 0)
	{

		row = --tile / 3;
		col = tile % 3;
		//checking diagonal possibilities
		if ((matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2]) || (matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0]))
			winner = p;
		else
		{
			for (j = 0; j <= 2; j++)
			{//checking row-wise and column-wise possiblities
				if ((matrix[j][0] == matrix[j][1] && matrix[j][0] == matrix[j][2]) || (matrix[0][j] == matrix[1][j] && matrix[0][j] == matrix[2][j]))
					winner = p;
			}
		}

	}
}
void drawx(int x, int y)//used to draw the symbol 'x'
{
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x - 25, y + 25);
	glVertex2f(x - 20, y + 25);
	glVertex2f(x + 25, y - 25);
	glVertex2f(x + 20, y - 25);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(x - 25, y - 25);
	glVertex2f(x - 20, y - 25);
	glVertex2f(x + 25, y + 25);
	glVertex2f(x + 20, y + 25);
	glEnd();
}
void drawc(int x, int y)//used to draw the symbol 'o'
{
	float t, tr, x1, y1, x2, y2, r1 = 25, r2 = 30;
	glColor3f(0, 0, 1);

	glBegin(GL_QUAD_STRIP);
	for (t = 0; t <= 360; t += 5)
	{
		tr = t*(3.142 / 180);
		x1 = x + (r1*cos(tr));
		y1 = y + (r1*sin(tr));
		x2 = x + (r2*cos(tr));
		y2 = y + (r2*sin(tr));

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void lines(int h, int x1, int y1, int x2, int y2)//used to draw the layout of the game
{
	if (h == 1)
	{
		glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x1, y1 + 5);
		glVertex2f(x2, y1 + 5);
		glVertex2f(x2, y1);// horizontal line
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glVertex2f(x1 + 5, y1);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x1 + 5, y2);//Vertical line
		glEnd();

	}
}

void load_texture()//function used to load the texture
{
	texture[0] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\wall.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y 
		);
	texture[1] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\play1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[2] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\play2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[3] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\exit1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[4] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\exit2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[5] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\re1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[6] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\re2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[7] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\exit1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[8] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\exit2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[9] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\title.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[10] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\step1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[11] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\step2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[12] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\step3.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[13] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\how1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[14] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\how2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	texture[15] = SOIL_load_OGL_texture
		(
		"C:\\Users\\Admin\\Desktop\\icons\\close1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
}
void help()//window on instructions about the game
{
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		disptex(texture[10], 50, 200, 200, 400);
		disptex(texture[11], 250, 400, 200, 400);
		disptex(texture[12], 150, 350, 5, 200);
		disptex(texture[15], 370, 450, 10, 50);
	
}
void mainmenu()//used to display the mainmenu
{
	int i;
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	selected = 1;
	disptex(texture[0],0,500,0,500);//background image
	disptex(texture[1], 200, 300, 330, 370);//play button
	disptex(texture[3], 200, 300, 130, 170);//exit button
	disptex(texture[13], 200, 300, 230, 270);//how to play button
	
}
void tic()//function  used to draw x and o appropriately
{
	int i;
	selected = 2;
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	lines(1, 100, 300, 400, 0);//upper horizontal line

	lines(1, 100, 200, 400, 0);//lower horizontal line

	lines(0, 200, 100, 0, 400);//left vertical line

	lines(0, 300, 100, 0, 400);//right vertical line
	glColor3f(1, 0, 0);
	disptex(texture[5],75,175,30,70);
	disptex(texture[7], 345, 445, 30, 70);
	
	if (selected == 2 && go == 1)
	{
		for (i = 1; i <= 10; i++)
		{
			if (select1[i] != 0)
			{
				if (xs[i] == 1)
				{
					drawx(mainx[select1[i]], mainy[select1[i]]);
				}
				if (cs[i] == 1)
				{
					drawc(mainx[select1[i]], mainy[select1[i]]);
				}
			}
		}
	}
}
void display()//coordinates the above three functions
{

	int i;
	if (selected == 1 && go == 0)
	{
		glColor3f(1, 0, 0);

		mainmenu();

	}
	if (go == 1)
	{
		tic();


	}
	if (selected == 3)
	{
		help();
	}
	disptex(texture[9],50,450,420,490);
	glFlush();
}

void mouse_sq(int x, int y, int tile)//analyses and identifies the box clicked
{

	if (player == 1)//for player1
	{
		matrix[x][y] = 1;
		calc(tile, player);
		select1[tile] = tile;
		xs[tile] = 1;
		cs[tile] = 0;
		player = 2;
	}
	else//for player 2
	{
		matrix[x][y] = 0;
		calc(tile, player);
		select1[tile] = tile;
		cs[tile] = 1;
		xs[tile] = 0;
		player = 1;
	}
}
void printt(char *str)//used to print the text on the screen
{
	glColor3f(1,0,0);
	glRasterPos2i(200, 50);
	for (int i = 0; i <= strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}
void mymouse(int b, int s, int x, int y)//used to calculate the mouse coordinates
{
	int i; int cx, cy; char res[50];
	y = 500 - y;

	if (selected == 1)//in mainmenu
	{
		if (x <= 300 && x >= 200 && y <= 370 && y >= 330)//play button
		{	
			disptex(texture[2], 200, 300, 330, 370);
			go = 1;
			glFlush();
		}
		if (x <= 300 && x >= 200 && y <= 270 && y >= 230)//how to play button
		{
			disptex(texture[14], 200, 300, 230, 270);
			selected = 3;
			go = 0;
			glFlush();
		}
		if (x <= 300 && x >= 200 && y <= 170 && y >= 130)//exit button 
		{
			disptex(texture[4], 200, 300, 130, 170);
			exit(0);
			glFlush();
		}
	}
	if (selected == 3)//in how to play window
		if (x >= 370 && x <= 450 && y >= 10 && y <= 50)
			selected = 1;
	if (winner == 0 && selected == 2 && go == 1 && count<9)
	{
		if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)

		{
			if (x <= 200 && x >= 100 && y <= 400 && y >= 305 && matrix[0][0] == 10)
			{
				count++;
				mouse_sq(0, 0, 1);
				//Tile no (0,0)
			}
			if (x <= 300 && x >= 205 && y <= 400 && y >= 305 && matrix[0][1] == 2)
			{
				count++;
				mouse_sq(0, 1, 2);
				//Tile no (0,1)
			}
			if (x <= 400 && x >= 305 && y <= 400 && y >= 305 && matrix[0][2] == 3)
			{
				count++;
				mouse_sq(0, 2, 3);
				//Tile no (0,2)
			}
			if (x <= 200 && x >= 100 && y <= 300 && y >= 205 && matrix[1][0] == 4)
			{
				count++;
				mouse_sq(1, 0, 4);
				//Tile no (1,0)
			}
			if (x <= 300 && x >= 205 && y <= 300 && y >= 205 && matrix[1][1] == 5)
			{
				count++;
				mouse_sq(1, 1, 5);
				//Tile no (1,1)
			}
			if (x <= 400 && x >= 305 && y <= 300 && y >= 205 && matrix[1][2] == 6)
			{
				count++;
				mouse_sq(1, 2, 6);
				//Tile no (1,2)
			}
			if (x <= 200 && x >= 100 && y <= 200 && y >= 100 && matrix[2][0] == 7)
			{
				count++;
				mouse_sq(2, 0, 7);
				//Tile no (2,0)
			}
			if (x <= 300 && x >= 205 && y <= 200 && y >= 100 && matrix[2][1] == 8)
			{
				count++;
				mouse_sq(2, 1, 8);
				//Tile no (2,1)
			}
			if (x <= 400 && x >= 305 && y <= 200 && y >= 100 && matrix[2][2] == 9)
			{
				count++;
				mouse_sq(2, 2, 9);
			    //Tile no (2,2)
			}
		}
	}
	else if (selected == 2)
	{
		strcpy(res, " ");
		done = 1;
		if (winner == 1)// winner is player 1
		{
			strcpy(res, " Player 1 Wins ");
			printt(res);
		}
		else if (winner == 2)//winner is player 2
		{
			strcpy(res, "Player 2 Wins");
			printt(res);
		}
		if (count >= 9 && winner == 0)//in case of a tie 
		{

			strcpy(res, "No Winner !!!");
			printt(res);
		}
	}
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN &&  selected == 2)
	{
		if (x >= 75 && x <= 175 && y >= 30 && y <= 70)//restart button
		{
			init_window();
			selected = 2;
			go = 1;
			winner = 0;
			disptex(texture[6], 75, 175, 30, 70);
		}
		if (x >= 345 && x <= 445 && y >= 30 && y <= 70)//exit button
		{
			exit(0);
			disptex(texture[8], 345, 445, 30, 70);
		}
	}
	glFlush();
}

void myinit()//used to initialize the orthogonal space 
{
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, 1, -1);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char *argv[])//main function
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("TIC TAC TOE");
	myinit();
	load_texture();
	glutDisplayFunc(display);
	glutMouseFunc(mymouse);
	glutMainLoop();
}