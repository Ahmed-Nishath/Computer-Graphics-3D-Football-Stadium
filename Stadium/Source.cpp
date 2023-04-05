#include <GL/glut.h>
#include <math.h>

#define PI 3.1415927

GLfloat camY = 0.0;
GLfloat camX = 0.0;
GLfloat camZ = 0.0;
GLfloat cam_speed = 2;

//Display Score
GLfloat r = 0.0;

//Animation
GLfloat hit = 60.0;
GLfloat ballX = 0.0;
GLfloat ballZ = 0.0;
GLfloat keeper = 0.0;
GLfloat ballRotation = 0.0;

//Switches
GLint tv = 0;
GLint seat = 0;
GLint hitBall = 0;
GLint timeCount = 0;


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
										/*  COMMON SHAPES  */

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

void drawCylinder(GLfloat radius,  GLfloat height) {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, radius, radius, height, 100, 100);
	DrawCircle(radius);
	glTranslatef(0, 0, height);
	DrawCircle(radius);
}

void drawCylinder(GLfloat radius1, GLfloat radius2, GLfloat height) {
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, radius1, radius2, height, 100, 100);
	DrawCircle(radius1);
	glTranslatef(0, 0, height);
	DrawCircle(radius2);
}

void customTorus(GLfloat multiply, GLfloat inner_radius, GLfloat outer_radius, GLint isFull) {
	double s, t, x, y, z, degree;
	int numc = 100, numt = 100;

	degree = multiply * PI;
	for (int i = 0; i <= numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j < numt + isFull; j++) {
			for (int k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (outer_radius + inner_radius * cos(s * degree / numc)) * cos(t * degree / numt);
				y = (outer_radius + inner_radius * cos(s * degree / numc)) * sin(t * degree / numt);
				z = inner_radius * sin(s * degree / numc);

				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

void draw3DPanel(float w, float h, float t) {
	glScalef(w, h, t);
	glutSolidCube(1);
}

/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
										/*  SCENE LIGHTING  */

void Lighting() {
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };

	//Natural Light Source
	GLfloat light_position_natural[] = { 0, 100, 0, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_natural);

	//Left Light Panel
	GLfloat light_position_left[] = { 75, 27, 0, 1 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_left);

	//Right Light Panel
	GLfloat light_position_right[] = { -75, 27, 0, 1 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position_right);

	//Score Board Light Left
	if (r == 1 && tv == 1) glEnable(GL_LIGHT4);
	else glDisable(GL_LIGHT4);

	GLfloat light_diffuse_red[] = { 0.2, 0, 0, 1 };
	GLfloat light_specular_red[] = { 0.2, 0, 0, 1 };

	GLfloat light_position_score_board[] = { 0, 51, 0, 1 };
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse_red);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular_red);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position_score_board);
}

/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  FOUNDATION  */

void drawFoundation() {
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glScalef(250, 1, 180);
	glutSolidCube(1);
	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  FEILD  */

void drawFeild(GLfloat width, GLfloat height) {
	glColor3f(0, 0.9, 0);
	glPushMatrix();

	//Feild
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(90, 1, 0, 0);
	draw3DPanel(width, height, 2);
	glPopMatrix();

	//Grass Pattern
	glColor3f(0.2, 0.9, 0.2);
	glPushMatrix();
	glTranslatef(30, 0, 0);
	int lines = 8;
	for (int i = -lines / 2; i < lines / 2 - 2; i++) {
		glPushMatrix();
		glTranslatef(i * 2 * 10, 2.01, 0);
		glRotatef(90, 1, 0, 0);
		draw3DPanel(10, height, 2);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
										/*  FEILD LINES  */

void drawBox() {
	//Main Line
	glPushMatrix();
	glTranslatef(40, 2.6, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(40, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	//Left Line
	glPushMatrix();
	glTranslatef(49.9, 2.6, 19.5);
	glScalef(21, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	//Right Line
	glPushMatrix();
	glTranslatef(49.9, 2.6, -19.5);
	glScalef(21, 1, 1);
	glutSolidCube(1);
	glPopMatrix();
}

void drawFeildLines() {
	glColor3f(1, 1, 1);
	glPushMatrix();

	//Mid Line
	glPushMatrix();
	glTranslatef(0, 2.509, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(75, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	//Left Goal Outer Line
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	drawBox();
	glPopMatrix();

	//Right Goal Outer Line
	glPushMatrix();
	glTranslatef(6, 0, 0);
	glRotatef(180, 0, 1, 0);
	drawBox();
	glPopMatrix();

	////////////////////////////////////////
	if (glIsEnabled(GL_LIGHT0)) glDisable(GL_LIGHTING);

	//Central Circle
	glPushMatrix();
	glTranslatef(0, 3.05, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(2, 0.5, 7, 1);
	glPopMatrix();

	//Right Goal Outer Arc
	glPushMatrix();
	glTranslatef(34, 3.05, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(1, 0.5, 7, 0);
	glPopMatrix();

	//Right Goal Outer Arc
	glPushMatrix();
	glTranslatef(-34, 3.05, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(1, 0.5, 7, 0);
	glPopMatrix();

	//Corner Arcs

	glPushMatrix();
	glTranslatef(54, 3.25, 36);
	glRotatef(180, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(0.5, 2, 3, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-54, 3.25, 36);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(0.5, 2, 3, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-54, 3.25, -36);
	glRotatef(90, 1, 0, 0);
	customTorus(0.5, 2, 3, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 3.25, -36);
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	customTorus(0.5, 2, 3, 0);
	glPopMatrix();

	if (glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHTING);
	////////////////////////////////////////

	//Left Goal Inner Line
	glPushMatrix();
	glScalef(0.3, 1, 0.6);
	glTranslatef(120, 0, 0);
	drawBox();
	glPopMatrix();

	//Right Goal Inner Line
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glScalef(0.3, 1, 0.6);
	glTranslatef(120, 0, 0);
	drawBox();
	glPopMatrix();

	//4 Borders
	glPushMatrix();
	glTranslatef(54.4, 2.6, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(75, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-54.4, 2.6, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(75, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.6, 36.2);
	glScalef(110, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.6, -36.2);
	glScalef(110, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  GROUND WALLS  */

void drawWalls(float fb_w, float lr_w, float h, float t, GLfloat r, GLfloat g, GLfloat b) {
	glColor3f(r, g, b);

	glPushMatrix();

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

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  STAGE  */

void draw2DStage(float w, float h, float d) {
	glBegin(GL_QUADS);
	glVertex3f(-w / 2, 0, 0);
	glVertex3f(w / 2, 0, 0);
	glVertex3f(w / 2, h, 0);
	glVertex3f(-w / 2, h, 0);

	glVertex3f(-w / 2, 0, 0);
	glVertex3f(w / 2, 0, 0);
	glVertex3f(w / 2 + d, 0, d);
	glVertex3f(-w / 2 - d, 0, d);

	glVertex3f(-w / 2 - d, 0, d);
	glVertex3f(w / 2 + d, 0, d);
	glVertex3f(w / 2 + d, h + d, d);
	glVertex3f(-w / 2 - d, h + d, d);

	glVertex3f(-w / 2 - d, h + d, d);
	glVertex3f(w / 2 + d, h + d, d);
	glVertex3f(w / 2, h, 0);
	glVertex3f(-w / 2, h, 0);

	glEnd();
}

void allStage() {
	glColor3f(0.9, 0.9, 0.85);
	glPushMatrix();

	//Front stage
	glPushMatrix();
	glTranslatef(0, 0, 41);
	draw2DStage(130, 8, 10);
	glPopMatrix();

	//Back stage
	glPushMatrix();
	glTranslatef(0, 0, -41);
	glRotatef(-180, 0, 1, 0);
	draw2DStage(130, 8, 10);
	glPopMatrix();

	//Left stage
	glPushMatrix();
	glTranslatef(-65, 0, 0);
	glRotatef(-90, 0, 1, 0);
	draw2DStage(82, 8, 10);
	glPopMatrix();

	//Right stage
	glPushMatrix();
	glTranslatef(65, 0, 0);
	glRotatef(90, 0, 1, 0);
	draw2DStage(82, 8, 10);
	glPopMatrix();

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  FLAGS  */

void drawFlags() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 2.8, 0);
	glRotatef(-90, 1, 0, 0);
	drawCylinder(0.2, 5);

	glutSolidSphere(0.2, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 7.2, -0.07);
	glScalef(0.1, 0.7, 2);
	glutSolidCone(1, 1, 4, 50);
	glPopMatrix();
}

void allFlags() {
	glPushMatrix();
	glTranslatef(54, 0, 36);
	glRotatef(180, 0, 1, 0);
	drawFlags();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 0, -36);
	drawFlags();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-54, 0, 36);
	glRotatef(180, 0, 1, 0);
	drawFlags();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-54, 0, -36);
	drawFlags();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -36);
	drawFlags();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 36);
	glRotatef(180, 0, 1, 0);
	drawFlags();
	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  OUTER WALLS  */

void drawRoofPanel(GLfloat w, GLfloat h, GLfloat t, GLfloat translate, GLfloat color[]) {
	glPushMatrix();
	glScalef(w, h, t);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	for (int i = -w / 2 + 1; i < w / 2; i += 4) {
		glPushMatrix();
		glTranslatef(i * 1, 0, translate);
		glScalef(2, h - 0.5, t);
		glutSolidCube(1);
		glPopMatrix();

	}
	glColor3fv(color);
}

void drawWallMainPanel(GLfloat w, GLfloat h, GLfloat t, GLfloat translate, GLfloat color[]) {
	glPushMatrix();
	glScalef(w, h, t);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.125, 0.25, 0.4);
	for (int i = -w / 2 + 1; i < w / 2; i += 4) {
		glPushMatrix();
		glTranslatef(i * 1, 0, translate);
		glScalef(2, h - 0.5, t);
		glutSolidCube(1);
		glPopMatrix();
	}
	glColor3fv(color);
}

void drawSurroundingWalls(GLfloat height) {
	GLfloat color[] = { 0.15, 0.35, 0.5 };
	glColor3fv(color);

	glPushMatrix();

	//Sides 1
	glPushMatrix();
	glTranslatef(0, height / 2, 53);
	drawWallMainPanel(153, height, 4, 0.8, color);
	glPopMatrix();

	//Side 2
	glPushMatrix();
	glTranslatef(0, height / 2, -53);
	drawWallMainPanel(153, height, 4, -0.8, color);
	glPopMatrix();

	///////////////
	//Angled Left 1
	glPushMatrix();
	glTranslatef(75.4, height / 2, 53.8);
	glRotatef(60, 0, 1, 0);
	glTranslatef(63.1 / 2, 0, -0.5);
	drawWallMainPanel(63.1, height, 4, 0.8, color);
	glPopMatrix();

	//Angled Left 2
	glPushMatrix();
	glTranslatef(75.4, height / 2, -53.8);
	glRotatef(-60, 0, 1, 0);
	glTranslatef(63.1 / 2, 0, 0.5);
	drawWallMainPanel(63.1, height, 4, -0.8, color);
	glPopMatrix();

	//Angled Right 1
	glPushMatrix();
	glTranslatef(-74.6, height / 2, 53.5);
	glRotatef(120, 0, 1, 0);
	glTranslatef(63.1 / 2, 0, -0.5);
	drawWallMainPanel(63.1, height, 4, -0.8, color);
	glPopMatrix();

	//Angled Right 2
	glPushMatrix();
	glTranslatef(-74.6, height / 2, -53.5);
	glRotatef(-120, 0, 1, 0);
	glTranslatef(63.1 / 2, 0, 0.5);
	drawWallMainPanel(63.1, height, 4, 0.8, color);
	glPopMatrix();

	//Roof
	///////////////
	glColor3fv(color);

	glPushMatrix();
	glTranslatef(0, -0.1, 0);

	//UP 1
	glPushMatrix();
	glTranslatef(0, height - 1.999, 53 - 12.5);
	glRotatef(-90, 1, 0, 0);
	drawRoofPanel(153, 25, 4, -1, color);
	glPopMatrix();

	//UP 2
	glPushMatrix();
	glTranslatef(0, height - 1.996, -53 + 12.5);
	glRotatef(-90, 1, 0, 0);
	drawRoofPanel(153, 25, 4, -1, color);
	glPopMatrix();

	//Angled Left 1 Up
	glPushMatrix();
	glTranslatef(80.4, height - 1.998, 20.9);
	glRotatef(60, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(63.1, 25, 4);
	glutSolidCube(1);
	glPopMatrix();

	//Angled Left 2 Up
	glPushMatrix();
	glTranslatef(80.4, height - 1.997, -20.9);
	glRotatef(-60, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(63.1, 25, 4);
	glutSolidCube(1);
	glPopMatrix();

	//Angled Right 1 Up
	glPushMatrix();
	glTranslatef(-80.4, height - 1.994, 20.9);
	glRotatef(-60, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(63.1, 25, 4);
	glutSolidCube(1);
	glPopMatrix();

	//Angled Right 2 Up
	glPushMatrix();
	glTranslatef(-80.4, height - 1.995, -20.9);
	glRotatef(60, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(63.1, 25, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	//Covers on sides
	glPushMatrix();
	glTranslatef(80, 19.5, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 39, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 19.5, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(90, 39, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  LIGHT PANELS  */

void LightSource(GLfloat light_on_off[]) {
	glColor3f(0, 0, 0);

	//Light Bar
	glPushMatrix();
	glTranslatef(0, -4, -4);
	glRotatef(90, 1, 0, 0);
	drawCylinder(1, 35);
	glPopMatrix();

	glRotatef(45, 1, 0, 0);
	//Light Panel
	glPushMatrix();
	glScalef(15, 15, 1);
	glutSolidCube(1);
	glPopMatrix();

	GLfloat mtrlshinnes[] = { 128 };
	GLfloat mtrldiffu[] = { 1, 1, 1, 1 };
	GLfloat mtrlspecu[] = { 1, 1, 1, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mtrldiffu);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mtrlspecu);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mtrlshinnes);

	GLfloat position[] = { 0, 0, 4, 1 };
	glLightfv(GL_LIGHT3, GL_POSITION, position);

	GLfloat lambient[] = { 1, 1, 1, 1 };
	GLfloat ldiffuse[] = { 1, 1, 1, 1 };
	GLfloat lspecular[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT3, GL_AMBIENT, lambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, ldiffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lspecular);

	glColor3fv(light_on_off);
	glEnable(GL_LIGHT3);

	for (int i = -4; i <= 4; i += 4) {
		for (int j = -4; j <= 4; j += 4) {
			glPushMatrix();
			glTranslatef(i, j, 0);
			drawCylinder(1, 1);
			glPopMatrix();
		}
	}
	glDisable(GL_LIGHT3);
}

void allPanels() {
	GLfloat black[] = { 0 ,0, 0 };
	GLfloat white[] = { 1, 1, 1 };

	//Light Panel Left
	glPushMatrix();
	glTranslatef(75, 27, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);

	if (glIsEnabled(GL_LIGHT1)) LightSource(white);
	else  LightSource(black);

	glPopMatrix();

	//Light Panel Right
	glPushMatrix();
	glTranslatef(-75, 27, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.7, 0.7, 0.7);

	if (glIsEnabled(GL_LIGHT2)) LightSource(white);
	else  LightSource(black);

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  SCORE BOARD  */

void ScoreBoard() {
	glColor3f(0, 0, 0);
	glPushMatrix();
	glScalef(22.5, 10.7, 1);
	glutSolidCube(1);
	glPopMatrix();

	GLfloat score[] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,r,r,r,r,r,0,0,0,0,0,0,0,0,0,r,r,r,r,r,0,
		0,0,0,0,0,r,0,0,0,0,0,0,0,0,0,r,0,0,0,r,0,
		0,0,0,0,0,r,0,0,0,0,0,0,0,0,0,r,0,0,0,r,0,
		0,r,r,r,r,r,0,0,0,r,r,r,0,0,0,r,0,0,0,r,0,
		0,r,0,0,0,0,0,0,0,r,r,r,0,0,0,r,0,0,0,r,0,
		0,r,0,0,0,0,0,0,0,0,0,0,0,0,0,r,0,0,0,r,0,
		0,r,0,0,0,0,0,0,0,0,0,0,0,0,0,r,0,0,0,r,0,
		0,r,r,r,r,r,0,0,0,0,0,0,0,0,0,r,r,r,r,r,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	GLfloat score_update[] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,r,r,r,r,r,0,0,0,0,0,0,0,0,0,r,r,r,0,0,0,
		0,0,0,0,0,r,0,0,0,0,0,0,0,0,0,r,0,r,0,0,0,
		0,0,0,0,0,r,0,0,0,0,0,0,0,0,0,0,0,r,0,0,0,
		0,r,r,r,r,r,0,0,0,r,r,r,0,0,0,0,0,r,0,0,0,
		0,r,0,0,0,0,0,0,0,r,r,r,0,0,0,0,0,r,0,0,0,
		0,r,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,r,0,0,0,
		0,r,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,r,0,0,0,
		0,r,r,r,r,r,0,0,0,0,0,0,0,0,0,r,r,r,r,r,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};

	int count = 0;

	glPushMatrix();
	glTranslatef(-10.5, 4.72, 0);
	glRotatef(-90, 0, 0, 1);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 21; j++) {

			if (tv == 1) {
				if (ballX < 180) glColor3f(score[count], 0, 0);
				else glColor3f(score_update[count], 0, 0);
			}
			else 
				glColor3f(0, 0, 0);

			glPushMatrix();
			glTranslatef(i + 0.05 * i, j + 0.05 * j, 0.02);
			glutSolidCube(1);
			glPopMatrix();
			count++;
		}
	}
	glPopMatrix();
}

void allScoreBoard() {
	//Score Board Front
	glPushMatrix();
	glTranslatef(0, 27, -51);
	glScalef(0.85, 0.85, 0.85);
	ScoreBoard();
	glPopMatrix();

	//Score Board Back
	glPushMatrix();
	glTranslatef(0, 27, 51);
	glRotatef(180, 0, 1, 0);
	glScalef(0.85, 0.85, 0.85);
	ScoreBoard();
	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  PLAYER  */

void drawHeadandNeck() {
	//head
	glPushMatrix();
	glTranslatef(0, 4, 0);
	glScalef(1, 1.1, 0.85);
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	//neck
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawCylinder(1, 1, 2.5);
	glPopMatrix();
}

void drawLeg() {
	glColor3f(0.90980, 0.74509, 0.674509);
	glPushMatrix();
	glTranslatef(-1.2, -2.5, 0);
	glRotatef(90, 1, 0, 0);
	drawCylinder(0.75, 0.6, 1);
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.9);
	glPushMatrix();
	glTranslatef(-1.2, -3.4, 0);
	glRotatef(90, 1, 0, 0);
	drawCylinder(0.6, 0.3, 5);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-1.2, -8.4, 0.75);
	glScalef(0.5, 0.4, 1.35);
	glutSolidSphere(0.8, 50, 50);
	glPopMatrix();
}

void drawHand(GLfloat color[]) {
	glColor3fv(color);

	//T-shirt part
	glPushMatrix();
	glTranslatef(-1.2, 5.1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1.02, 1.02, 1.02);
	glScalef(1, 0.7, 0.7);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, 5.1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1.02, 1.02, 1.02);
	glScalef(1, 0.7, 0.7);
	drawCylinder(1, 0.95, 2.5);
	glPopMatrix();

	glColor3f(0.90980, 0.74509, 0.674509);
	glPushMatrix();
	glTranslatef(-1.2, 5.1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 0.7, 0.7);
	drawCylinder(1, 0.7, 11.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.2, -3, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.5, 0.3, 1.35);
	glutSolidSphere(1.1, 50, 50);
	glPopMatrix();
}

void drawUpperBody(GLfloat color[], GLfloat hand_front, GLfloat hand_side) {
	glColor3fv(color);
	//Chest
	glPushMatrix();
	glTranslatef(0, 3.9, 0);
	glScalef(4, 1, 1.75);
	glRotatef(90, 1, 0, 0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glScalef(4, 4, 1.75);
	glRotatef(90, 1, 0, 0);
	drawCylinder(1, 1.2, 2);
	glPopMatrix();

	glColor3f(0.90980, 0.74509, 0.674509);
	//Hands
	glPushMatrix();
	glTranslatef(3.8, 2.7, 1);
	glRotatef(hand_front, 1, 0, 0);
	glRotatef(hand_side, 0, 0, 1);
	glTranslatef(1.2, -4, 0);
	drawHand(color);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(3.8, 2.7, 1);
	glRotatef(-25, 1, 0, 0);
	glTranslatef(1.2, -4, 0);
	drawHand(color);
	glPopMatrix();
}

void drawLap() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(4, 4, 1.5);
	glRotatef(90, 1, 0, 0);
	drawCylinder(1.2, 1, 2);
	glPopMatrix();
}

void drawLowerBody(GLfloat color[], GLboolean isForward) {
	glColor3fv(color);
	//Lower Body Left
	glPushMatrix();
	glTranslatef(-1.2, 1.3, 0);
	glScalef(0.25, 0.25, 0.25);
	glScalef(1, 2, 2);
	drawLap();
	glPopMatrix();

	//Lower Body Right
	glPushMatrix();
	glTranslatef(1.2, 1.3, 0);
	glScalef(0.25, 0.25, 0.25);
	glScalef(1, 2, 2);
	drawLap();
	glPopMatrix();

	//Leg Left
	glPushMatrix();
	
	if (isForward) {
		glTranslatef(-1.2, -2.5, 0);
		glRotatef(hit, 1, 0, 0);
		glTranslatef(1.2, 2.5, 0);
	}

	drawLeg();
	glPopMatrix();

	//Leg Right
	glPushMatrix();
	glTranslatef(2.5, 0, 0);
	drawLeg();
	glPopMatrix();
}

void drawPlayer(GLfloat shirt_color[], GLfloat trouser_color[], GLfloat hand_front, GLfloat hand_side, GLboolean isForward) {
	glColor3f(0.90980, 0.74509, 0.674509);
	glPushMatrix();
	glTranslatef(0, 5.3, 0);
	glScalef(0.27, 0.27, 0.27);

	//Head and Neck
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glScalef(0.5, 0.5, 0.5);
	drawHeadandNeck();
	glPopMatrix();

	//Upper Body
	glPushMatrix();
	glTranslatef(0, 3.3, 0);
	glScalef(0.5, 0.5, 0.5);
	drawUpperBody(shirt_color, hand_front, hand_side);
	glPopMatrix();

	//Lower Body
	glPushMatrix();
	drawLowerBody(trouser_color, isForward);
	glPopMatrix();

	glPopMatrix();
}

void allPlayers() {
	GLfloat white[] = { 1, 1, 1 };
	GLfloat black[] = { 0, 0, 0 };
	GLfloat red[] = { 1, 0, 0 };
	GLfloat yellow[] = { 1, 1, 0 };

	//Player
	glPushMatrix();
	glTranslatef(42, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawPlayer(red, white, -45, 15, true);
	glPopMatrix();

	//Goal Keeper
	glPushMatrix();
	glTranslatef(0, 0, keeper);
	glTranslatef(53, 0, -5);
	glRotatef(-90, 0, 1, 0);
	drawPlayer(red, white, -45, 15, false);
	glPopMatrix();

	//Refree
	glPushMatrix();
	glTranslatef(47, 0, 15);
	glRotatef(200, 0, 1, 0);
	drawPlayer(yellow, black, -90, 0, false);
	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  GOAL POST  */

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

void allGoals() {
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
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/* FOOT  BALL */

void drawBall() {
	glColor3f(1, 1, 1);

	glPushMatrix();
	glTranslatef(42.85, 3.39, 0);
	glScalef(0.08, 0.08, 0.08);

	glTranslatef(ballX, 0, ballZ);
	glRotatef(-ballRotation, 0, 0, 1);
	glPushMatrix();
	glutSolidSphere(5, 50, 50);
	glPopMatrix();

	glColor3f(0, 0, 0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 8; j++) {
			glPushMatrix();
			glRotatef(120 * i, 0, 1, 0);
			glRotatef(45 * j, 1, 0, 0);
			glTranslatef(0, 0, 4.08);
			glScalef(1, 1, 0.5);
			glutSolidSphere(2, 50, 50);
			glPopMatrix();
		}
	}
	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  SEATS  */

void drawChairComponent() {
	glPushMatrix();
	glTranslatef(0, 2, 0.5);
	glScalef(8, 4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, -0.01);
	drawCylinder(4, 1);
	glPopMatrix();
}

void drawChair() {
	glColor3f(1, 1, 1);
	//Chair Back Rester
	glPushMatrix();
	glTranslatef(0, 1, 0);
	drawChairComponent();
	glPopMatrix();

	glColor3f(1, 1, 1);
	//Chair Seat
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	drawChairComponent();
	glPopMatrix();
}

void drawSeatRow(int row_length) {
	glColor3f(1, 0, 0);
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
	//Left Seat Set
	glPushMatrix();
	glTranslatef(0, 9, 42);

		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		drawSeatRow(130);
		glPopMatrix();

		glTranslatef(0, 3, 3);
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		drawSeatRow(138);
		glPopMatrix();

		glTranslatef(0, 3, 3);
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		drawSeatRow(145);
		glPopMatrix();

	glPopMatrix();

	//Right Seat Set
	glPushMatrix();

	glTranslatef(0, 9, -42);

		glPushMatrix();
		drawSeatRow(130);
		glPopMatrix();

		glTranslatef(0, 3, -3);
		glPushMatrix();
		drawSeatRow(138);
		glPopMatrix();

		glTranslatef(0, 3, -3);
		glPushMatrix();
		drawSeatRow(145);
		glPopMatrix();

	glPopMatrix();

	//Front Seat Set
	glPushMatrix();

	glTranslatef(-68.5, 11.8, 0);
	glRotatef(180, 0, 1, 0);

		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(90);
		glPopMatrix();

		glTranslatef(3, 3, 0);
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(94);
		glPopMatrix();

		glTranslatef(-6, -6, 0);
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(84);
		glPopMatrix();

	glPopMatrix();

	//Back Seat Set
	glPushMatrix();

	glTranslatef(68.5, 11.8, 0);

		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(90);
		glPopMatrix();

		glTranslatef(3, 3, 0);
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(94);
		glPopMatrix();

		glTranslatef(-6, -6, 0);
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		drawSeatRow(84);
		glPopMatrix();

	glPopMatrix();
}


/*______________________________________________________________________________________________________*/
										    /*  DISPLAY  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*______________________________________________________________________________________________________*/

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	//Normal Camera
	if (seat == 0)
		gluLookAt(62 + camX, 10 + camY, 0 + camZ, 0, 0, 0, 0, 1, 0);
	
	//Camera to view Chair
	if (seat == 1)
		gluLookAt(66 + camX, 22 + camY, 0 + camZ, 0, 0, 0, 0, 1, 0);

	////////////////////////////////////////////////////////////////
	Lighting();

	float width = 120, height = 75;

	//Base Foundation
	drawFoundation();

	//Feild
	drawFeild(width, height);
	
	//Lines
	drawFeildLines();

	//Wall IN
	drawWalls(width, height, 5, 1, 0.5, 0.5, 0.2);

	//Wall Out   // ( height / width ) * 130 = 81.25
	drawWalls(width + 10, 81.25, 8, 1, 0.9, 0.6, 0.2);  

	//Stage
	allStage();

	//Flags
	allFlags();

	//Outer Walls
	drawSurroundingWalls(40);

	//Light Panel 
	allPanels();

	//Score Board 
	allScoreBoard();

	//Player
	allPlayers();

	//Goals
	allGoals();

	//Ball
	drawBall();

	//Seats
	if (seat == 1) allSeats();

	////////////////////////////////////////////////////////////////
	glPopMatrix();
	glutSwapBuffers();
}


/*______________________________________________________________________________________________________*/
/*------------------------------------------------------------------------------------------------------*/
											/*  MAIN FUNCTIONS  */

void timer(int x) {
	if (timeCount == 16) {
		if (r == 1) r = 0;
		else r = 1;
		timeCount = 0;
	}
	timeCount++;

	if (hitBall == 1 && hit > -30) hit -= 35;

	if (hit <= 0 && ballX < 183) {
		ballRotation += 35;
		ballX += 6.5;
		ballZ += 1.6;
		keeper += 0.32;
	}

	glutPostRedisplay();
	glutTimerFunc(30, timer, 1);
}

void keyboard(unsigned char key, int x, int y) {

	if (key == 'z')	camZ += cam_speed;
	if (key == 'Z')	camZ -= cam_speed;

	if (key == 'b')	hitBall = 1;

	if (key == '1') glEnable(GL_LIGHT0);
	if (key == '!') glDisable(GL_LIGHT0);

	if (key == '2') glEnable(GL_LIGHT1);
	if (key == '@') glDisable(GL_LIGHT1);

	if (key == '3') glEnable(GL_LIGHT2);
	if (key == '#') glDisable(GL_LIGHT2);

	if (key == 't') tv = 1;
	if (key == 'T') tv = 0;

	//RESET THE CAMERA AND SWITCH SEATS
	if (key == 's')	{
		camX = 0;
		camY = 0;
		camZ = 0;
		seat = 0;
	}

	if (key == 'S') {
		camX = 0;
		camY = 0;
		camZ = 0;
		seat = 1;
	}

	if (key == 27) exit(0);

	glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)	camX += cam_speed;
	if (key == GLUT_KEY_LEFT)	camX -= cam_speed;
	if (key == GLUT_KEY_UP)		camY += cam_speed;
	if (key == GLUT_KEY_DOWN)	camY -= cam_speed;

	glutPostRedisplay();
}

void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialf(GL_FRONT, GL_AMBIENT, 128.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_ambient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, aspect, 1.0, 200.0);
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
	glutTimerFunc(60.0, timer, 1);
	glutSpecialFunc(keyboardSpecial);

	glutFullScreen();
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}