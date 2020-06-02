#pragma once

#include "bmpfuncs.h"
#include "ObjParser.h"
#include "Lego.h"
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
#include<mmsystem.h>

#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
using namespace std;

void init(void);
void resize(int width, int height);

void draw(void);	// �ܼ� draw �Լ�
void draw_skybox(void);		// skybox �׸���

void special_keys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);

void func_Antialiasing(unsigned char key);

void light_default();
void environmentalMapSetting(void);

void mymenu();	// �޴� ����
void main_menu_function(int option);	// mymenu �Լ����� �޴��� ��� �۵��� �� ����

void draw_main();
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);
void draw_preview(void);
void flame_init(void);
void set_flame(int i, int color, int type, Flame Rocket_flame[], LEGO rocket[]);

void idle();
float get_time(void);
void countdown(void);

/* �߻� �� ī�޶� view */
void followcam(void);
void rocketcam(void);
void landscapecam(void); 
void undercam(void);

/* camera location */
double theta = 45.0;
double phi = 45.0;
double radius = 18;
double upVector = cos(phi * M_PI / 180);
double eyex, eyey, eyez;
int core_of_view = 0; // ���� �߽� ����

float g_Rot_x = 0, g_Rot_y = 0, g_Rot_z = 0;	// global ������
float g_loc_x = 0, g_loc_y = 0, g_loc_z = 0;
float launch_y = 0;
int color_select = 1, type_select = 0;
int p_color_select = 1, p_type_select = 0; // preview ��

int xx = 0;     // ���콺�� ���� x ��ǥ
int yy = 0;     // ���콺�� ���� y ��ǥ 
int click = 0;  // ���콺 ���� ��ư�� ������ �� ���� ���� 
int height;

/* time set variable */
clock_t start, moment;
float duration = 0.0;
bool Launch = 0;	// ���� �߻� Flag
bool Launchmode = 0;	// �߻� ��� Flag
bool which_Design = 0;	// ������ ��忡�� � ������ ������, false->rocket true->platfrom
int view_during_launch = 1;		// �߻�� �� �� Flag
bool pre_view = 1; // preview ��� Flag
bool flame_sound = 0;
int component_checker = 0; // 0�� ���, 1�� ������ ��ǰ�� ���� ��, 2�� ������ ��ǰ�� ���µ� �߻�õ��� �� ���

int current_width, current_height;

int rocket_lego_num = 0;	// ������ �����ϴ� ���� �ѹ�
int platform_lego_num = 0;	// �÷����� �����ϴ� ���� �ѹ�
int flame_lego_num = 0;		// Flame�� �����ϴ� object �ѹ�

LEGO rocket[1000];
LEGO platform[1000];
Flame Rocket_flame[100];
LEGO preview;

int main(int argc, char** argv)
{
	/* Initialize window */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Space Rocket Simulator");
	init();

	/* Define Draw Callback */
	glutDisplayFunc(draw);

	/* Ű���� ���ͷ�Ʈ ó�� */
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);

	/* ���콺 ó�� */
	glutMouseFunc(mouse);    // ���콺�� �Է� ó���� �޴� �Լ�
	glutMotionFunc(motion);  // ���콺�� ������ ó���� �޴� �Լ�
	//glutMouseWheelFunc(mouseWheel);

	/* Idle */
	glutIdleFunc(idle);

	/* Reshape */
	glutReshapeFunc(resize);

	/* msg box */
	MessageBox(NULL, TEXT("1 2 3 4 5 6 7 8 9 0 - = to choose lego,\nc to change color, enter to confirm\nqewsad to rotate, r to reset, , . direction keys to move\nu j to adjust the core of view\nbackspace to undo"), TEXT("READ ME"), MB_OK);

	/* menu */
	mymenu();

	/* Main Loop Start! */
	glutMainLoop();

	return 0;
}

void init(void)
{
	Lego_1 = new ObjParser("./obj/lego_1_soften.obj"); //�ش� �޸𸮷� ��ü�� ������ �� �ּ� �����͸� ��ȯ, &�� ��� 
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
	big_flame = new ObjParser("./obj/big_flame.obj");
	small_flame = new ObjParser("./obj/small_flame.obj");

	/* BGM */
	PlaySound(TEXT("./bgm/Starlight.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

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

	//polygon�� ���� ������ �����ϰ� texture�� ����
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
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	draw_main();

	draw_preview();

	glutSwapBuffers();
}

void draw_main()
{
	glPushMatrix();
	glViewport(0, 0, current_width, current_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eyex = radius * sin(theta * M_PI / 180) * cos(phi * M_PI / 180);
	eyey = radius * sin(phi * M_PI / 180);
	eyez = radius * cos(theta * M_PI / 180) * cos(phi * M_PI / 180);
	upVector = cos(phi * M_PI / 180); // simplify upvector correspond to y-axis

	if (Launch == FALSE) {	// �߻� ���� �ƴϸ� ���콺�� ���� ���� 
		gluLookAt(eyex, eyey, eyez, 0, core_of_view, 0, 0, upVector, 0);
	}
	else {	// �߻�Ǹ� countdown �Լ��� ���� ���� ����
		countdown();
	}

	draw_skybox();	// skybox �׸���

	/* �߻� ���� Launch mode���� ��� */
	if (Launchmode) {	
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Launchmode", -9.5, 9, 0, 0, 0);
	}
	else {
		/* ������ ���� Rockect�� Platform �� � ������ ������� ��� */
		if (which_Design) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Platform Designmode", -9.5, 9, 0, 0, 0);
		else if (!which_Design) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Rocket Designmode", -9.5, 9, 0, 0, 0);

	}

	/* �����䰡 ���� �ְ�, �߻��尡 �ƴ� ���� preview���� �˸��� ���� ��� */
	if (pre_view && (!Launchmode)) draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "Preview", 6.5, 9.5, 0, 0, 0);

	/* rocket/platform �� � ������ ��������� ���� set���ִ� object�� �޶��� */
	if (!which_Design)
	{
		rocket[rocket_lego_num].set_lego_color(color_select);
		rocket[rocket_lego_num].set_lego_type(type_select);
		rocket[rocket_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
		rocket[rocket_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z);
	}
	else if (which_Design)
	{
		platform[platform_lego_num].set_lego_color(color_select);
		platform[platform_lego_num].set_lego_type(type_select);
		platform[platform_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
		platform[platform_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z);
	}

	/* ��� platfrom lego draw */
	for (int i = 0; i <= platform_lego_num; i++) {
		glPushMatrix();
		platform[i].draw_lego();
		glPopMatrix();
	}

	if (component_checker==2) {
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "There are no proper components", -9.5, 5, 1, 0, 0);
	}

	/* �߻簡 �Ǹ� launch_y�� idle�� ���� �ٲ��, rocket ���� ���� �����̸� �׷��� */
 	glTranslatef(0, launch_y, 0);

	/* ��� rocket lego draw */
	for (int i = 0; i <= rocket_lego_num; i++) {
		glPushMatrix();
		rocket[i].draw_lego();
		glPopMatrix();
	}

	/* ��� rocket flame draw */
	if (Launch == TRUE && (6000 < get_time())) {
		for (int i = 0; i <= flame_lego_num; i++) {
			glPushMatrix();
			/* flame�� ȸ�� ����ȭ, �Ҳ�ó�� ���̰� */
			Rocket_flame[i].set_flame_rotate(0, rand() % 360, 0);
			Rocket_flame[i].draw_flame();
			glPopMatrix();
		}
	}
	glFlush();
}

/* ���� preview*/
void draw_preview(void)
{
	glMatrixMode(GL_VIEWPORT);
	glPushMatrix();
	glViewport(current_width * 2 / 3, current_height * 2 / 3, current_width / 3, current_height / 3);  
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glClearColor(0, 0, 0., 0);

	double p_eyex, p_eyey, p_eyez;

	p_eyex = 6 * sin(30 * M_PI / 180) * cos(30 * M_PI / 180);
	p_eyey = 6 * sin(30 * M_PI / 180);
	p_eyez = 6 * cos(30 * M_PI / 180) * cos(30 * M_PI / 180);
	gluLookAt(p_eyex, p_eyey, p_eyez, 0, 0, 0, 0, 1, 0);

	glTranslatef(0.5, -1, 0.5);
	preview.set_lego_color(p_color_select);
	preview.set_lego_type(p_type_select);
	preview.set_lego_rotate(0, 0, 0);
	preview.set_lego_location(0, 0, 0);
	// preview�� ���� ���� ���� preview�� ���� draw
	if (pre_view == 1) preview.draw_lego();	

	glPopMatrix();
	glMatrixMode(GL_VIEWPORT);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();

	glFlush();
}

void resize(int width, int height)
{
	/* ���� ����� �޾ƿ� */
	current_width = width;
	current_height = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)width / (float)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == 3) radius *= 0.99;	// ���콺 ���� ������ global (0, 0, 0)���κ����� �Ÿ� ����
	else if (button == 4) radius *= 1.01;

	y = height - y;   // ���콺�� y ��ǥ ��ġ�� ����
	if (state == GLUT_DOWN) {   // ���콺 ��ư�� ������
		xx = x;   // ���� x ��ǥ�� ����
		yy = y;   // ���� y ��ǥ�� ����
		if (button == GLUT_LEFT_BUTTON)   // ���콺 ���� ��ư�� ���� ��
			click = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)   // ���콺 ���� ��ư�� ���� ��
		click = 0;

	glutPostRedisplay();
}

void motion(int x, int y) {   // ���콺�� ������ ó���� �޴� �Լ�
	y = height - y;    // ���콺�� y ��ǥ ��ġ�� ����
	if (click == 1) {  // ���콺 ���� ��ư�� ������
		phi -= (y - yy) / 4;  // �̵��� y ��ǥ�� ����Ͽ� ���� ��ȭ
		theta -= (x - xx) / 4;    // �̵��� x ��ǥ�� ����Ͽ� �浵 ��ȭ
	}
	xx = x;   // ���� x ��ǥ�� ���� x ��ǥ�� ����
	yy = y;   // ���� y ��ǥ�� ���� y ��ǥ�� ����
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

void keyboard(unsigned char key, int x, int y)
{
	if (!Launchmode)	// design mode�� ���� �۵�
	{
		/* lego type ���� */
		if (key == '1') {
			p_type_select = 1;
		}
		if (key == '2') {
			p_type_select = 2;
		}
		if (key == '3') {
			p_type_select = 3;
		}
		if (key == '4') {
			p_type_select = 4;
		}
		if (key == '5') {
			p_type_select = 5;
		}
		if (key == '6') {
			p_type_select = 6;
		}
		if (key == '7') {
			p_type_select = 7;
		}
		if (key == '8') {
			p_type_select = 8;
		}
		if (key == '9') {
			p_type_select = 9;
		}
		if (key == '0') {
			p_type_select = 10;
		}
		if (key == '-') {
			p_type_select = 11;
		}
		if (key == '=') {
			p_type_select = 12;
		}

		/* Lego color ���� */
		if (key == 'c') {
			p_color_select += 1;
			if (p_color_select == 10) p_color_select = 0;
		}

		/* Undo, Rocket/Platform ��� �� �ش�Ǵ� ����� ������ ������� ���� */
		if (key == 8) {	// backspace
			if (which_Design)
			{
				if (platform_lego_num >= 1) platform_lego_num -= 1;
			}
			else if (!which_Design)
			{
				if (rocket_lego_num >= 1) rocket_lego_num -= 1;
			}
		}

		/* Lego tilting */
		if (key == 's') {
			if (g_Rot_x == 355.0f) g_Rot_x = 0.0f;
			else g_Rot_x += 5.0f;
		}
		else if (key == 'w') {
			if (g_Rot_x == 0.0f) g_Rot_x = 355.0f;
			else g_Rot_x -= 5.0f;
		}
		else if (key == 'e') {
			if (g_Rot_y == 355.0f) g_Rot_y = 0.0f;
			else g_Rot_y += 5.0f;
		}
		else if (key == 'q') {
			if (g_Rot_y == 0.0f) g_Rot_y = 355.0f;
			else g_Rot_y -= 5.0f;
		}
		else if (key == 'a') {
			if (g_Rot_z == 355.0f) g_Rot_z = 0.0f;
			else g_Rot_z += 5.0f;
		}
		else if (key == 'd') {
			if (g_Rot_z == 0.0f) g_Rot_z = 355.0f;
			else g_Rot_z -= 5.0f;
		}
		else if (key == 'r') {
			g_Rot_x = 0.0f; g_Rot_y = 0.0f; g_Rot_z = 0.0f;
		}

		/* Lego moving */
		if (key == ',') {
			g_loc_x -= 0.1f;
		}
		else if (key == '.') {
			g_loc_x += 0.1f;
		}

		/* Lego ���� */
		if (key == 13) {	// enter
			/* �����信�� ���� �Է� �� ���� view�� display���ֱ� ���� preview lego�� ������ ���� */
			if (pre_view == 1) {	
				type_select = p_type_select;
				color_select = p_color_select;
				pre_view = 0;
			}
			/* main �信�� ���� �Է�(Lego�� ����)�� Rocket/Platform ��忡 ���� �ش� ���� ���� ����++ */
			else {	
				if (!which_Design)	// 
				{
					rocket_lego_num += 1;
					printf("rocket lego num = %d\n", rocket_lego_num);
				}
				else if (which_Design)
				{
					platform_lego_num += 1;
					printf("platform_lego_num = %d\n", platform_lego_num);
				}

				/* ��� �׸� �ʱ�ȭ */
				//g_Rot_x = 0.0f; g_Rot_y = 0.0f; g_Rot_z = 0.0f;
				//g_loc_x = 0.0f; g_loc_y = 0.0f; g_loc_z = 0.0f;	// ��ġ�� ȸ���� �ʱ�ȭ���� ���Ǹ� ���� �ʱ�ȭ X
				type_select = 0; color_select = 0; pre_view = 1; p_type_select = 0;
			}
		}
	}
	else if (Launchmode)	// Launch mode�� ���� �۵� 
	{
		/* Launch rocket */
		if (key == ' ') {	// space bar
			component_checker = 2;

			/* �߻縦 ���� ���� ������ �߻簡 ���� ����*/
			for (int i = 0; i <= rocket_lego_num; i++) {
				if ((rocket[i].get_lego_type() == 9) || (rocket[i].get_lego_type() == 12))
				component_checker = 1;
			}

			if (!Launch && (component_checker==1)) {	// �߻� �߿� �߻�� �Ұ���
				Launch = TRUE;	// ���� �߻� Flag
				start = clock();	// �߻��� ���� ����
				/* ī��Ʈ�ٿ� + �߻� ���� */
				PlaySound(TEXT("./bgm/590318main_ringtone_135_launch.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				/* flame initiating */
				flame_init(); 
			}
		}

		/* Camera view, �߻� ���߿� view �ٲٱ� */
		if (key == '1') {
			view_during_launch = 1;
		}
		else if (key == '2') {
			view_during_launch = 2;
			if (!flame_sound && Launch) {
				PlaySound(TEXT("./bgm/71150__timbre__simulation-of-nasa-rocket-launch.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				flame_sound = TRUE;
			}
		}
		else if (key == '3') {
			view_during_launch = 3;
			if (!flame_sound && Launch) {
				PlaySound(TEXT("./bgm/71150__timbre__simulation-of-nasa-rocket-launch.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				flame_sound = TRUE;
			}
		}
		else if (key == '4') {
			view_during_launch = 4; 
			if (!flame_sound && Launch) {
				PlaySound(TEXT("./bgm/71150__timbre__simulation-of-nasa-rocket-launch.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
				flame_sound = TRUE;
			}
		}
	}

	// B�� ���� Antialiasing on/off
	func_Antialiasing(key);

	/* ���� �߽� ���� */
	switch (key) {
	case 'u':
		core_of_view++;
		break;
	case'j':
		core_of_view--;
	}

	glutPostRedisplay();
}

void special_keys(int key, int x, int y) {
	/* Lego moving */
	if (!Launchmode) {
		if (key == GLUT_KEY_LEFT) {
			g_loc_z += 0.1f;
		}
		else if (key == GLUT_KEY_RIGHT) {
			g_loc_z -= 0.1f;
		}
		else if (key == GLUT_KEY_UP) {
			g_loc_y += 0.1f;
		}
		else if (key == GLUT_KEY_DOWN) {
			g_loc_y -= 0.1f;
		}
	}
	glutPostRedisplay();
}

float get_time(void)	// �߻��� �ķκ��� �ð��� ���.
{
	moment = clock();	// ���� �ð� ȹ��
	duration = (float)(moment - start);	// �߻� �ð����� ���� �ð�����

	return duration;	// �߻��� �ķ� �󸶳� ������ ��
}

/* launch_y�� ���� ��� ���� ���� �÷��� �׸�(�߻� ǥ��) */
void idle(void)
{
	if (Launch == TRUE && (get_time() > 23000)) {	// ���� �߻� ���̰�, �߻����� 20001~
		launch_y += 0.2f;
	}
	else if (Launch == TRUE && (13000 <= get_time() && get_time() <= 23000)) { // ���� �߻� ���̰�, �߻����� 10000~20000
		launch_y += 0.1f;
	}

	glutPostRedisplay();
}

/* �߻縦 ���� countdown, �߻縦 ������ 10000 �ڿ� ������ �߻簡 �ȴ�.
1000���� view�� �����ϰ�, 5000���ʹ� view ����, 10000�� �Ѿ�� view_during_launch
������ ���� view ���� ����*/
void countdown(void)
{
	if (Launch == TRUE && (0 <= get_time() && get_time() <= 1000)) {
		gluLookAt(25, 25, 25, 0, 10, 0, 0, upVector, 0);
	}
	else if (Launch == TRUE && (0 < get_time() && get_time() <= 2000)) {
		gluLookAt(150, 20, 20, 0, 10, 0, 0, upVector, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "10", -5.4, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (2000 < get_time() && get_time() <= 3000)) {
		gluLookAt(20, 20, 130, 0, 10, 0, 0, upVector, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "9", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (3000 < get_time() && get_time() <= 4000)) {
		gluLookAt(100, 25, 25, 0, 10, 0, 0, upVector, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "8", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (4000 < get_time() && get_time() <= 5000)) {
		gluLookAt(25, 25, 70, 0, 10, 0, 0, upVector, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "7", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (5000 < get_time() && get_time() <= 6000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "6", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (6000 < get_time() && get_time() <= 7000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "5", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (7000 < get_time() && get_time() <= 8500)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "4", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (8500 < get_time() && get_time() <= 10000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "3", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (10000 < get_time() && get_time() <= 11000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "2", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (11000 < get_time() && get_time() <= 12000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "1", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (12000 < get_time() && get_time() <= 13000)) {
		followcam();
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "0", -5.25, 0, 1, 0, 0);
	}
	else if (Launch == TRUE && (13000 < get_time() && get_time() <= 14000)) {
		if (view_during_launch == 1) followcam();		// toward rocket
		else if (view_during_launch == 2) rocketcam();		// toward ground
		else if (view_during_launch == 3) landscapecam();		// toward landscape
		else if (view_during_launch == 4) undercam();		// undercam

		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Launch", -6.5, 0, 1, 0, 0);
	}
	else {
		if (view_during_launch == 1) followcam();		// toward rocket
		else if (view_during_launch == 2) rocketcam();		// toward ground
		else if (view_during_launch == 3) landscapecam();		// toward landscape
		else if (view_during_launch == 4) undercam();		// undercam
	}
}

void followcam(void) // toward rocket
{
	if (int(get_time()) % 3 == 0) gluLookAt(50, 30, 30, -0.35, 10 + launch_y, -0.35, 0, upVector, 0);
	else if (int(get_time()) % 3 == 1) gluLookAt(50, 30, 30, 0, 10 + launch_y, 0, 0, upVector, 0);
	else if (int(get_time()) % 3 == 2) gluLookAt(50, 30, 30, 0.35, 10 + launch_y, 0.35, 0, upVector, 0);
}
void rocketcam(void) // toward ground
{
	if (int(get_time()) % 3 == 0) gluLookAt(1.35, 10 + launch_y, 1.35, 1.7, 0, 1.7, 1, 0, 0);
	else if (int(get_time()) % 3 == 1) gluLookAt(1.35, 10 + launch_y, 1.35, 1.35, 0, 1.35, 1, 0, 0);
	else if (int(get_time()) % 3 == 2) gluLookAt(1.35, 10 + launch_y, 1.35, 1.0, 0, 1.0, 1, 0, 0);
}
void landscapecam(void) // toward landscape
{
	if (int(get_time()) % 3 == 0) gluLookAt(-1.7, 10 + launch_y, 0, -180, launch_y, 180, 0, upVector, 0);
	else if (int(get_time()) % 3 == 1) gluLookAt(-1.7, 10 + launch_y, 0, -200, launch_y, 200, 0, upVector, 0);
	else if (int(get_time()) % 3 == 2) gluLookAt(-1.7, 10 + launch_y, 0, -220, launch_y, 220, 0, upVector, 0);
}
void undercam(void) // undercam
{
	if (int(get_time()) % 3 == 0) gluLookAt(15, -3 + launch_y, 15, -0.2, 3 + launch_y, -0.2, 0, upVector, 0);
	else if (int(get_time()) % 3 == 1) gluLookAt(15, -3 + launch_y, 15, 0, 3 + launch_y, 0, 0, upVector, 0);
	else if (int(get_time()) % 3 == 2) gluLookAt(15, -3 + launch_y, 15, 0.2, 3 + launch_y, 0.2, 0, upVector, 0);
}

void mymenu()
{
	glutCreateMenu(main_menu_function);

	glutAddMenuEntry("save rocket model", 1);
	glutAddMenuEntry("save platform model", 2);
	glutAddMenuEntry("load rocket model", 3);
	glutAddMenuEntry("load platform model", 4);
	glutAddMenuEntry("launch mode", 5);
	glutAddMenuEntry("clear lego", 9);

	glutAddMenuEntry("design rocket", 10);
	glutAddMenuEntry("design platform", 11);

	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

FILE* out;	// file ���� ����

void main_menu_function(int option) {
	switch (option)
	{
	case 1:	// save rocket model
		printf("Save rocket model has selected\n");
		fopen_s(&out, "rocket1.txt", "w");	// rocket1.txt�� write
		for (int i = 0; i <= rocket_lego_num; i++) {	// rocket_lego_num�� �÷����� �ϳ��ϳ� ����
			fprintf(out, "%d, %d, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n",
				// �����ȣ, type, color �� %d��, ������ location�� rotation�� �Ҽ��� ��° �ڸ����� ���� (porque 0.1������ ����)
				i, rocket[i].get_lego_type(), rocket[i].get_lego_color(),
				rocket[i].get_lego_location_x(), rocket[i].get_lego_location_y(), rocket[i].get_lego_location_z(),
				rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		}
		fclose(out);
		break;
	case 2:	// save platform model
		printf("Save platform model has selected\n");
		fopen_s(&out, "platform1.txt", "w");	// platform1.txt�� write
		for (int i = 0; i <= platform_lego_num; i++) {	// platform_lego_num�� �÷����� �ϳ��ϳ� ����
			fprintf(out, "%d, %d, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n",
				// �����ȣ, type, color �� %d��, ������ location�� rotation�� �Ҽ��� ��° �ڸ����� ���� (porque 0.1������ ����)
				i, platform[i].get_lego_type(), platform[i].get_lego_color(),
				platform[i].get_lego_location_x(), platform[i].get_lego_location_y(), platform[i].get_lego_location_z(),
				platform[i].get_lego_rotate_x(), platform[i].get_lego_rotate_y(), platform[i].get_lego_rotate_z());
		}
		fclose(out);
		break;
	case 3:	// load rocket model
		printf("Load rocket model has selected\n");
		fopen_s(&out, "rocket1.txt", "r"); // rocket1.txt�� read
		while (!feof(out)) {	// ������ ���� ������ 
			fscanf_s(out, "%d, %d, %d, %f, %f, %f, %f, %f, %f \n",
				// �о�� ���� �׳� %f�� �о�� ��
				&rocket_lego_num, &type_select, &color_select,
				&g_loc_x, &g_loc_y, &g_loc_z, &g_Rot_x, &g_Rot_y, &g_Rot_z);

			rocket[rocket_lego_num].set_lego_color(color_select);
			rocket[rocket_lego_num].set_lego_type(type_select);
			rocket[rocket_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
			rocket[rocket_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z); // ���� �������� �� ���� �ٷ� set
		}
		fclose(out);
		break;
	case 4:	// load platform model
		printf("Load platform model has selected\n");
		fopen_s(&out, "platform1.txt", "r"); // launch_platform1.txt�� read
		while (!feof(out)) {	// ������ ���� ������ 
			fscanf_s(out, "%d, %d, %d, %f, %f, %f, %f, %f, %f \n",
				// �о�� ���� �׳� %f�� �о�� ��
				&platform_lego_num, &type_select, &color_select,
				&g_loc_x, &g_loc_y, &g_loc_z, &g_Rot_x, &g_Rot_y, &g_Rot_z);

			platform[platform_lego_num].set_lego_color(color_select);
			platform[platform_lego_num].set_lego_type(type_select);
			platform[platform_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
			platform[platform_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z); // ���� �������� �� ���� �ٷ� set
		}
		fclose(out);
		break;
	case 5:	// launch mode
		printf("launch mode has selected\n");
		glutChangeToMenuEntry(5, "design mode", 6); //5��° �޴��� case 6�� design�� �ȴ�
		Launchmode = 1;	// Launch mode�� ���ٴ� Flag
		type_select = 0; // �������� ���� ����� �������
		pre_view = 0; // preview�� ����
		break;
	case 6:	// design mode
		printf("design mode has selected\n");
		glutChangeToMenuEntry(5, "launch mode", 5); //5��° �޴��� case 5�� Load �� �ȴ�
		Launchmode = 0; // design mode�� ��.
		component_checker = 0; 
		pre_view = 1; // preview�� �ٽ� ���ش�.
		break;

	case 9:	// clear lego
		if (!Launch) {
			printf("Clear lego\n");
			/* ������ ������ ��� 0���� ������ش�. */
			platform_lego_num = 0;
			rocket_lego_num = 0;
			/*�ܼ��� ���� ������ 0���� ����� �ִ� �����δ� ���� ��尡 �ƴ� ���� ���� ù��° ���� �׷���
			(ex. rocket design ����� ��, platform�� ù��° ������ type�� ���� �־� �׷����� ��)
			���� ��� ���� ù��° ������ Ÿ���� �ʱ�ȭ ���־�� ��.*/
			rocket[rocket_lego_num].set_lego_type(0);
			platform[platform_lego_num].set_lego_type(0);
		}
		break;
	case 10:	// design rocket mode
		printf("now you can design rocket\n");
		which_Design = 0;
		break;
	case 11:	// design platform mode
		printf("now you can design platform\n");
		which_Design = 1;
		break;
	case 999:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

/* string �׸��� �Լ� */
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(red, green, blue);
	glRasterPos3f(x_position, y_position, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

/* flame initiating */
void flame_init(void)
{
	for (int i = 0; i <= rocket_lego_num; i++)
	{
		/* 1���� ���ⱸ�� �־� �Ҳ� ������ 1�� ����, ���ⱸ�� ��ġ�� �״�� �޾� �´�*/
		if (rocket[i].get_lego_type() == 9)
		{
			/* color 1 */
			set_flame(i, 1, 1, Rocket_flame, rocket);
			/* color 2 */
			set_flame(i, 2, 1, Rocket_flame, rocket);
			/* color 3 */
			set_flame(i, 3, 1, Rocket_flame, rocket);
		}
		/* 4���� ���ⱸ�� �־� �Ҳ� ������ 4�� ���� */
		if (rocket[i].get_lego_type() == 12)
		{
			/* color 1 */
			set_flame(i, 1, 2, Rocket_flame, rocket);
			/* color 2 */
			set_flame(i, 2, 2, Rocket_flame, rocket);
			/* color 3 */
			set_flame(i, 3, 2, Rocket_flame, rocket);
		}
	}
}

/* flame�� �ʱ� ��ġ�� ���ⱸ�� ��ġ�� ���� ���� */
void set_flame(int i, int color, int type, Flame Rocket_flame[], LEGO rocket[]) 
{	
	if (type == 1) 
	{
		Rocket_flame[flame_lego_num].set_flame_color(color);
		Rocket_flame[flame_lego_num].set_flame_type(type);
		Rocket_flame[flame_lego_num].set_flame_location(rocket[i].get_lego_location_x(), rocket[i].get_lego_location_y(), rocket[i].get_lego_location_z());
		Rocket_flame[flame_lego_num].set_flame_rotate(rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());

		flame_lego_num++;
	}
	else if (type == 2)
	{
		Rocket_flame[flame_lego_num].set_flame_color(color);
		Rocket_flame[flame_lego_num].set_flame_type(type);
		Rocket_flame[flame_lego_num].set_flame_location(rocket[i].get_lego_location_x() + 0.2, rocket[i].get_lego_location_y() - 0.2, rocket[i].get_lego_location_z() + 0.2);
		Rocket_flame[flame_lego_num].set_flame_rotate(rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		flame_lego_num++;
		Rocket_flame[flame_lego_num].set_flame_color(color);
		Rocket_flame[flame_lego_num].set_flame_type(type);
		Rocket_flame[flame_lego_num].set_flame_location(rocket[i].get_lego_location_x() + 0.2, rocket[i].get_lego_location_y() - 0.2, rocket[i].get_lego_location_z() - 0.2);
		Rocket_flame[flame_lego_num].set_flame_rotate(rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		flame_lego_num++;		
		Rocket_flame[flame_lego_num].set_flame_color(color);
		Rocket_flame[flame_lego_num].set_flame_type(type);
		Rocket_flame[flame_lego_num].set_flame_location(rocket[i].get_lego_location_x() - 0.2, rocket[i].get_lego_location_y() - 0.2, rocket[i].get_lego_location_z() + 0.2);
		Rocket_flame[flame_lego_num].set_flame_rotate(rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		flame_lego_num++;
		Rocket_flame[flame_lego_num].set_flame_color(color);
		Rocket_flame[flame_lego_num].set_flame_type(type);
		Rocket_flame[flame_lego_num].set_flame_location(rocket[i].get_lego_location_x() - 0.2, rocket[i].get_lego_location_y() - 0.2, rocket[i].get_lego_location_z() - 0.2);
		Rocket_flame[flame_lego_num].set_flame_rotate(rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		flame_lego_num++;
	}
}