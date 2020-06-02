#include <gl/glut.h>
#include <gl/glext.h>
using namespace std;
#include "ObjParser.h"
/* lego */
ObjParser* Lego_1, * Lego_2, * Lego_3, * Lego_4, * Lego_5, * Lego_6, * Lego_7, * Lego_8, * Lego_9, * Lego_10, * Lego_11, * Lego_12, *big_flame, *small_flame;

void draw_obj(ObjParser* objParser);	// 오브젝트를 실제로 그리는 함수

class LEGO {
private:
	float loc_x, loc_y, loc_z;
	float Rot_x, Rot_y, Rot_z;
	int color;
	int type;
public:
	LEGO()
	{
		loc_x = 0.0;
		loc_y = 0.0;
		loc_z = 0.0;
		Rot_x = 0.0;
		Rot_y = 0.0;
		Rot_z = 0.0;
		color = 0;
		type = 0;
	}

	~LEGO() {};

	void LEGO_color_select(int c)
	{
		switch (c) {
		case 1:
			glColor3f(1.0f, 1.0f, 1.0f); // White 
			break;
		case 2:
			glColor3f(0.117647f, 0.564706f, 1.0f); // blue
			break;
		case 3:
			glColor3f(0.133333f, 0.545098f, 0.133333f); // Green
			break;
		case 4:
			glColor3f(0.580392f, 0.0f, 0.827451f); // Purple
			break;
		case 5:
			glColor3f(0.85f, 0.0f, 0.0f);  // Red
			break;
		case 6:
			glColor3f(0.2f, 0.8f, 1.0f);  // Sky
			break;
		case 7:
			glColor3f(1.0f, 0.270588f, 0.0f);   // Orange
			break;
		case 8:
			glColor3f(1.0f, 0.311765f, 0.605882f); // Pink
			break;
		case 9:
			glColor3f(0.1f, 0.1f, 0.1f); // Black
			break;
		}
	}

	void set_lego_color(int c)
	{
		color = c;
	}
	int get_lego_color()
	{
		return color;
	}

	void LEGO_draw_con_type(int t)
	{
		switch (t) {
		case 1:
			draw_obj(Lego_1);
			break;
		case 2:
			draw_obj(Lego_2);
			break;
		case 3:
			draw_obj(Lego_3);
			break;
		case 4:
			draw_obj(Lego_4);
			break;
		case 5:
			draw_obj(Lego_5);
			break;
		case 6:
			draw_obj(Lego_6);
			break;
		case 7:
			draw_obj(Lego_7);
			break;
		case 8:
			draw_obj(Lego_8);
			break;
		case 9:
			draw_obj(Lego_9);
			break;
		case 10:
			draw_obj(Lego_10);
			break;
		case 11:
			draw_obj(Lego_11);
			break;
		case 12:
			draw_obj(Lego_12);
			break;
		}
	}

	void set_lego_type(int t)
	{
		type = t;
	}
	int get_lego_type()
	{
		return type;
	}
	void set_lego_rotate(float x, float y, float z)
	{
		Rot_x = x;
		Rot_y = y;
		Rot_z = z;
	}
	float get_lego_rotate_x()
	{
		return Rot_x;
	}
	float get_lego_rotate_y()
	{
		return Rot_y;
	}
	float get_lego_rotate_z()
	{
		return Rot_z;
	}
	void get_lego_rotated()
	{
		//rotate on x axis
		glRotatef(Rot_x, 1.0, 0.0, 0.0);

		//rotate on y axis
		glRotatef(Rot_y, 0.0, 1.0, 0.0);

		//rotate on z axis
		glRotatef(Rot_z, 0.0, 0.0, 1.0);
	}
	void set_lego_location(float x, float y, float z)
	{
		loc_x = x;
		loc_y = y;
		loc_z = z;
	}
	float get_lego_location_x()
	{
		return loc_x;
	}
	float get_lego_location_y()
	{
		return loc_y;
	}
	float get_lego_location_z()
	{
		return loc_z;
	}
	void get_lego_translated()
	{
		glTranslatef(loc_x, loc_y, loc_z);
	}

	void draw_lego()
	{
		LEGO_color_select(color);
		get_lego_translated();
		get_lego_rotated();
		LEGO_draw_con_type(type);
	}
};


class Flame {
private:
	float loc_x, loc_y, loc_z;
	float Rot_x, Rot_y, Rot_z;
	int color;
	int type;

public:
	void flame_color_select(int c)
	{
		switch (c) {
		case 1:
			glColor3f(0.886f, 0.345f, 0.133f);
			break;
		case 2:
			glColor3f(0.886f, 0.157f, 0.133f);
			break;
		case 3:
			glColor3f(1.0f, 0.831f, 0.0f);
			break;
		}
	}

	void set_flame_color(int c)
	{
		color = c;
	}
	int get_flame_color()
	{
		return color;
	}

	void flame_draw_con_type(int t)
	{
		switch (t) {
		case 1:
			draw_obj(big_flame);
			break;
		case 2:
			draw_obj(small_flame);
			break;
		}
	}

	void set_flame_type(int t)
	{
		type = t;
	}
	int get_flame_type()
	{
		return type;
	}
	void set_flame_rotate(float x, float y, float z)
	{
		Rot_x = x;
		Rot_y = y;
		Rot_z = z;
	}
	float get_flame_rotate_x()
	{
		return Rot_x;
	}
	float get_flame_rotate_y()
	{
		return Rot_y;
	}
	float get_flame_rotate_z()
	{
		return Rot_z;
	}
	void get_flame_rotated()
	{
		//rotate on x axis
		glRotatef(Rot_x, 1.0, 0.0, 0.0);

		//rotate on y axis
		glRotatef(Rot_y, 0.0, 1.0, 0.0);

		//rotate on z axis
		glRotatef(Rot_z, 0.0, 0.0, 1.0);
	}
	void set_flame_location(float x, float y, float z)
	{
		loc_x = x;
		loc_y = y;
		loc_z = z;
	}
	float get_flame_location_x()
	{
		return loc_x;
	}
	float get_flame_location_y()
	{
		return loc_y;
	}
	float get_flame_location_z()
	{
		return loc_z;
	}
	void get_flame_translated()
	{
		glTranslatef(loc_x, loc_y, loc_z);
	}

	void draw_flame()
	{
		flame_color_select(color);
		get_flame_translated();
		get_flame_rotated();
		flame_draw_con_type(type);
	}
};

void draw_obj(ObjParser* objParser) {
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
