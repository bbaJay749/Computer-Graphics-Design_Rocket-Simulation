#include <stdio.h>
#include <gl/glut.h>

bool Antialiasing = false;

void func_Antialiasing(unsigned char key)
{
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
}
