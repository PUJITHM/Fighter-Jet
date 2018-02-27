#include <stdlib.h>
#include<stdio.h>
#include<iostream>
#include <GL/glut.h>
#include <windows.h>
#include<string.h>

static float p=-3,p1=3,q1=-5,b1[2],bc=0,bf=0;
static float q=-5,b2[2],bd=1;
static float obs[20][4]={{0,0,0,0}};
float f=11,b22;
bool bulletfired = false,gameover=false,begin=false,multiplayer=false;
int hitobj=99,score=0,life=0,shots=0;


void myinit();


void bitmap_output(int x,float y,char *string,void *font)
{
	int len,i;
	glRasterPos2f(x,y);
	len=(int)strlen(string);
	for(i=0;i<len;i++)
	{
		glutBitmapCharacter(font,string[i]);
	}
	return;
}

 void sleep(unsigned milliseconds)
 {
        Sleep(milliseconds);
 }

void drawtri(float p,float q)
{
	glBegin(GL_POLYGON);
	glColor3f(1,0.67,0.45);
		glVertex3f(p+2,q,0);
		glVertex3f(p-2,q,0);
		glVertex3f(p,q+2,0);
	
	glEnd();

	glFlush();
	
}

void drawsquar(float x,float y)
{
	glBegin(GL_POLYGON);
	glColor3f(.87,0.34,0.5);
		glVertex3f(x,y,0);
		glVertex3f(x+1.5,y,0);
		glVertex3f(x+1.5,y-1.5,0);
		glVertex3f(x,y-1.5,0);
	
	glEnd();

	glFlush();
	return;
	
}

void makeitnill(int i)
{
	obs[i][0]=0;
	obs[i][1]=0;
	obs[i][2]=0;
	obs[i][3]=0;
}

static void checkobs(float ttx,float tty,float ox,float oy,int m)
{
if(obs[m][2]==1.0)
{
 int i;
 if(b1[1]+bc+2>=(oy-1.5) && b1[1]+bc+2<=oy && bulletfired)
	 {
		 if(b1[0]<=(ox+1.5) && b1[0]>=ox)
		 {
			
			makeitnill(m);
			bulletfired=false;
			bc=0;	
			shots++;
			score++;
			if(shots==10)
			{
				if(life<3)
				life++;
				shots=0;
			}

			return;
		 }
  }
 float tx=ttx,ty=tty;
 tx = tx - 2;
 for(i=0;i<7;i++)
 {
	 if(ty>(oy-1.5) && ty<oy)
	 {
		 if(tx<(ox+1.5) && tx>ox)
		 {
			gameover=true;

			 glColor3f(1,0,0);
			 if(life==0)
				 bitmap_output(-02,0,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
			 bitmap_output(-03,-1.5,"PRESS ENTER TO CONTINUE.....",GLUT_BITMAP_TIMES_ROMAN_24);
			 hitobj=m;
			 makeitnill(m);

			 return;
		 }

	 }
	  tx = tx+(2.0/3.0);
	  if(i>2)
	   ty = ty-(2.0/3.0);
	  else
		   ty = ty+(2.0/3.0);
 } 
  
}
}

void drawobs()
{
	
	int i;
	for(i=0;i<20;i++)
	{
		
		if(obs[i][2]==1.0)
		{
			drawsquar(obs[i][0],obs[i][1]);
			if(obs[i][1]<(-10))
			{
				makeitnill(i);
				score++;

			}	
			if (multiplayer)
            checkobs(p,q,obs[i][0],obs[i][1],i);
			checkobs(p1,q1,obs[i][0],obs[i][1],i);
			obs[i][1]=obs[i][1]-0.25;
			
		}
	}
}

void firebullet()
{
	if(bulletfired)
	{
		if((b1[1]+bc)<10.0)
		{
			
	glBegin(GL_LINES);
       glVertex2f(b1[0],b1[1]+bc);
       glVertex2f(b2[0],b22+bc);
    glEnd();
    glFlush();
	}
	else
	{

		bulletfired=false;
		bf=0;
	}
		

	}
	else
	{

		bc=0;
		bf=0;
		bulletfired=false;
	}
	
}


void init1()
{
glClearColor(0.21,0.2,0,1);
glColor3f(1,0,0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,500,0,500);
glMatrixMode(GL_MODELVIEW);
}




void disp()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glColor3f(1,1,0);
bitmap_output(150,450,"SJBIT INSTUTE OF TECHNOLODGY ",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(200,250,"Press any key to start",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(300,100,"DONE BY:",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(370,75,"PUJITH M",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(370,50,"RAJAT GL",GLUT_BITMAP_TIMES_ROMAN_24);
bitmap_output(0,50,"FIGHTER JET",GLUT_BITMAP_TIMES_ROMAN_24);


glFlush();
glutSwapBuffers();
}

void display(void)
{
	if(!gameover)
	{
		char snum[5];
		itoa(score, snum, 10);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 firebullet();
		 if(multiplayer)
		 drawtri(p,q);
		 drawtri(p1,q1);
		 drawobs();
		 glFlush();
		 



		 glBegin(GL_POLYGON);
			glColor3f(0,0,1);
			glVertex2i(-10,10);
			glVertex2i(-10,11);
			glVertex2i(10,11);
			glVertex2i(10,10);
		
		glEnd();

	glFlush();
	glColor3f(0,1,0);
		

		 //bitmap
		 bitmap_output(-10,10.2,"Score: ",GLUT_BITMAP_TIMES_ROMAN_24);
		 bitmap_output(-8,10.2,snum,GLUT_BITMAP_TIMES_ROMAN_24);
		 bitmap_output(3.5,10.2,"Lifes: ",GLUT_BITMAP_TIMES_ROMAN_24);
	   	itoa(life, snum, 10);
	   	bitmap_output(5,10.2,snum,GLUT_BITMAP_TIMES_ROMAN_24);
		
		 glutSwapBuffers();

 	}
}

void mymove()
{
	if(!gameover)
	{
		int temp;
	if(f>2)
	{
	  temp=(rand()%20);
		
	  while(1)
	  {
		   int count=0;
	 if(obs[temp][2]==0)
	 {
	  f=-19;
	  obs[temp][0]=float(temp-10);
	  obs[temp][1]=10.0;
	  obs[temp][2]=1;
	  break;
	 }
	 else 
	 {
	 if (count==20)
		 break;
	 count++;
	 temp=(temp+count)%20;
	 }
	  }
	 }
	f=f+01;
	if(q>8)
			q=-10;
	if(q<-10)
			q=8;
	sleep(40);
	bc=bc+0.4;
	q=q+0.01;
	display();    
	}
	
}

void keys(unsigned char key, int x, int y)
{
	if(!begin)
	{
		glutDestroyWindow(1);
		 glutInitWindowSize(800,800);
            glutInitWindowPosition(0,0);
            glutCreateWindow("Fighter Jet");
            glutDisplayFunc(display);
			glutKeyboardFunc(keys);
			glutIdleFunc(mymove);
            myinit();
			begin=true;
			gameover=false;
	}

	if(!gameover)
	{
	if(key == 'd')
	{
		p=p+.8;
		if(p>10)
			p=-10;
	}
	if(key == 'a')
	{
		p=p-.8;
		if(p<-10)
			p=10;
		
	}
	if(key == 'w')
	{
		q=q+1.0;
		if(q>10)
			q=-10;
	}
	if(key == 's')
	{
		q=q-1.0;
		if(q<-10)
			q=10;
	}

	if(key == ' ' && !bulletfired )
	{
		bc=0;
		bulletfired=true;
		bf=1;
		b1[0]=p1;
	    b1[1]=q1;
	    b2[0]=p1;
	    b2[1]=q1+2;
		b22=q1+2;
		firebullet();
	}


	if(key == 'm' && !bulletfired && multiplayer )
	{
		bc=0;
		bulletfired=true;
		bf=1;
		b1[0]=p;
	    b1[1]=q;
	    b2[0]=p;
	    b2[1]=q+2;
		b22=q+2;
		firebullet();
	}

	}

	if(key == 13 && gameover)
	{
		if(life==0)
		{
			myinit();
			shots=0;
			life=0;
			score=0;
			int i;
			for (i=0;i<20;i++)
				makeitnill(i);
			glutDestroyWindow(1);
			glutInitWindowPosition(0,0);
			glutInitWindowSize(900,500);
			glutCreateWindow("Fighter Jet");
			glutKeyboardFunc(keys);
			init1();
			begin = false;
			glutDisplayFunc(disp);
		}
		else
		{
		life--;
		shots=0;
		gameover=false;
		}
		if(hitobj<20)
			makeitnill(hitobj);
		hitobj=99;
		//display();
		glutPostRedisplay();  

	}
	
	if (key == 27)
		exit(0);

  glutPostRedisplay();    
}


void key(int ch,int x,int y)
{
	switch(ch)
	{
	case GLUT_KEY_LEFT:{
		p1=p1-.8;
		if(p1<-10)
			p1=10;
		
	break;}
	case GLUT_KEY_RIGHT:{
		p1=p1+.8;
		if(p1>10)
			p1=-10;
	break;}
	case GLUT_KEY_UP:{
		q1=q1+1.0;
		if(q1>10)
			q1=-10;
	break;}
	case GLUT_KEY_DOWN:{
		q1=q1-1.0;
		if(q1<-10)
			q1=10;
	break;}
	}
}


void myinit()
{
           glClearColor(0.21,0.2,0,1);
            glColor3f(1.0,0.0,0.0);
            glPointSize(1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-10,10,-10,11);
			glutSpecialFunc(key);

}




int main()
{
//glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(900,500);
glutCreateWindow("Fighter Jet");
init1();
glutDisplayFunc(disp);
glutKeyboardFunc(keys);
glutSpecialFunc(key);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
return 0;
}

