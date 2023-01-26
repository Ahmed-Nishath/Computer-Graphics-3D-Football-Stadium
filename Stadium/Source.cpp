#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

GLfloat camY = 0.0;
GLfloat camX = 0.0;
GLfloat camZ = 0.0;

//GLfloat rotate = 0.0;

									/*  COMMON FUNCTIONS  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/

void enableLighting() {
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 50.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialf(GL_FRONT, GL_AMBIENT, 128.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_ambient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

void drawAxes() {
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 200, 0);
	glVertex3f(0, -200, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);
	glEnd();
}

										/*  COMMON SHAPES  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/


void DrawCircle(float r) {
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

void drawCylinder(GLfloat radius, GLfloat height) {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, radius, radius, height, 100, 100);
	DrawCircle(radius);
	glTranslatef(0, 0, height);
	DrawCircle(radius);
}

void draw2DRectangle(float w, float h) {
	glBegin(GL_QUADS);
	glVertex3f(-w / 2, -h / 2, 0);
	glVertex3f(w / 2, -h / 2, 0);
	glVertex3f(w / 2, h / 2, 0);
	glVertex3f(-w / 2, h / 2, 0);
	glEnd();
}

void draw3DPanel(float w, float h, float t) {
	glScalef(w, h, t);
	glutSolidCube(1);
}

											/*  STAGE  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/


void draw2DStage(float w1, float w2, float h1, float h2, float distance) {

	float h_diff = fabsf(h2 - h1);
	float theta = atan(h_diff / distance);
	float L = h_diff / sin(theta);

	glBegin(GL_POLYGON);
	glVertex3f(-w1 / 2, 0, 0);
	glVertex3f(w1 / 2, 0, 0);
	glVertex3f(w2 / 2, L, 0);
	glVertex3f(-w2 / 2, L, 0);
	glEnd();
}

void drawWalls(float fb_w, float lr_w, float h, float t) {

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

											/*  CHAIR  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/


void customCylinderForChair(GLfloat radius, GLfloat height) {
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 0.5 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glEnd();

	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 0.5 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}

void drawCircleFilledForChair(float r) {
	int i, triangles = 50;
	GLfloat x = 0.0f, y = 0.0f;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangles; i++) {
		glVertex2f(x + (r * cos(i * 0.5 * PI / triangles)),
			y + (r * sin(i * 0.5 * PI / triangles)));
	}
	glEnd();
}

void drawChairComponent() {
	glPushMatrix();
	glTranslatef(0, 2, 0.5);
	glScalef(8, 4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	drawCylinder(4, 1);
	glPopMatrix();
}

void drawChair() {
	glColor3f(0.9, 0.8, 0.5);
	//Chair Back Rester
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawChairComponent();
	glPopMatrix();

	glColor3f(0.7, 0.6, 0.3);
	//Chair Seat
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	drawChairComponent();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	//Left Hand Rest
	glPushMatrix();
	glTranslatef(-1, 1, 1);
	glTranslatef(-2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	customCylinderForChair(3, 1);
	drawCircleFilledForChair(3);
	glTranslatef(0, 0, 1);
	drawCircleFilledForChair(3);
	glPopMatrix();

	//Right Hand Rest
	glPushMatrix();
	glTranslatef(6, 1, 1);
	glTranslatef(-2, 0, 0);
	glRotatef(-90, 0, 1, 0);
	customCylinderForChair(3, 1);
	drawCircleFilledForChair(3);
	glTranslatef(0, 0, 1);
	drawCircleFilledForChair(3);
	glPopMatrix();
}

void drawSeatRow(int row_length) {
	glColor3f(0.5, 1, 0.8);
	glPushMatrix();
	glScalef(row_length, 1, 2);
	glutSolidCube(1);
	glPopMatrix();

	for (int i = -(row_length / 2) + 1; i <= (row_length / 2) - 1; i += 2) {
		glPushMatrix();
		glTranslatef(i, 0.5, -0.70);
		glScalef(0.2, 0.2, 0.2);
		drawChair();
		glPopMatrix();
	}
}

void allSeats() {

	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 11, -42);
	drawSeatRow(138);
	glPopMatrix();

	glTranslatef(0, 2, -3);
	glPushMatrix();
	glTranslatef(0, 11, -42);
	drawSeatRow(148);
	glPopMatrix();

	glTranslatef(0, -4, 6);
	glPushMatrix();
	glTranslatef(0, 11, -42);
	drawSeatRow(136);
	glPopMatrix();

	glPopMatrix();

	/*
	glPushMatrix();

		glPushMatrix();
		glTranslatef(0, 11, 42);
		glRotatef(180, 0, 1, 0);
		drawSeatRow(140);
		glPopMatrix();

		glTranslatef(0, 2, 3);
		glPushMatrix();
		glTranslatef(0, 11, 42);
		glRotatef(180, 0, 1, 0);
		drawSeatRow(150);
		glPopMatrix();

		glTranslatef(0, -4, -6);
		glPushMatrix();
		glTranslatef(0, 11, 42);
		glRotatef(180, 0, 1, 0);
		drawSeatRow(130);
		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glPushMatrix();
		glTranslatef(70, 11, 0);
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(86);
		glPopMatrix();

		glTranslatef(3, 2, 0);
		glPushMatrix();
		glTranslatef(70, 11, 0);
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(90);
		glPopMatrix();

		glTranslatef(-6, -4, 0);
		glPushMatrix();
		glTranslatef(70, 11, 0);
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(78);
		glPopMatrix();

	glPopMatrix();
	*/
}

											/*  GOAL POST  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/


void drawMesh(float width, float height, float spread) {

	if (height > width) {
		glRotatef(90, 0, 0, 1);
		float temp = height;
		height = width;
		width = temp;
	}

	glPushMatrix();
	glTranslatef(-width / 2, height / 2, 0);
	float j = 0;
	for (float i = 0; i < width; i += spread) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, 0);
		if (i >= height) {
			glVertex3f(j, -height, 0);
			j += spread;
		}
		else glVertex3f(0, -i, 0);
		glEnd();
	}

	for (float i = 0; i < height; i += spread) {
		glBegin(GL_LINES);
		glVertex3f(width, -i, 0);
		glVertex3f(j, -height, 0);
		glEnd();
		j += spread;
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-width / 2, height / 2, 0);
	j = 0;
	for (float i = 0; i < width; i += spread) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, 0);
		if (i >= height) {
			glVertex3f(j, -height, 0);
			j += spread;
		}
		else glVertex3f(0, -i, 0);
		glEnd();
	}

	for (float i = 0; i < height; i += spread) {
		glBegin(GL_LINES);
		glVertex3f(width, -i, 0);
		glVertex3f(j, -height, 0);
		glEnd();
		j += spread;
	}
	glPopMatrix();
}

void drawGoalPostBar(float width, float height, float thick) {

	//Three Polls
	glPushMatrix();
	glTranslatef(-width / 2, 0, 0);
	glScalef(1, (1 / thick) * height, 1);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(thick, thick);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(width / 2, 0, 0);
	glScalef(1, (1 / thick) * height, 1);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(thick, thick);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(width / 2, height, 0);
	glScalef((1 / thick) * width, 1, 1);
	glRotatef(-90, 0, 1, 0);
	drawCylinder(thick, thick);
	glPopMatrix();

	//Sphear for Sharp edges
	glPushMatrix();
	glTranslatef(width / 2, height, 0);
	glutSolidSphere(thick, 100, 100);

	glTranslatef(-width, 0, 0);
	glutSolidSphere(thick, 100, 100);
	glPopMatrix();
}

void drawGoal(float width, float thick) {

	float height = width / 3, distance = width * 0.3;

	//Front U bar
	drawGoalPostBar(width, height, thick);

	//Left Connector
	glPushMatrix();
	glTranslatef(-width / 2, height, 0);
	glScalef(1, 1, (1 / thick) * distance);
	glRotatef(-180, 1, 0, 0);
	drawCylinder(thick, thick);
	glPopMatrix();

	//Right Connector
	glPushMatrix();
	glTranslatef(width / 2, height, 0);
	glScalef(1, 1, (1 / thick) * distance);
	glRotatef(-180, 1, 0, 0);
	drawCylinder(thick, thick);
	glPopMatrix();

	//Back U bar
	glPushMatrix();
	glTranslatef(0, 0, -distance);
	drawGoalPostBar(width, height, thick);
	glPopMatrix();

	glColor3f(0.95, 0.95, 1);
	float spread = 0.5;
	glLineWidth(2);
	//Mesh Back
	glPushMatrix();
	glTranslatef(0, height / 2, -distance);
	drawMesh(width, height, spread);
	glPopMatrix();

	//Mesh Left
	glPushMatrix();
	glTranslatef(-width / 2, height / 2, -distance / 2);
	glRotatef(90, 0, 1, 0);
	drawMesh(distance, height, spread);
	glPopMatrix();

	//Mesh Right
	glPushMatrix();
	glTranslatef(width / 2, height / 2, -distance / 2);
	glRotatef(90, 0, 1, 0);
	drawMesh(distance, height, spread);
	glPopMatrix();

	//Mesh Top
	glPushMatrix();
	glTranslatef(0, height, -distance / 2);
	glRotatef(90, 1, 0, 0);
	drawMesh(width, distance, spread);
	glPopMatrix();
}


										    /*  DISPLAY  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	gluLookAt(0 + camX, 0 + camY, 8 + camZ, 0, 0, 0, 0, 1, 0);
	drawAxes();

	//enableLighting();

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

	//Goal 1
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(54, 2.7, 0);
	glRotatef(-90, 0, 1, 0);
	drawGoal(15, 0.2);
	glPopMatrix();

	//Goal 2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-54, 2.7, 0);
	glRotatef(180, 0, 1, 0);
	glRotatef(-90, 0, 1, 0);
	drawGoal(15, 0.2);
	glPopMatrix();

	//allSeats();

	glPopMatrix();
	glutSwapBuffers();
}


											/*  MAIN FUNCTIONS  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/

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