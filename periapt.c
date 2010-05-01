#include <stdlib.h>
#include <GL/glut.h>
#include "glm.c"

GLMmodel* pmodel1 = NULL;
static float ypoz = 0, zpoz = 0;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    /* these form the material */
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    /*
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, diffuseLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    */
}

void drawmodel_box(void)
{
    if (!pmodel1)
    {
        pmodel1 = glmReadOBJ("objects/monkey.obj");
        if (!pmodel1) exit(0);
        glmUnitize(pmodel1);
        glmFacetNormals(pmodel1);
        glmVertexNormals(pmodel1, 90.0);
    }
    /* glmDraw(pmodel1, GLM_SMOOTH | GLM_TEXTURE); */
    glmDraw(pmodel1, GLM_SMOOTH);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glTranslatef(0,0,-2.5);
    /*
    glBegin(GL_TRIANGLES);
    glVertex3f(0,2,0);
    glVertex3f(3,0,0);
    glVertex3f(-3,0,0);
    glEnd();
    */
    /* SIMPLE FLAT POLYGON
    glBegin(GL_POLYGON);
    glVertex3f(1.0f, 1.0f , 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    */
    /*
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(-1.0f,-1.0f, 0.0f);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f( 1.0f,-1.0f, 0.0f);
    glEnd();
    */
    glPushMatrix();
    glRotatef(ypoz,0,1,0);
    glRotatef(zpoz,0,0,1);
    drawmodel_box();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
        exit(0);
        break;
        case 'y':
        ypoz=ypoz+5;
        if (ypoz > 360) ypoz=0;
        glutPostRedisplay();
        break;
        case 'z':
        zpoz = zpoz+5;
        if (zpoz > 360) zpoz=0;
        glutPostRedisplay();
        break;
    }
}
void animate()
{
    ypoz+=0.125;
    if (ypoz > 360) ypoz=0;
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Periapt - Steven Schronk");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}
