#include "Includes.h"

void drawHouse(GLfloat x, GLfloat y, GLfloat z, GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLuint houseTexID, GLuint roofTexID) {
	vec3 verts[] = {
		// Front
		{ -0.5, 0, -0.5 },
		{ 0.5, 0, -0.5 },
		{ 0.5, 1, -0.5 },
		{ -0.5, 1, -0.5 },
		// Back
		{ -0.5, 0, 0.5 },
		{ 0.5, 0, 0.5 },
		{ 0.5, 1, 0.5 },
		{ -0.5, 1, 0.5 },
		// Left
		{-0.5, 0, -0.5},
		{ -0.5, 0, 0.5 },
		{ -0.5, 1, 0.5 },
		{ -0.5, 1, -0.5 },
		// Right
		{ 0.5, 1, -0.5 },
		{ 0.5, 1, 0.5 },
		{ 0.5, 0, 0.5 },
		{ 0.5, 0, -0.5 },
	};

	vec2 uv[16] = {
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 }
	};

	vec3 vertsRoof[] = {
		// Front
		{ -0.5, 1, 0.5 },
		{ 0.5, 1, 0.5 },
		{ 0.4, 1.2, 0 },
		{ -0.4, 1.2, 0 },
		// Back
		{ -0., 1, -0.5 },
		{ 0.5, 1, -0.5 },
		{ 0.4, 1.2, 0 },
		{ -0.4, 1.2, 0 },
		// Left side
		{ -0.5, 1, -0.5 },
		{ -0.5, 1, 0.5 },
		{ -0.4, 1.2, 0 },
		// Right side
		{ -0.4, 1.2, 0 },
		{ -0.5, 1, 0.5 },
		{ -0.5, 1, -0.5 },
	};

	vec2 uvRoof[] = {
		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },

		{ 0, 0 },
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },

		{ 0, 0 },
		{ 1, 0 },
		{ 0.5, 1 },

		{ 0, 0 },
		{ 1, 0 },
		{ 0.5, 1 },
	};

	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(scaleX, scaleY, scaleZ);

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//
	// House box
	//
	glBindTexture(GL_TEXTURE_2D, houseTexID);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glTexCoordPointer(2, GL_FLOAT, 0, uv);

	glDrawArrays(GL_QUADS, 0, 16);	// Count = number of verts!



	//
	// Roof
	//

	glBindTexture(GL_TEXTURE_2D, roofTexID);

	glColor3f(0.75, 0.75, 0.75);
	glVertexPointer(3, GL_FLOAT, 0, vertsRoof);
	glTexCoordPointer(2, GL_FLOAT, 0, uvRoof);

	glDrawArrays(GL_QUADS, 0, 8);
	glDrawArrays(GL_POLYGON, 8, 6);

	//
	// Cleanup
	//
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void drawGround(GLuint textureID) {
	vec3 verts[4] = {
		{ -250, 0, 0 },
		{ 250, 0, 0 },
		{250, 0, -250},
		{ -250, 0, -250}
	};

	vec2 uv[4] = {
		{ 0, 0 },
		{ 250, 0 },
		{ 250, 250},
		{ 0, 250 }
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glTexCoordPointer(2, GL_FLOAT, 0, uv);

	glDrawArrays(GL_QUADS, 0, 4);	// Count = number of verts!

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}
