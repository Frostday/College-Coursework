#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <future>

using namespace std;

class Bullet
{
    public:
    float bullet_size, bullet_damage, bullet_speed, bullet_length;
    float x, y, angle;

    Bullet(float bullet_size, float bullet_damage, float bullet_speed, float bullet_length, float x, float y, float angle)
    {
        this->bullet_size = bullet_size;
        this->bullet_damage = bullet_damage;
        this->bullet_speed = bullet_speed;
        this->bullet_length = bullet_length;
        this->x = x;
        this->y = y;
        this->angle = angle;
    }

    void displayBullet()
    {
        this->x = this->x+cos(angle);
        this->y = this->y+sin(angle);
        glBegin(GL_POLYGON);
        glVertex2f(this->x, this->y-this->bullet_size/2);
        glVertex2f(this->x, this->y+this->bullet_size/2);
        glVertex2f(this->x+this->bullet_length*cos(angle), this->y+this->bullet_size/2+this->bullet_length*sin(angle));
        glVertex2f(this->x+this->bullet_length*cos(angle), this->y-this->bullet_size/2+this->bullet_length*sin(angle));
        glEnd();
    }
};

class Enemy
{
    public:
    float x, y;
    string type;
    float health, color[3]={0};

    Enemy(float x, float y, string t)
    {
        this->x = x;
        this->y = y;
        this->type.assign(t);

        if (this->type.compare("basic")==0)
        {
            health = 30;
            color[1] = 255;
        }
    }

    void displayEnemies()
    {
        this->x-=0.4;
        glBegin(GL_POLYGON);
        glVertex2f(x-50, y-50);
        glVertex2f(x-50, y+50);
        glVertex2f(x+50, y+50);
        glVertex2f(x+50, y-50);
        glEnd();
    }
};

class Agent
{
    public:
    float x=200;
    float y=200;
    float speed=1;
    float lives=3;
    int level=0;
    bool can_fire=true;
    vector<Bullet> bullets;
    vector<Enemy> enemies;

    void increaseSpeed()
    {
        this->speed++;
    };

    void decreaseSpeed()
    {
        this->speed--;
    };

    void spawnBullet()
    {
        this->can_fire=true;
        for (int i=0; i<this->bullets.size(); i++)
        {
            if (this->bullets[i].x<=x+200)
                this->can_fire=false;
        }
        if (this->can_fire)
        {
            Bullet b(10.0, 10.0, 2.0, 20.0, this->x+80.0, this->y+5.0, 0.0);
            bullets.push_back(b);
        }
    }

    void spawnEnemies()
    {
        if (enemies.size()==0)
        {
            this->level++;
            if (this->level==1)
            {
                cout<<"adding enemies";
                float x = rand() % 50 + 1500;
                float y = rand() % 1000 + 100;
                Enemy e(x, y, "basic");
                enemies.push_back(e);
            }
        }
    }

    void renderJett()
    {
        glColor3ub(255, 255, 255);
        glBegin(GL_POLYGON);
        glVertex2f(this->x, this->y);
        glVertex2f(this->x, this->y+25);
        glVertex2f(this->x+10, this->y+10);
        glVertex2f(this->x+60, this->y+10);
        glVertex2f(this->x+80, this->y);
        glVertex2f(this->x, this->y);
        glEnd();
    }

    void renderBullets()
    {
        glColor3ub(255, 255, 0);
        for (int i=0; i<this->bullets.size(); i++)
            this->bullets[i].displayBullet();
    }

    void renderEnemies()
    {
        glColor3ub(0, 255, 0);
        for (int i=0; i<this->enemies.size(); i++)
            this->enemies[i].displayEnemies();
    }

    void renderHearts()
    {
        glColor3ub(255, 0, 0);
        int i;
        for (i=0; i<this->lives; i++)
        {
            float centerX=1600+i*50, centerY=1100;
            glBegin(GL_POLYGON);
            glVertex2f(centerX, centerY-15);
            glVertex2f(centerX-20, centerY+20);
            glVertex2f(centerX-10, centerY+30);
            glVertex2f(centerX, centerY+20);
            glVertex2f(centerX+10, centerY+30);
            glVertex2f(centerX+20, centerY+20);
            glEnd();
        }
        while (i<3)
        {
            float centerX=1600+i*50, centerY=1100;
            glBegin(GL_LINE_LOOP);
            glVertex2f(centerX, centerY-15);
            glVertex2f(centerX-20, centerY+20);
            glVertex2f(centerX-10, centerY+30);
            glVertex2f(centerX, centerY+20);
            glVertex2f(centerX+10, centerY+30);
            glVertex2f(centerX+20, centerY+20);
            glEnd();
            i++;
        }
        glColor3ub(255, 255, 255);
        string str;
        if (level==0)
            str="Level 0";
        else if (level==1)
            str="Level 1";
        else if (level==2)
            str="Level 2";
        else if (level==3)
            str="Level 3";
        else if (level==4)
            str="Level 4";
        else
            str="Level 5";
        glRasterPos2i(800, 1080);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}agent;

bool keybuffer[256] = {0};

void keyPress(unsigned char key, int x, int y)
{
	keybuffer[key]=true;
}

void keyRelease(unsigned char key, int x, int y)
{
	keybuffer[key]=false;
}

void keyOperations()
{
    if (keybuffer['w']==true)
        if (agent.y<=1200-25)
            agent.y += agent.speed;
    if (keybuffer['s']==true)
        if (agent.y>=0)
            agent.y -= agent.speed;
    if (keybuffer['d']==true)
        if (agent.x<=1800-80)
            agent.x += agent.speed;
    if (keybuffer['a']==true)
        if (agent.x>=0)
            agent.x -= agent.speed;
    if (keybuffer[' ']==true)
        agent.spawnBullet();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    keyOperations();

    agent.renderJett();
    agent.renderBullets();
    agent.renderHearts();
    agent.renderEnemies();

    if (agent.enemies.size()==0)
    {
        cout<<"spawning";
        agent.spawnEnemies();
    }

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1800.0, 0.0, 1200.0);
}

void frame_rate(GLint msecs)
{
    // timer function - to make frame rate constant - stop jittering
    // also glutPostRedisplay will be called here now
    glutPostRedisplay();
    glutTimerFunc(msecs, frame_rate, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Computer Graphics Project");
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    frame_rate(10);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
