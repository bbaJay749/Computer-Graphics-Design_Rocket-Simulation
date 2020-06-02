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

void draw(void);	// 단순 draw 함수
void draw_skybox(void);		// skybox 그리기

void special_keys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);

void func_Antialiasing(unsigned char key);

void light_default();
void environmentalMapSetting(void);

void mymenu();	// 메뉴 설정
void main_menu_function(int option);	// mymenu 함수에서 메뉴가 어떻게 작동할 지 설정

void draw_main();
void draw_string(void* font, const char* str, float x_position, float y_position, float red, float green, float blue);
void draw_preview(void);
void flame_init(void);
void set_flame(int i, int color, int type, Flame Rocket_flame[], LEGO rocket[]);

void idle();
float get_time(void);
void countdown(void);

/* 발사 시 카메라 view */
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
int core_of_view = 0; // 뷰의 중심 조절

float g_Rot_x = 0, g_Rot_y = 0, g_Rot_z = 0;	// global 변수들
float g_loc_x = 0, g_loc_y = 0, g_loc_z = 0;
float launch_y = 0;
int color_select = 1, type_select = 0;
int p_color_select = 1, p_type_select = 0; // preview 용

int xx = 0;     // 마우스의 이전 x 좌표
int yy = 0;     // 마우스의 이전 y 좌표 
int click = 0;  // 마우스 왼쪽 버튼을 누르고 뗄 때의 변수 
int height;

/* time set variable */
clock_t start, moment;
float duration = 0.0;
bool Launch = 0;	// 실제 발사 Flag
bool Launchmode = 0;	// 발사 모드 Flag
bool which_Design = 0;	// 디자인 모드에서 어떤 디자인 중인지, false->rocket true->platfrom
int view_during_launch = 1;		// 발사된 후 뷰 Flag
bool pre_view = 1; // preview 사용 Flag
bool flame_sound = 0;
int component_checker = 0; // 0은 평시, 1은 적절한 부품이 있을 때, 2는 적절한 부품이 없는데 발사시도를 한 경우

int current_width, current_height;

int rocket_lego_num = 0;	// 로켓을 구성하는 레고 넘버
int platform_lego_num = 0;	// 플랫폼을 구성하는 레고 넘버
int flame_lego_num = 0;		// Flame을 구성하는 object 넘버

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

	/* 키보드 인터럽트 처리 */
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);

	/* 마우스 처리 */
	glutMouseFunc(mouse);    // 마우스의 입력 처리를 받는 함수
	glutMotionFunc(motion);  // 마우스의 움직임 처리를 받는 함수
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

	if (Launch == FALSE) {	// 발사 중이 아니면 마우스로 시점 조정 
		gluLookAt(eyex, eyey, eyez, 0, core_of_view, 0, 0, upVector, 0);
	}
	else {	// 발사되면 countdown 함수에 의해 시점 조정
		countdown();
	}

	draw_skybox();	// skybox 그리기

	/* 발사 모드면 Launch mode임을 출력 */
	if (Launchmode) {	
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Launchmode", -9.5, 9, 0, 0, 0);
	}
	else {
		/* 디자인 모드면 Rockect과 Platform 중 어떤 디자인 모드인지 출력 */
		if (which_Design) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Platform Designmode", -9.5, 9, 0, 0, 0);
		else if (!which_Design) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Rocket Designmode", -9.5, 9, 0, 0, 0);

	}

	/* 프리뷰가 켜져 있고, 발사모드가 아닐 때면 preview임을 알리는 문구 출력 */
	if (pre_view && (!Launchmode)) draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "Preview", 6.5, 9.5, 0, 0, 0);

	/* rocket/platform 중 어떤 디자인 모드인지에 따라 set해주는 object가 달라짐 */
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

	/* 모든 platfrom lego draw */
	for (int i = 0; i <= platform_lego_num; i++) {
		glPushMatrix();
		platform[i].draw_lego();
		glPopMatrix();
	}

	if (component_checker==2) {
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "There are no proper components", -9.5, 5, 1, 0, 0);
	}

	/* 발사가 되면 launch_y가 idle에 따라 바뀌고, rocket 레고가 위로 움직이며 그려짐 */
 	glTranslatef(0, launch_y, 0);

	/* 모든 rocket lego draw */
	for (int i = 0; i <= rocket_lego_num; i++) {
		glPushMatrix();
		rocket[i].draw_lego();
		glPopMatrix();
	}

	/* 모든 rocket flame draw */
	if (Launch == TRUE && (6000 < get_time())) {
		for (int i = 0; i <= flame_lego_num; i++) {
			glPushMatrix();
			/* flame의 회전 랜덤화, 불꽃처럼 보이게 */
			Rocket_flame[i].set_flame_rotate(0, rand() % 360, 0);
			Rocket_flame[i].draw_flame();
			glPopMatrix();
		}
	}
	glFlush();
}

/* 우상단 preview*/
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
	// preview가 켜져 있을 때만 preview용 레고를 draw
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
	/* 현재 사이즈를 받아옴 */
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
	if (button == 3) radius *= 0.99;	// 마우스 휠을 움직여 global (0, 0, 0)으로부터의 거리 조절
	else if (button == 4) radius *= 1.01;

	y = height - y;   // 마우스의 y 좌표 위치를 설정
	if (state == GLUT_DOWN) {   // 마우스 버튼을 누르면
		xx = x;   // 눌린 x 좌표를 저장
		yy = y;   // 눌린 y 좌표를 저장
		if (button == GLUT_LEFT_BUTTON)   // 마우스 왼쪽 버튼을 누를 때
			click = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)   // 마우스 왼쪽 버튼을 뗐을 때
		click = 0;

	glutPostRedisplay();
}

void motion(int x, int y) {   // 마우스의 움직임 처리를 받는 함수
	y = height - y;    // 마우스의 y 좌표 위치를 설정
	if (click == 1) {  // 마우스 왼쪽 버튼을 누르면
		phi -= (y - yy) / 4;  // 이동한 y 좌표에 비례하여 위도 변화
		theta -= (x - xx) / 4;    // 이동한 x 좌표에 비례하여 경도 변화
	}
	xx = x;   // 현재 x 좌표를 이전 x 좌표로 저장
	yy = y;   // 현재 y 좌표를 이전 y 좌표로 저장
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
	if (!Launchmode)	// design mode일 때만 작동
	{
		/* lego type 결정 */
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

		/* Lego color 결정 */
		if (key == 'c') {
			p_color_select += 1;
			if (p_color_select == 10) p_color_select = 0;
		}

		/* Undo, Rocket/Platform 모드 중 해당되는 모드의 마지막 레고부터 삭제 */
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

		/* Lego 고정 */
		if (key == 13) {	// enter
			/* 프리뷰에서 엔터 입력 시 실제 view에 display해주기 위해 preview lego의 변수들 전달 */
			if (pre_view == 1) {	
				type_select = p_type_select;
				color_select = p_color_select;
				pre_view = 0;
			}
			/* main 뷰에서 엔터 입력(Lego를 고정)시 Rocket/Platform 모드에 따라 해당 모델의 레고 개수++ */
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

				/* 모든 항목 초기화 */
				//g_Rot_x = 0.0f; g_Rot_y = 0.0f; g_Rot_z = 0.0f;
				//g_loc_x = 0.0f; g_loc_y = 0.0f; g_loc_z = 0.0f;	// 위치와 회전은 초기화하지 편의를 위해 초기화 X
				type_select = 0; color_select = 0; pre_view = 1; p_type_select = 0;
			}
		}
	}
	else if (Launchmode)	// Launch mode일 때만 작동 
	{
		/* Launch rocket */
		if (key == ' ') {	// space bar
			component_checker = 2;

			/* 발사를 위한 레고가 없으면 발사가 되지 않음*/
			for (int i = 0; i <= rocket_lego_num; i++) {
				if ((rocket[i].get_lego_type() == 9) || (rocket[i].get_lego_type() == 12))
				component_checker = 1;
			}

			if (!Launch && (component_checker==1)) {	// 발사 중에 발사는 불가능
				Launch = TRUE;	// 실제 발사 Flag
				start = clock();	// 발사한 시점 저장
				/* 카운트다운 + 발사 음향 */
				PlaySound(TEXT("./bgm/590318main_ringtone_135_launch.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
				/* flame initiating */
				flame_init(); 
			}
		}

		/* Camera view, 발사 도중에 view 바꾸기 */
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

	// B를 눌러 Antialiasing on/off
	func_Antialiasing(key);

	/* 시점 중심 조절 */
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

float get_time(void)	// 발사한 후로부터 시간을 잰다.
{
	moment = clock();	// 현재 시각 획득
	duration = (float)(moment - start);	// 발사 시각에서 현재 시각빼기

	return duration;	// 발사한 후로 얼마나 지났는 지
}

/* launch_y를 통해 모든 레고를 위로 올려서 그림(발사 표현) */
void idle(void)
{
	if (Launch == TRUE && (get_time() > 23000)) {	// 실제 발사 중이고, 발사한지 20001~
		launch_y += 0.2f;
	}
	else if (Launch == TRUE && (13000 <= get_time() && get_time() <= 23000)) { // 실제 발사 중이고, 발사한지 10000~20000
		launch_y += 0.1f;
	}

	glutPostRedisplay();
}

/* 발사를 위한 countdown, 발사를 누르고 10000 뒤에 실제로 발사가 된다.
1000마다 view를 변경하고, 5000부터는 view 고정, 10000이 넘어가면 view_during_launch
조정을 통해 view 변경 가능*/
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

FILE* out;	// file 변수 설정

void main_menu_function(int option) {
	switch (option)
	{
	case 1:	// save rocket model
		printf("Save rocket model has selected\n");
		fopen_s(&out, "rocket1.txt", "w");	// rocket1.txt에 write
		for (int i = 0; i <= rocket_lego_num; i++) {	// rocket_lego_num을 늘려가며 하나하나 저장
			fprintf(out, "%d, %d, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n",
				// 레고번호, type, color 는 %d로, 나머지 location과 rotation은 소숫점 둘째 자리까지 저장 (porque 0.1단위로 조정)
				i, rocket[i].get_lego_type(), rocket[i].get_lego_color(),
				rocket[i].get_lego_location_x(), rocket[i].get_lego_location_y(), rocket[i].get_lego_location_z(),
				rocket[i].get_lego_rotate_x(), rocket[i].get_lego_rotate_y(), rocket[i].get_lego_rotate_z());
		}
		fclose(out);
		break;
	case 2:	// save platform model
		printf("Save platform model has selected\n");
		fopen_s(&out, "platform1.txt", "w");	// platform1.txt에 write
		for (int i = 0; i <= platform_lego_num; i++) {	// platform_lego_num을 늘려가며 하나하나 저장
			fprintf(out, "%d, %d, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n",
				// 레고번호, type, color 는 %d로, 나머지 location과 rotation은 소숫점 둘째 자리까지 저장 (porque 0.1단위로 조정)
				i, platform[i].get_lego_type(), platform[i].get_lego_color(),
				platform[i].get_lego_location_x(), platform[i].get_lego_location_y(), platform[i].get_lego_location_z(),
				platform[i].get_lego_rotate_x(), platform[i].get_lego_rotate_y(), platform[i].get_lego_rotate_z());
		}
		fclose(out);
		break;
	case 3:	// load rocket model
		printf("Load rocket model has selected\n");
		fopen_s(&out, "rocket1.txt", "r"); // rocket1.txt을 read
		while (!feof(out)) {	// 파일이 끝날 때까지 
			fscanf_s(out, "%d, %d, %d, %f, %f, %f, %f, %f, %f \n",
				// 읽어올 때는 그냥 %f로 읽어야 함
				&rocket_lego_num, &type_select, &color_select,
				&g_loc_x, &g_loc_y, &g_loc_z, &g_Rot_x, &g_Rot_y, &g_Rot_z);

			rocket[rocket_lego_num].set_lego_color(color_select);
			rocket[rocket_lego_num].set_lego_type(type_select);
			rocket[rocket_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
			rocket[rocket_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z); // 읽은 정보들을 각 레고에 바로 set
		}
		fclose(out);
		break;
	case 4:	// load platform model
		printf("Load platform model has selected\n");
		fopen_s(&out, "platform1.txt", "r"); // launch_platform1.txt을 read
		while (!feof(out)) {	// 파일이 끝날 때까지 
			fscanf_s(out, "%d, %d, %d, %f, %f, %f, %f, %f, %f \n",
				// 읽어올 때는 그냥 %f로 읽어야 함
				&platform_lego_num, &type_select, &color_select,
				&g_loc_x, &g_loc_y, &g_loc_z, &g_Rot_x, &g_Rot_y, &g_Rot_z);

			platform[platform_lego_num].set_lego_color(color_select);
			platform[platform_lego_num].set_lego_type(type_select);
			platform[platform_lego_num].set_lego_rotate(g_Rot_x, g_Rot_y, g_Rot_z);
			platform[platform_lego_num].set_lego_location(g_loc_x, g_loc_y, g_loc_z); // 읽은 정보들을 각 레고에 바로 set
		}
		fclose(out);
		break;
	case 5:	// launch mode
		printf("launch mode has selected\n");
		glutChangeToMenuEntry(5, "design mode", 6); //5번째 메뉴가 case 6의 design이 된다
		Launchmode = 1;	// Launch mode에 들어갔다는 Flag
		type_select = 0; // 고정하지 않은 레고는 사라지게
		pre_view = 0; // preview를 끈다
		break;
	case 6:	// design mode
		printf("design mode has selected\n");
		glutChangeToMenuEntry(5, "launch mode", 5); //5번째 메뉴가 case 5의 Load 가 된다
		Launchmode = 0; // design mode에 들어감.
		component_checker = 0; 
		pre_view = 1; // preview를 다시 켜준다.
		break;

	case 9:	// clear lego
		if (!Launch) {
			printf("Clear lego\n");
			/* 레고의 개수를 모두 0으로 만들어준다. */
			platform_lego_num = 0;
			rocket_lego_num = 0;
			/*단순히 레고 개수를 0으로 만들어 주는 것으로는 현재 모드가 아닌 레고 모델의 첫번째 레고가 그려짐
			(ex. rocket design 모드일 시, platform의 첫번째 레고의 type이 남아 있어 그려지게 됨)
			따라서 모든 모델의 첫번째 레고의 타입을 초기화 해주어야 함.*/
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

/* string 그리는 함수 */
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
		/* 1개의 분출구가 있어 불꽃 색별로 1개 설정, 분출구의 위치를 그대로 받아 온다*/
		if (rocket[i].get_lego_type() == 9)
		{
			/* color 1 */
			set_flame(i, 1, 1, Rocket_flame, rocket);
			/* color 2 */
			set_flame(i, 2, 1, Rocket_flame, rocket);
			/* color 3 */
			set_flame(i, 3, 1, Rocket_flame, rocket);
		}
		/* 4개의 분출구가 있어 불꽃 색별로 4개 설정 */
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

/* flame의 초기 위치를 분출구의 위치를 통해 설정 */
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