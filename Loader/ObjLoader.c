#include "ObjLoader.h"
#include <stdio.h>
#include <stdlib.h>

/**
* OBJ File Loader
*
* References:
*	- OpenGL index specification
*		https://www.opengl.org/wiki/FAQ#Multi_indexed_rendering
*	- OBJ Format specification
*		http://en.wikipedia.org/wiki/Wavefront_.obj_file#Face_Elements
**/
void objLoadModel(Model* model, char* filePath, int elementSize) {

	FILE* objFile;
	objFile = fopen(filePath, "r");

	int vertexCount = 0, normalCount = 0, texCoordCount = 0, elementCount = 0;

	char buf[256];
	char entryType[2];

	//
	// Count number of verts etc.
	//

	while (fgets(buf, sizeof(buf), objFile)) {
		
		// Determine type of entry (vertex, normal, tex coord, element)
		strncpy(entryType, buf, 2);

		if (entryType[0] == 'v' && entryType[1] == ' ') {	// Vertex
			vertexCount++;
		} else if (entryType[0] == 'v' && entryType[1] == 'n') {	// Normal
			normalCount++;
		} else if (entryType[0] == 'v' && entryType[1] == 't'){		// Texture Coordinate
			texCoordCount++;
		} else if (entryType[0] == 'f' && entryType[1] == ' ') {	// Element (face)
			elementCount++;
		}
	}

	//
	// Allocate memory for buffers
	//

	model->vertexCount = vertexCount;
	model->vertices = malloc(vertexCount * 3 * sizeof(GLfloat));

	model->normalCount = normalCount;
	model->normals = malloc(normalCount * 3 * sizeof(GLfloat));

	model->texCoordCount = texCoordCount;
	model->textureCoords = malloc(texCoordCount * 3 * sizeof(GLfloat));

	model->indexCount = elementCount;
	model->indices = malloc(elementCount * 3 * elementSize * sizeof(int));

	//
	// Read in values to buffers
	//
	rewind(objFile);

	int vertexIndex = 0, normalIndex = 0, texCoordIndex = 0, elementIndex = 0;

	char* lineVals;
	char* coordDelimiter = " ";
	char* elimDelimiter = "/";

	while (fgets(buf, sizeof(buf), objFile)) {
		lineVals = strtok(buf, coordDelimiter);	// Line split into values. 0: type, 1/2/3: x/y/z

		if (lineVals[0] == "v") {	// Vertex
			model->vertices[vertexIndex] = strtof(lineVals[1], NULL);
			model->vertices[vertexIndex+1] = strtof(lineVals[2], NULL);
			model->vertices[vertexIndex+2] = strtof(lineVals[3], NULL);
			vertexIndex += 3;

		} else if (lineVals[0] == "vn") {	// Normal
			model->normals[normalIndex] = strtof(lineVals[1], NULL);
			model->normals[normalIndex + 1] = strtof(lineVals[2], NULL);
			model->normals[normalIndex + 2] = strtof(lineVals[3], NULL);
			normalIndex += 3;
			
		} else if (lineVals[0] == "vt"){	// Texture Coordinate
			model->textureCoords[texCoordIndex] = strtof(lineVals[1], NULL);
			model->textureCoords[texCoordIndex + 1] = strtof(lineVals[2], NULL);
			texCoordIndex += 3;

		} else if (lineVals[0] == "f") {	// Element (face)
			// Syntax: f vertex/texturecoordinate/normal
			// Example, polygon: f 1/1/1 2/2/1 3/3/1 4/4/1 
			// Indices are 1-based. Must be converted to 0-based for OpenGL.

			int i;
			for (i = 0; i < elementCount; i++) {
				// Split each value at slashes
				char* valString = lineVals[i + 1];	// vert/texcoord/normal
				char* vals = strtok(valString, elimDelimiter);	// Split into ints

				int i;
				for (i = 0; vals[i] != NULL; i++) {
					model->indices[elementIndex] = atoi(vals[0]);
					elementIndex++;
				}
			}
		}
	} // Finished storing values

	//
	// TODO Input needs to be prepared for OpenGL. Number of verts,normals and texture coords must be the same.
	//

	fclose(objFile);

	if (ferror(stdin)) {
		fprintf(stderr, "File could not be read: %s\n", filePath);
	}

}