#pragma once

#include "bmpfuncs.h"
#include "ObjParser.h"
#define _USE_MATH_DEFINES   
#include <gl/glut.h>
#include <gl/glext.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)

using namespace std;

void init(void);
void resize(int width, int height);

void draw(void);
void draw_axis(void);
void draw_lego(ObjParser *objParser, int i);
void draw_obj(ObjParser *objParser);
void draw_skybox(void);

void special_keys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

void light_default();
void environmentalMapSetting(void);

void idle();
float get_time(void);

/* camera location */
double theta = 45.0;
double phi = 45.0;
double radius = 18;
double upVector = cos(phi*M_PI / 180);
double eyex, eyey, eyez;

/* lego tilting */
float loc_x, loc_y, loc_z = 0;
int Rot_x, Rot_y, Rot_z = 0;

/* Antialiasing */
bool Antialiasing = false;

/* time set variable */
clock_t start, moment;
float duration = 0.0;
bool Launch = false;

/* texture mapping set variable */
GLuint g_nCubeTex;

/* lego */
ObjParser *Lego_1, *Lego_2, *Lego_3, *Lego_4, *Lego_5, *Lego_6, *Lego_7, *Lego_8, *Lego_9, *Lego_10, *Lego_11, *Lego_12;

int main(int argc, char **argv)
{
	/* Initialize window */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init();

	/* Define Draw Callback */
	glutDisplayFunc(draw);

	/* 키보드 인터럽트 처리 */
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);

	/* 마우스 처리 */
	glutMouseFunc(mouse);
	//glutMouseWheelFunc(mouseWheel);

	/* Idle */
	glutIdleFunc(idle);

	/* Reshape */
	glutReshapeFunc(resize);

	/* msg box */
	MessageBox(NULL, TEXT("No EYE"), TEXT("EYE"), MB_OK);

	/* Main Loop Start! */
	glutMainLoop();

	return 0;
}

void init(void)
{
	Lego_1 = new ObjParser("./obj/lego_1_soften.obj"); //해당 메모리로 객체를 만든후 그 주소 포인터를 반환, &랑 비슷 
	Lego_2 = new ObjParser("./obj/lego_2_soften.obj");
	Lego_3 = new ObjParser("./obj/lego_3_soften.obj");
	Lego_4 = new ObjParser("./obj/lego_4_soften.obj");
	Lego_5 = new ObjParser("./obj/lego_5_soften.obj");
	Lego_6 = new ObjParser("./obj/lego_6_soften.obj");
	Lego_7 = new ObjParser("./obj/lego_7_soften.obj");
	Lego_8 = new ObjParser("./obj/lego_8_soften.obj");
	Lego_9 = new ObjParser("./obj/lego_9_soften.obj");
	Lego_10 = new ObjParser("./obj/lego_10_soften.obj");
	Lego_11 = new ObjParser("./obj/lego_11_soften.obj");
	Lego_12 = new ObjParser("./obj/lego_12_soften.obj");

	/* Background color :  Black */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Default Object Color Set : Black */
	glColor3f(1.0f, 1.0f, 1.0f);

	/* resize callback */
	glutReshapeFunc(resize);

	/* light setting */
	light_default();

	/* skybox setting*/
	environmentalMapSetting();

	//polygon의 원래 색상은 무시하고 texture로 덮음
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	/* Front face */
	glFrontFace(GL_CCW);

	/* Enable depth buffer */
	glEnable(GL_DEPTH_TEST);
}

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eyex = radius * sin(theta*M_PI / 180)*cos(phi*M_PI / 180);
	eyey = radius * sin(phi*M_PI / 180);
	eyez = radius * cos(theta*M_PI / 180)*cos(phi*M_PI / 180);
	upVector = cos(phi*M_PI / 180); // simplify upvector correspond to y-axis

	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, upVector, 0);

	//glPushMatrix();
	draw_skybox();
	//glPopMatrix();

	//glColor3f(1.0f, 0.7f, 0.0f);
	//glutSolidSphere(50, 30, 30);
	//glTranslatef(0, 50, 0);
	draw_axis();

	// move lego
	glTranslatef(loc_x, loc_y, loc_z);

	//rotate on x axis
	glRotatef(Rot_x, 1.0, 0.0, 0.0);

	//rotate on y axis
	glRotatef(Rot_y, 0.0, 1.0, 0.0);

	//rotate on z axis
	glRotatef(Rot_z, 0.0, 0.0, 1.0);

	draw_lego(Lego_8, 7);

	glutSwapBuffers();
}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == 3) radius *= 0.99;
	else if (button == 4) radius *= 1.01;

	glutPostRedisplay();
}

void light_default() {
	glClearColor(0, 0, 0, 1.0f);

	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	/************* spot position setting *************/
	//GLfloat spot_direction[] = { 0.0, 0.0, -2.0, 1.0 };
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5);

	GLfloat ambientMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularMaterial[] = { 0.9f, 0.9f, 0.9f, 1.0f };

	/************* Material  setting *************/
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	/* global light setting */
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void keyboard(unsigned char key, int x, int y) {

	/* Antialiasing */
	if (key == 'b') {
		printf("You pressed a\n");

		if (Antialiasing) Antialiasing = false;
		else Antialiasing = true;

		if (Antialiasing) {
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

			printf("Antialiasing on\n");
		}
		else {
			glDisable(GL_POINT_SMOOTH);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);

			printf("Antialiasing off\n");
		}
	}

	/* tilting */
	if (key == 's') {
		if (Rot_x == 355) Rot_x = 0;
		else Rot_x += 5;
	}
	else if (key == 'w') {
		if (Rot_x == 0) Rot_x = 355;
		else Rot_x -= 5;
	}
	else if (key == 'e') {
		if (Rot_y == 355) Rot_y = 0;
		else Rot_y += 5;
	}
	else if (key == 'q') {
		if (Rot_y == 0) Rot_y = 355;
		else Rot_y -= 5;
	}
	else if (key == 'a') {
		if (Rot_z == 355) Rot_z = 0;
		else Rot_z += 5;
	}
	else if (key == 'd') {
		if (Rot_z == 0) Rot_z = 355;
		else Rot_z -= 5;
	}
	else if (key == 'r') {
		Rot_x = 0; Rot_y = 0; Rot_z = 0;
	}

	/* moving */
	if (key == ',') {
		loc_x -= 0.1;
	}
	else if (key == '.') {
		loc_x += 0.1;
	}

	/* Launch rocket */
	if (key == ' ') {
		Launch = TRUE;
		start = clock();
	}

	/* move camera */
	switch (key) {
	case 'j':
		theta -= 1;
		if (theta == -360) theta = 0.0;
		break;
	case 'l':
		theta += 1;
		if (theta == 360) theta = 0.0;
		break;
	case 'k':
		phi -= 1;
		if (abs((int)phi) % 360 == 0) phi = 0.0;
		break;
	case 'i':
		phi += 1;
		if (abs((int)phi) % 360 == 0) phi = 0.0;
		break;
	default:
		printf("%d is pressed\n", key);
		break;
	}
	glutPostRedisplay();
}

void special_keys(int key, int x, int y) {
	/* moving */
	if (key == GLUT_KEY_LEFT) {
		loc_z += 0.1;
	}
	else if (key == GLUT_KEY_RIGHT) {
		loc_z -= 0.1;
	}
	else if (key == GLUT_KEY_UP) {
		loc_y += 0.1;
	}
	else if (key == GLUT_KEY_DOWN) {
		loc_y -= 0.1;
	}

	glutPostRedisplay();
}

void draw_axis(void)
{
	glLineWidth(3); // 좌표축의 두께
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(5, 0, 0); // x축은 red

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5, 0); // y축은 green


	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5); // z축은 blue
	glEnd();
	glLineWidth(1); // 좌표축의 두께
}

void draw_lego(ObjParser *objParser, int i) {
	switch (i) {
	case 1: glColor3f(1.0f, 1.0f, 1.0f);  draw_obj(objParser); // White
	case 2: glColor3f(0.117647f, 0.564706f, 1.0f);  draw_obj(objParser); // blue
	case 3: glColor3f(0.133333f, 0.545098f, 0.133333f);  draw_obj(objParser); // Green
	case 4: glColor3f(0.580392f, 0.0f, 0.827451f);  draw_obj(objParser); // Purple
	case 5: glColor3f(0.85f, 0.0f, 0.0f);  draw_obj(objParser); // Red
	case 6: glColor3f(0.2f, 0.8f, 1.0f);  draw_obj(objParser); // Sky
	case 7: glColor3f(1.0f, 0.270588f, 0.0f);  draw_obj(objParser); // Orange
	case 8: glColor3f(1.0f, 0.311765f, 0.605882f);  draw_obj(objParser); // Pink
	case 9: glColor3f(0.1f, 0.1f, 0.1f);  draw_obj(objParser); // Black
	}
}

void draw_obj(ObjParser *objParser) {
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) { //obj parser에서 3면의 face를 받아온다
																	 //우선 n-1부터, 전
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x, // normal 인덱스를 받아옴 
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x, //vertice 인덱스
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

void idle(void)
{
	if (Launch == TRUE && (get_time() > 1000)) {
		loc_y += 0.3;
	}
	else if (Launch == TRUE && (get_time() <= 1000)) {
		loc_y += 0.11;
	}

	glutPostRedisplay();
}

float get_time(void)
{
	moment = clock();
	duration = (float)(moment - start);

	return duration;
}

void draw_skybox() {
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	float g_nSkySize = 100.0;

	glTranslatef(0, g_nSkySize, 0);

	glBegin(GL_QUADS);
	//px
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	//nx
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	//py
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	//ny
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	//pz
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	//nz
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);

	glEnd();

	glTranslatef(0, -g_nSkySize, 0);

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_CUBE_MAP);
}

void environmentalMapSetting(void) {
	glGenTextures(1, &g_nCubeTex);
	int imgWidth, imgHeight, channels;

	uchar* img0 = readImageData("./skybox/bumsz-cwkf6.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img1 = readImageData("./skybox/bumsz-cwkf6.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img2 = readImageData("./skybox/bumsz-cwkf6.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img3 = readImageData("./skybox/256ny.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img4 = readImageData("./skybox/256pz.bmp", &imgWidth, &imgHeight, &channels);
	uchar* img5 = readImageData("./skybox/256nz.bmp", &imgWidth, &imgHeight, &channels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);
	//glEnable(GL_TEXTURE_CUBE_MAP);
}
