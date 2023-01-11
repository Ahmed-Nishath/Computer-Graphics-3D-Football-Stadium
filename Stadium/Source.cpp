#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

GLfloat camY = 0.0;
GLfloat camX = 0.0;
GLfloat camZ = 0.0;

GLfloat rotate = 0.0;

void drawAxes() {
	glLineWidth(2);//Should be out of GL_LINES
	glBegin(GL_LINES);
	//X-Axis
	glColor3f(1, 0, 0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	//Y-Axis
	glColor3f(0, 1, 0);
	glVertex3f(0, 200, 0);
	glVertex3f(0, -200, 0);

	//Z-Axis
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);
	glEnd();
}

void drawGrid(int gridSpan) {
	GLfloat step = 1;
	GLint line;

	glColor3f(0.2, 0.2, 0.2);
	glLineWidth(1);
	glBegin(GL_LINES);
	for (line = -gridSpan; line <= gridSpan; line += step) {
		glVertex3f(line, -0.2, -gridSpan);
		glVertex3f(line, -0.2, gridSpan);

		glVertex3f(-gridSpan, -0.2, line);
		glVertex3f(gridSpan, -0.2, line);
	}
	glEnd();
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	//glTranslatef(0, 0, -4);
	gluLookAt(0 + camX, 10 + camY, 10 + camZ, 0, 0, 0, 0, 1, 0);
	drawAxes();
	drawGrid(40);

	glMaterialf(GL_FRONT, GL_SHININESS, 32);
	GLfloat position[] = { 2.0, 2.0, 2.0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	const GLfloat matwhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, matwhite);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//glRotatef(rotate, 1, 1, 1);
	
	//Base
	glColor3f(0, 0, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-90.0, 0, 55);
	glVertex3f(-90.0, 0, -55);
	glVertex3f(90.0, 0, -55);
	glVertex3f(90.0, 0, 55);
	glEnd();
	glPushMatrix();

	//Feild
	glColor3f(0,1,0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.0, 0.5, 25);
	glVertex3f(-60.0, 0.5, -25);
	glVertex3f(60.0, 0.5, -25);
	glVertex3f(60.0, 0.5, 25);
	glEnd();
	glPushMatrix();

	//Feild side walls
	glColor3f(1, 1, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.0, 0, 25);
	glVertex3f(-60.0, 5, 25);
	glVertex3f(-60.0, 5, -25);
	glVertex3f(-60.0, 0, -25);
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(60.0, 0, 25);
	glVertex3f(60.0, 5, 25);
	glVertex3f(60.0, 5, -25);
	glVertex3f(60.0, 0, -25);
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.0, 0, 25);
	glVertex3f(-60.0, 5, 25);
	glVertex3f(60.0, 5, 25);
	glVertex3f(60.0, 0, 25);
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.0, 0, -25);
	glVertex3f(-60.0, 5, -25);
	glVertex3f(60.0, 5, -25);
	glVertex3f(60.0, 0, -25);
	glEnd();
	glPushMatrix();

	//Stage
	glColor3f(1, 0, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.5, 0, 25);
	glVertex3f(-60.5, 15, 25);
	glVertex3f(-60.5, 15, -25);
	glVertex3f(-60.5, 0, -25);
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-80.0, 0, 45);
	glVertex3f(-80.0, 25, 45);
	glVertex3f(-80.0, 25, -45);
	glVertex3f(-80.0, 0, -45);
	glEnd();
	glPushMatrix();


	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.5, 0, 25);
	glVertex3f(-60.5, 15, 25);
	glVertex3f(-80.0, 25, 45);
	glVertex3f(-80.0, 0, 45);
	glEnd();
	glPushMatrix();





	glColor3f(1, 0, 1);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-60.5, 0, 25.5);
	glVertex3f(-60.5, 15, 25.5);
	glVertex3f(60.5, 15, 25.5);
	glVertex3f(60.5, 0, 25.5);
	glEnd();
	glPushMatrix();


	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-80, 0, 45);
	glVertex3f(-80, 25, 45);
	glVertex3f(80, 25, 45);
	glVertex3f(80, 0, 45);
	glEnd();
	glPushMatrix();


	glPopMatrix();
	glutSwapBuffers();
}


void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, aspect, 1.0, 100.0);
}


void timer(int x) {
	rotate += 10;
	if (rotate >= 360) rotate = 0.0;

	glutPostRedisplay();
	glutTimerFunc(60.0, timer, 1);
}


void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)	camX += 1;
	if (key == GLUT_KEY_LEFT)	camX -= 1;
	if (key == GLUT_KEY_PAGE_UP)camY += 1;
	if (key == GLUT_KEY_PAGE_DOWN)camY -= 1;
	if (key == GLUT_KEY_UP)		camZ += 1;
	if (key == GLUT_KEY_DOWN)	camZ -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == '2') glEnable(GL_LIGHT0);
	if (key == '@') glDisable(GL_LIGHT0);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(80, 80);
	glutCreateWindow("Football Areana");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(60.0, timer, 1);
	glutSpecialFunc(keyboardSpecial);

	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}