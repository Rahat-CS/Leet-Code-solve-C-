
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include  <math.h>

double angle=0.0,angle1=0.0;
GLfloat angleflag=false, angleflag1=false;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat mTheta = 0.0, hTheta = 0.0, fTheta = 0.0, speed = 0.5;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

GLfloat eyeX = 0;
GLfloat eyeY = 1;
GLfloat eyeZ = 10;

GLfloat headX=0;
GLfloat headY=1;
GLfloat headZ=0;

GLfloat lookX = 1;
GLfloat lookY = 0;
GLfloat lookZ = 0;
int rr =90;

void roll() // z axis
{
    headX  = cos(rr*3.1416/180.0);
    headY = sin(rr*3.1416/180.0);
    //  printf("%lf %faR\n" , rr,cos(rr*3.1416/180.0));
}
GLboolean fanFlag = false, spotLight = false, Light1 = false, Light2 = false, ambL = true, diffL = true, specL = true;
GLboolean ambL1 = false, ambL2 = false, ambL3 = false, diffL1 = false, diffL2 = false, diffL3 = false, specL1 = false, specL2 = false, specL3 = false;
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 }, light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient1[]  = { 0.5, 0.5, 0.5, 1.0 }, light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0 };  //white
GLfloat light_ambient2[]  = {0.0, 0.0, 0.5, 1.0}, light_diffuse2[]  = { 0.0, 0.0, 1.0, 1.0 };  //blue
GLfloat light_ambient3[]  = {0.5, 0.5, 0.5, 1.0}, light_diffuse3[]  = { 1.0, 1.0, 1.0, 1.0 };  //white
static GLfloat cube1[8][3] =
{
    {0.0, 2.0,-2.0},
    {0.0, 2.0,0.0},
    {2.0,2.0,-2.0},
    {2.0,2.0,0},
    {2.0,0.0,-2.0},
    {2.0,0.0,0.0},
    {0.0,0.0,-2.0},
    {0.0,0.0,0.0}

};


static GLubyte s_Indices1[2][8] =
{
    {0, 1, 2,3,4,5,6,7},
    {3,5,1,7,0,6,2,4}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawcube(GLfloat col1, GLfloat col2, GLfloat col3)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { col1*0.5, col2*0.5, col3*0.5, 1.0 };
    GLfloat mat_diffuse[] = { col1, col2, col3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    //  glColor3f(col1,col2,col3);
    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {

//        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        glVertex3fv(&cube1[s_Indices1[i][0]][0]);
        glVertex3fv(&cube1[s_Indices1[i][1]][0]);
        glVertex3fv(&cube1[s_Indices1[i][2]][0]);
        glVertex3fv(&cube1[s_Indices1[i][3]][0]);
        glVertex3fv(&cube1[s_Indices1[i][4]][0]);
        glVertex3fv(&cube1[s_Indices1[i][5]][0]);
        glVertex3fv(&cube1[s_Indices1[i][6]][0]);
        glVertex3fv(&cube1[s_Indices1[i][7]][0]);

    }


    glEnd();



}


void Light_One()
{
    glPushMatrix();
    GLfloat light_position[] = { 2, 10.0, 10.0, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void Light_Two()
{
    glPushMatrix();
    GLfloat light_position[] = { 0.0, 8.0, 5.0, 1.0 };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void Light_Three()
{
    glPushMatrix();
    GLfloat light_position[] = { 0,0,5, 1.0 };  //-23, 2.5, -6.0
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 1, 2, -2 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
    glPopMatrix();
}
void drawname()
{
    glPushMatrix();
    glRotatef(angle1 ,0,1,0);

Naeem Mia CSE 17, [12/12/2022 00:06]
glPushMatrix();
    glRotatef(angle,0,1,0);
    glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(0.2,2.0,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glRotatef(25,0,0,1);
    glTranslatef(-2.8,1.3,0);
    glScalef(0.1,2.0,0.20);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.0,0,0);
    glScalef(0.2,2.0,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(-25,0,0,1);
    glTranslatef(-2.3,-.8,0);
    glScalef(0.2,2.0,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8,1.0,0);
    glScalef(1.3,0.2,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glRotatef(25,0,0,1);
    glTranslatef(1.0,-0.5,0);
    glScalef(0.2,2.2,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,0,0);
    glScalef(0.2,2.0,0.10);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,4.0,0);
    glScalef(1.3,0.2,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,2.0,0);
    glScalef(1.3,0.2,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8,0.0,0);
    glScalef(1.3,0.2,0.10);
    drawcube(0.197, 0.117, 0.650);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    glScalef(0.2,2.3,0.10);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-25,0,0,1);
    glTranslatef(3,6,0);
    glScalef(1,.3,0.10);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(25,0,0,1);
    glTranslatef(8,0,0);
    glScalef(1,.3,0.10);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9,0,0);
    glScalef(0.2,2.3,0.10);
    drawcube(1,1,1);
    glPopMatrix();
    glPopMatrix();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-2,20, -5, 12, 4, 100);
    // glFrustum(-5, 5, -5, 5, 4, 50);
    glFrustum(-5,5,-5,5, 4,50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, headX,headY,headZ);
    //  gluLookAt(0,1,10, 1,0,0, 0,1,0);
    // glViewport(0,0, windowHeight, windowWidth);


    glEnable(GL_LIGHTING);
    Light_One();
    Light_Two();
    Light_Three();


    drawname();




    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}



void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;



    case '+': //zoom in
        eyeZ++;
        lookZ++;
        break;
    case '-': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case '*': //zoom up
        eyeY++;
        lookY++;
        break;
    case '/': //zoom down
        eyeY--;
        lookY--;
        break;

    case 'x':
        eyeX++;
        lookX++;
        break;
    case 'z':
        eyeX--;
        lookX--;
        break;

    ///yaw
    case 'i':
        if(lookX<=20)
            lookX+=1.0;
        //cout<<refX<<endl;
        break;
    case 'u':
        if(lookX>=-7)
            lookX-=1.0;
        //cout<<refX<<endl;
        break;
    ///pitch
    case 'o':
        if(lookY<=10)
            lookY+=1.0;

      //  cout<<refY<<endl;
        break;
    case 'p':
        if(lookY>=-12)
            lookY-=1.0;
       // cout<<refY<<endl;
        break;

Naeem Mia CSE 17, [12/12/2022 00:06]
case 'q':
        if(angleflag== false)
            angleflag=true;
        else
            angleflag=false;
    case 'Q':
        if(angleflag1== false)
            angleflag1=true;
        else
            angleflag1=false;
    case '1':
        if(Light1 == false)
        {
            Light1 = true;
            ambL1 = true;
            diffL1 = true;
            specL1 = true;
            glEnable( GL_LIGHT0);   //Turn on light 1
        }
        else if(Light1 == true)
        {
            Light1 = false;
            ambL1 = false;
            diffL1 = false;
            specL1 = false;
            glDisable( GL_LIGHT0);   //Turn off light 1
        }
        break;
    case '2':
        if(Light2 == false)
        {
            Light2 = true;
            ambL2 = true;
            diffL2 = true;
            specL2 = true;
            glEnable( GL_LIGHT1);    //Turn on light 2
        }
        else if(Light2 == true)
        {
            Light2 = false;
            ambL2 = false;
            diffL2 = false;
            specL2 = false;
            glDisable( GL_LIGHT1);  //Turn off light 2
        }
        break;
    case '3':
        if(spotLight == false)
        {
            spotLight = true;
            ambL3 = true;
            diffL3 = true;
            specL3 = true;
            glEnable( GL_LIGHT2);   //Turn on spot light
        }
        else if(spotLight == true)
        {
            spotLight = false;
            ambL3 = false;
            diffL3 = false;
            specL3 = false;
            glDisable( GL_LIGHT2);  //Turn off spot light
        }
        break;



    case 'h':
        rr+=1;
        roll();
        break;
    case 'j':
        rr-=1;
        roll();
        break;

    case 'a':
        ambL1 =! ambL1;
        break;
    case 'A':
        ambL2 =! ambL2;
        break;
    case 'M':
        ambL3 =! ambL3;
        break;
    case 'd':
        diffL1 =! diffL1;
        break;
    case 'D':
        diffL2 =! diffL2;
        break;
    case 'E':
        diffL3 =! diffL3;
        break;
    case 's':
        specL1 =! specL1;
        break;
    case 'S':
        specL2 =! specL2;
        break;
    case 'T':
        specL3 =! specL3;
        break;

    case 27:  // Escape key
        exit(1);

    }
}


void animate()
{
    mTheta -= 1.0/60;
    hTheta -= 1.0/3600;
    if(mTheta < 0)
        mTheta += 360;
    if(hTheta<0)
        hTheta += 360;

    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if(angleflag==true)
    {
        angle += 0.03;
        if(angle > 360)
            angle -=360;
    }
    if(angleflag1==true)
    {
        angle1 += 0.03;
        if(angle1 > 360)
            angle1 -=360;
  }
    if(ambL1 == true)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient1);
    }
    else if(ambL1 == false)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    }
    if(diffL1 == true)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    }
    else if(diffL1 == false)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    }
    if(specL1 == true)
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else if(specL1 == false)
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }
//Light2
    if(ambL2 == true)
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient2);
    }
    else if(ambL2 == false)
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
    }
    if(diffL2 == true)
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    }
    else if(diffL2 == false)
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    }
    if(specL2 == true)
    {
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    }
    else if(specL2 == false)
    {
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }

Naeem Mia CSE 17, [12/12/2022 00:06]
//Light3
    if(ambL3 == true)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient3);
    }
    else if(ambL3 == false)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    }
    if(diffL3 == true)
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
    }
    else if(diffL3 == false)
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    }
    if(specL3 == true)
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    }
    else if(specL3 == false)
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }



    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    printf("To change camera position:\n");
    printf("1. Zoom In: +\n2. Zoom Out: -\n");
    printf("3. Camera Down: *\n4. Camera Up: /\n");
    printf("5. Camera Left: x\n6. Camera Right: z");
    printf("To rotate click r or R ");

    printf("\n\nTo roll h and j :\n");
    printf(" To yaw i and u \n");
    printf(" To pitch o and p \n");

   // printf("\nBack to Default position: b\n");
    printf("Fan on/off: f\n");

    printf("To control Lighting\n");
    printf("1. To turn Light1 on/off: 1\n");
    printf("i. To turn Light1 Ambient on/off: a\n");
    printf("ii. To turn Light1 Diffuse on/off: d\n");
    printf("iii. To turn Light1 Specular on/off: s\n\n");
    printf("2. To turn Light2 on/off: 2\n");
    printf("i. To turn Light2 Ambient on/off: A\n");
    printf("ii. To turn Light2 Diffuse on/off: D\n");
    printf("iii. To turn Light2 Specular on/off: S\n\n");
    printf("3. To turn Light3 on/off: 3\n");
    printf("i. To turn Light3 Ambient on/off: M\n");
    printf("ii. To turn Light3 Diffuse on/off: E\n");
    printf("iii. To turn Light3 Specular on/off: T");

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Assignment");
    glShadeModel(GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
