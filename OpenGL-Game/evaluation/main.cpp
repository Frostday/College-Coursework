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
#define PI 3.14159

using namespace std;

bool start=true, game_over=false, victory=false;

void semiCircle(float r, float cx, float cy)
{
    glBegin(GL_TRIANGLE_FAN);

    for (float i = 1.5*PI; i <= 2*PI; i += 0.02)
        glVertex2f(cx+(sin(i)*r), cy+(cos(i)*r));
    for (float i = 0; i <= 0.5*PI; i += 0.02)
        glVertex2f(cx+(sin(i)*r), cy+(cos(i)*r));

    glEnd();
}

void circle(float r, float cx, float cy)
{
    glBegin(GL_TRIANGLE_FAN);

    for (float i = 0; i <= 2.0*PI; i += 0.02)
        glVertex2f(cx+(sin(i)*r), cy+(cos(i)*r));

    glEnd();
}

class Rect
{
    public:
    float x, y, h, w;

    Rect()
    {
        this->x = 0;
        this->y = 0;
        this->h = 0;
        this->w = 0;
    }

    Rect(float x, float y, float h, float w)
    {
        this->x = x;
        this->y = y;
        this->h = h;
        this->w = w;
    }

    bool detectCollision(Rect r)
    {
        bool collision=false;
        if (this->x < r.x + r.w &&
            this->x + this->w > r.x &&
            this->y < r.y + r.h &&
            this->h + this->y > r.y) {
                collision=true;
        }
        return collision;
    }

    void update(float x, float y, float h, float w)
    {
        this->x = x;
        this->y = y;
        this->h = h;
        this->w = w;
    }
};

class Bullet
{
    public:
    float bullet_size, bullet_damage, bullet_speed, bullet_length;
    float x, y, angle;
    Rect r;

    Bullet(float bullet_size, float bullet_damage, float bullet_speed, float bullet_length, float x, float y, float angle)
    {
        this->bullet_size = bullet_size;
        this->bullet_damage = bullet_damage;
        this->bullet_speed = bullet_speed;
        this->bullet_length = bullet_length;
        this->x = x;
        this->y = y;
        this->angle = angle;
        Rect temp(x, y, bullet_size, bullet_length);
        this->r = temp;
    }

    bool displayBullet()
    {
        if (this->x>=1800 || this->y>=1200 || this->x<=0 || this->y<=0)
            return true;
        this->x = this->x+cos(angle);
        this->y = this->y+sin(angle);
        glBegin(GL_POLYGON);
        glVertex2f(this->x, this->y);
        glVertex2f(this->x, this->y+this->bullet_size);
        glVertex2f(this->x+this->bullet_length*cos(angle), this->y+this->bullet_size+this->bullet_length*sin(angle));
        glVertex2f(this->x+this->bullet_length*cos(angle), this->y+this->bullet_length*sin(angle));
        glEnd();
        this->r.update(this->x, this->y, bullet_size, bullet_length);
        return false;
    }
};

class Enemy
{
    public:
    float x, y;
    string type, text;
    float health;
    Rect r;

    Enemy(float x, float y, string t, int num)
    {
        this->x = x;
        this->y = y;
        this->type.assign(t);
        this->text.assign(to_string(num));

        if (this->type.compare("basic")==0)
        {
            this->health = 30;
            Rect temp(this->x, this->y, 110, 100);
            this->r = temp;
        }
        if (this->type.compare("chonk")==0)
        {
            this->health = 70;
            Rect temp(this->x, this->y, 110, 100);
            this->r = temp;
        }
        if (this->type.compare("speedy")==0)
        {
            this->health = 20;
            Rect temp(this->x, this->y, 110, 100);
            this->r = temp;
        }
    }

    int displayEnemies()
    {
        if (this->x<=0)
            return 2;
        else if (this->x>=1800 || this->y>=1200 || this->y<-100)
            return 1;
        if (this->type.compare("basic")==0)
        {
            glColor3ub(0, 255, 0);
            this->x-=0.4;
            semiCircle(50, x+50, y+60);
            glBegin(GL_POLYGON);
            glVertex2f(x, y+30);
            glVertex2f(x+100, y+30);
            glVertex2f(x+100, y+60);
            glVertex2f(x, y+60);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x, y+50);
            glVertex2f(x+30, y+50);
            glVertex2f(x+30, y);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x+70, y);
            glVertex2f(x+70, y+50);
            glVertex2f(x+100, y+50);
            glVertex2f(x+100, y);
            glEnd();
            glColor3ub(0, 0, 0);
            circle(20, x+25, y+70);
            glColor3ub(255, 255, 255);
            circle(7, x+20, y+75);
            r.update(this->x, this->y, 100, 100);
            //glColor3ub(0, 0, 255);
            //glRasterPos2i(this->x, this->y);
            //for (int i=0; i<this->text.length(); i++)
                //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->text[i]);
            return 0;
        }
        else if (this->type.compare("chonk")==0)
        {
            glColor3ub(0, 0, 255);
            this->x-=0.2;
            semiCircle(50, x+50, y+60);
            glBegin(GL_POLYGON);
            glVertex2f(x, y+30);
            glVertex2f(x+100, y+30);
            glVertex2f(x+100, y+60);
            glVertex2f(x, y+60);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x, y+50);
            glVertex2f(x+30, y+50);
            glVertex2f(x+30, y);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x+70, y);
            glVertex2f(x+70, y+50);
            glVertex2f(x+100, y+50);
            glVertex2f(x+100, y);
            glEnd();
            glColor3ub(0, 0, 0);
            circle(20, x+25, y+70);
            glColor3ub(255, 255, 255);
            circle(7, x+20, y+75);
            r.update(this->x, this->y, 100, 100);
            return 0;
        }
        else if (this->type.compare("speedy")==0)
        {
            glColor3ub(255, 0, 0);
            this->x-=0.6;
            semiCircle(50, x+50, y+60);
            glBegin(GL_POLYGON);
            glVertex2f(x, y+30);
            glVertex2f(x+100, y+30);
            glVertex2f(x+100, y+60);
            glVertex2f(x, y+60);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x, y+50);
            glVertex2f(x+30, y+50);
            glVertex2f(x+30, y);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex2f(x+70, y);
            glVertex2f(x+70, y+50);
            glVertex2f(x+100, y+50);
            glVertex2f(x+100, y);
            glEnd();
            glColor3ub(0, 0, 0);
            circle(20, x+25, y+70);
            glColor3ub(255, 255, 255);
            circle(7, x+20, y+75);
            r.update(this->x, this->y, 100, 100);
            return 0;
        }
    }
};

class Agent
{
    public:
    float x=200;
    float y=300;
    Rect r;
    float speed=1;
    float lives=3;
    int level=0;
    bool can_fire=true;
    vector<Bullet> bullets;
    vector<Enemy> enemies;

    Agent()
    {
        Rect temp(this->x, this->y, 25, 80);
        this->r = temp;
    }

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
            Bullet b(10.0, 10.0, 2.0, 20.0, this->x+80.0, this->y, 0.0);
            bullets.push_back(b);
        }
    }

    void spawnEnemies()
    {
        float x, y;
        if (enemies.size()==0)
        {
            this->level++;
            if (this->lives==0)
                game_over = true;
            if (this->level==6)
                victory=true;
            if (this->level==1)
            {
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 1));
            }
            if (this->level==2)
            {
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 1));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 2));
            }
            if (this->level==3)
            {
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 1));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 2));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "chonk", 3));
            }
            if (this->level==4)
            {
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 1));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 2));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "speedy", 3));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "chonk", 4));
            }
            if (this->level==5)
            {
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 1));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "basic", 2));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "speedy", 3));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "speedy", 4));
                x = rand() % 50 + 1500;
                y = rand() % 900 + 100;
                enemies.push_back(Enemy(x, y, "chonk", 5));
            }
        }
    }

    void detectCollisions()
    {
        bool collision, erased=false;
        int i=0, j=0;
        while(i<enemies.size())
        {
            collision = this->r.detectCollision(enemies[i].r);
            if (collision)
            {
                this->lives--;
                enemies.erase(enemies.begin() + i);
                //cout<<"lose hearts"<<endl;
                continue;
                // add timer function
            }
            j = 0;
            while(j<bullets.size())
            {
                erased = false;
                collision = bullets[j].r.detectCollision(enemies[i].r);
                //cout<<collision<<" "<<i<<" "<<j<<" "<<erased<<endl;
                if (collision)
                {
                    //cout<<"delete bullet"<<endl;
                    enemies[i].health -= bullets[j].bullet_damage;
                    bullets.erase(bullets.begin() + j);
                    if (enemies[i].health <= 0)
                    {
                        //cout<<"delete enemy"<<endl;
                        enemies.erase(enemies.begin() + i);
                        erased = true;
                    }
                }
                else
                    j++;
            }
            if (erased==0)
                i++;
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
        this->r.update(this->x, this->y, 25, 80);
    }

    void renderBullets()
    {
        bool del=false;
        int i=0;
        glColor3ub(255, 255, 0);
        while (i<this->bullets.size())
        {
            del = this->bullets[i].displayBullet();
            if (del)
                bullets.erase(bullets.begin() + i);
            else
                ++i;
        }
    }

    void renderEnemies()
    {
        int del;
        int i=0;
        while (i<this->enemies.size())
        {
            del = this->enemies[i].displayEnemies();
            if (del==1)
                enemies.erase(enemies.begin() + i);
            if (del==2)
            {
                this->lives--;
                enemies.erase(enemies.begin() + i);
            }
            else
                ++i;
        }
    }

    void renderHearts()
    {
        if (this->lives==0)
            game_over = true;
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
        else if (level==5)
            str="Level 5";
        glRasterPos2i(800, 1080);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }

    void generateBackground()
    {
        glColor3ub(150, 150, 150);
        circle(1000, 2200, -300);
        glColor3ub(255, 255, 255);
        glPointSize(6);
        glBegin(GL_POINTS);
        glVertex2f(100, 500);
        glVertex2f(1000, 100);
        glVertex2f(1150, 800);
        glVertex2f(700, 600);
        glVertex2f(400, 1000);
        glVertex2f(1400, 1100);
        glVertex2f(1700, 800);
        glVertex2f(200, 200);
        glEnd();
        glPointSize(1);
    }

    void startScreen()
    {
        string str;
        glColor3ub(255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Starting in 5";
        glRasterPos2i(700, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Starting in 4";
        glRasterPos2i(700, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Starting in 3";
        glRasterPos2i(700, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Starting in 2";
        glRasterPos2i(700, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Starting in 1";
        glRasterPos2i(700, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Go!";
        glRasterPos2i(800, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
        sleep(1);
    }

    void endScreen()
    {
        string str;
        glColor3ub(255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Game Over! :(";
        glRasterPos2i(800, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glFlush();
    }

    void victoryScreen()
    {
        string str;
        glColor3ub(255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        str = "Victory! :)";
        glRasterPos2i(800, 600);
        for (int i=0; i<str.length(); i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
        glColor3ub(255, 0, 0);
        int i;
        for (i=0; i<this->lives; i++)
        {
            float centerX=825+i*50, centerY=550;
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
            float centerX=825+i*50, centerY=550;
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
        glFlush();
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
    if (start)
    {
        agent.startScreen();
        start = false;
    }
    else if (game_over)
    {
        agent.endScreen();
        sleep(5);
        exit(0);
    }
    else if (victory)
    {
        agent.victoryScreen();
        sleep(5);
        exit(0);
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);

        keyOperations();

        agent.generateBackground();
        agent.renderJett();
        agent.renderBullets();
        agent.renderHearts();
        agent.renderEnemies();

        agent.detectCollisions();

        if (agent.enemies.size()==0)
        {
            agent.spawnEnemies();
        }

        glFlush();

    }
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
