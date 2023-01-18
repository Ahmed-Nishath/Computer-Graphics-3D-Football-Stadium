#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

GLfloat camY = 0.0;
GLfloat camX = 0.0;
GLfloat camZ = 0.0;

//GLfloat rotate = 0.0;


void drawAxes() {
	glLineWidth(2);
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

void draw2DRectangle(float w, float h) {
	glBegin(GL_QUADS);
	glVertex3f(-w / 2, -h / 2, 0);
	glVertex3f( w / 2, -h / 2, 0);
	glVertex3f( w / 2,  h / 2, 0);
	glVertex3f(-w / 2,  h / 2, 0);
	glEnd();
}

void draw2DStage(float w1, float w2, float h1, float h2, float distance) {

	float h_diff = fabsf(h2 - h1);
	
	float theta = atan(h_diff / distance);

	float L = h_diff / sin(theta);

	glBegin(GL_POLYGON);
	glVertex3f(-w1 / 2, 0, 0);
	glVertex3f( w1 / 2, 0, 0);
	glVertex3f( w2 / 2, L, 0);
	glVertex3f(-w2 / 2, L, 0);
	glEnd();
}

void draw3DPanel(float w, float h, float t) {
	glBegin(GL_QUADS);
	glVertex3f( w / 2, -h / 2, t / 2);
	glVertex3f( w / 2,  h / 2, t / 2);
	glVertex3f(-w / 2,  h / 2, t / 2);
	glVertex3f(-w / 2, -h / 2, t / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f( w / 2, -h / 2, -t / 2);
	glVertex3f( w / 2,  h / 2, -t / 2);
	glVertex3f(-w / 2,  h / 2, -t / 2);
	glVertex3f(-w / 2, -h / 2, -t / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(w / 2, -h / 2,  t / 2);
	glVertex3f(w / 2, -h / 2, -t / 2);
	glVertex3f(w / 2,  h / 2, -t / 2);
	glVertex3f(w / 2,  h / 2,  t / 2);

	glBegin(GL_QUADS);
	glVertex3f(-w / 2, -h / 2,  t / 2);
	glVertex3f(-w / 2, -h / 2, -t / 2);
	glVertex3f(-w / 2,  h / 2, -t / 2);
	glVertex3f(-w / 2,  h / 2,  t / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-w / 2, h / 2,  t / 2);
	glVertex3f(-w / 2, h / 2, -t / 2);
	glVertex3f( w / 2, h / 2, -t / 2);
	glVertex3f( w / 2, h / 2,  t / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-w / 2, -h / 2,  t / 2);
	glVertex3f(-w / 2, -h / 2, -t / 2);
	glVertex3f( w / 2, -h / 2, -t / 2);
	glVertex3f( w / 2, -h / 2,  t / 2);
	glEnd();
}

void drawWalls(float fb_w, float lr_w, float h, float t ) {

	//Wall left
	glPushMatrix();
	glTranslatef(-fb_w / 2, h / 2, 0);
	glRotatef(90, 0, 1, 0);
	draw3DPanel(lr_w, h, t);
	glPopMatrix();

	//Wall right
	glPushMatrix();
	glTranslatef(fb_w / 2, h / 2, 0);
	glRotatef(90, 0, 1, 0);
	draw3DPanel(lr_w, h, t);
	glPopMatrix();

	//Wall front
	glPushMatrix();
	glTranslatef(0, h / 2, lr_w / 2 - t / 2);
	draw3DPanel(fb_w, h, t);
	glPopMatrix();

	//Wall back
	glPushMatrix();
	glTranslatef(0, h / 2, -lr_w / 2 + t / 2);
	draw3DPanel(fb_w, h, t);
	glPopMatrix();
}

void drawCircleFilled(float r) {
	int i, triangles = 100;
	GLfloat x = 0.0f, y = 0.0f;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangles; i++) {
		glVertex2f(x + (r * cos(i * 2 * PI / triangles)),
			y + (r * sin(i * 2 * PI / triangles)));
	}
	glEnd();
}

void drawLinesOnFeild() {

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 3.001, 0);
	glRotatef(90, 1, 0, 0);
	drawCircleFilled(9);
	glPopMatrix();

	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 3.002, 0);
	glRotatef(90, 1, 0, 0);
	drawCircleFilled(8.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.003, 0);

	glColor3f(1, 1, 1);
	glLineWidth(5);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(-37.5, 0);
	glVertex2f(37.5, 0);
	glEnd();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	//glTranslatef(0, 0, -4);
	gluLookAt(0 + camX, 0 + camY, 8 + camZ, 0, 0, 0, 0, 1, 0);
	drawAxes();
	drawGrid(40);

	//glRotatef(180, 0, 1, 0);
	
	glColor3f(0.45, 0.45, 0.45);
	//Base Foundation
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	draw2DRectangle(250, 180);
	glPopMatrix();

	float width = 120, height = 75;

	glColor3f(0, 1, 0);
	//Feild
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(90, 1, 0, 0);
	draw3DPanel(width, height, 2);
	glPopMatrix();

	drawLinesOnFeild(); //Not optimized

	glColor3f(1, 1, 0);
	drawWalls(width, height, 5, 1);

	glColor3f(0, 0.5, 1);
	drawWalls(width + 10, 81.25, 8, 1); // ( height / width ) * 130 = 81.25 

	glColor3f(1, 0, 1);
	drawWalls(width + 40, 100, 14, 1);  // ( height / width ) * 160 = 100


	//Front stage
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 8, 40);
	glRotatef(-34, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	draw2DStage(130, 160, 8, 14, 9.1);
	glPopMatrix();

	//Back stage
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 8, -40);
	glRotatef(34, 1, 0, 0);
	glRotatef(-90, 1, 0, 0);
	draw2DStage(130, 160, 8, 14, 9);
	glPopMatrix();

	//Left stage
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(65, 8, 0);
	glRotatef(22.5, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	draw2DStage(81.25, 100, 8, 14, 14.5);
	glPopMatrix();

	//Right stage
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(-65, 8, 0);
	glRotatef(-22.5, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	draw2DStage(81.25, 100, 8, 14, 14.5);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, aspect, 1.0, 200.0);
}


//void timer(int x) {
//
//	glutPostRedisplay();
//	glutTimerFunc(60.0, timer, 1);
//}


void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)	camX += 1;
	if (key == GLUT_KEY_LEFT)	camX -= 1;
	if (key == GLUT_KEY_UP)		camY += 1;
	if (key == GLUT_KEY_DOWN)	camY -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'z')	camZ += 1;
	if (key == 'Z')	camZ -= 1;

	if (key == 27) exit(0);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(80, 80);
	glutCreateWindow("Football 3D");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutTimerFunc(60.0, timer, 1);
	glutSpecialFunc(keyboardSpecial);

	glutFullScreen();
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}