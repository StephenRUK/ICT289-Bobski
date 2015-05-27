#include "ObjLoader.h"
#include <stdio.h>
#include <stdlib.h>

/**
* OBJ File Loader
*
* Parameters:
* - model		Pointer to model to load data into
* - filePath	OBJ file path
* - elementSize	Number of entries in an OBJ element, i.e. 3 for triangles, 4 for quads.
*
* References:
*	- OpenGL index specification
*		https://www.opengl.org/wiki/FAQ#Multi_indexed_rendering
*	- OBJ Format specification
*		http://en.wikipedia.org/wiki/Wavefront_.obj_file#Face_Elements
**/
void objLoadModel(Model* model, char* filePath) {
	
	const int elementSize = 3;	// Size of elements in OBJ file. We use triangles!

	FILE* objFile;
	objFile = fopen(filePath, "r");

	if (ferror(stdin)) {
		fprintf(stderr, "File could not be read: %s\n", filePath);
		return;
	}

	int vertexCount = 0, normalCount = 0, texCoordCount = 0, elementCount = 0;
	int preparedVertCount = 0;	// Stores number of vertices after data preparation. Not number of verts in OBJ file.

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

	vertex3* tempVertices = malloc(vertexCount * sizeof(vertex3));
	vertex3* tempNormals = malloc(normalCount * sizeof(vertex3));
	vertex2* tempTexCoords = malloc(texCoordCount * sizeof(vertex2));
	int* tempIndices = malloc(elementCount * 3 * elementSize * sizeof(int));	// *3 for vertex/texturecoordinate/normal

	//
	// Read in values to buffers
	//
	rewind(objFile);

	int vertexIndex = 0, normalIndex = 0, texCoordIndex = 0, elementIndex = 0;

	char* lineVals;
	char* coordDelimiter = " ";
	char* elimDelimiter = "/";

	while (fgets(buf, sizeof(buf), objFile)) {
		lineVals = strtok(buf, coordDelimiter);	// Get tokens delimited by spaces, beginning with the type (v/vn/vt/f)

		if (lineVals[0] == 'v' && lineVals[1] == '\0') {	// Vertex

			lineVals = strtok(NULL, coordDelimiter);	// Fetch first value
			int dimension = 0;	// Choose X, Y, Z of the vertex
			while (lineVals != NULL) {
				tempVertices[vertexIndex][dimension] = strtof(lineVals, NULL);
				dimension++;
				lineVals = strtok(NULL, coordDelimiter);	// Fetch next value
			}
			vertexIndex++;

		} else if (lineVals[0] == 'v' && lineVals[1] == 'n') {	// Normal

			lineVals = strtok(NULL, coordDelimiter);	// Fetch first value
			int dimension = 0;	// Choose X, Y, Z of the normal
			while (lineVals != NULL) {
				tempNormals[normalIndex][dimension] = strtof(lineVals, NULL);
				dimension++;
				lineVals = strtok(NULL, coordDelimiter);	// Fetch next value
			}
			normalIndex++;

		} else if (lineVals[0] == 'v' && lineVals[1] == 't') {	// Texture Coordinate

			lineVals = strtok(NULL, coordDelimiter);	// Fetch 'U' value
			tempTexCoords[texCoordIndex][0] = strtof(lineVals, NULL);

			lineVals = strtok(NULL, coordDelimiter);	// Fetch 'V' value
			tempTexCoords[texCoordIndex][1] = strtof(lineVals, NULL);

			texCoordIndex++;

		} else if (lineVals[0] == 'f') {	// Element (face)
			// Syntax: f vertex/texturecoordinate/normal
			// Example, polygon: f 1/1/1 2/2/1 3/3/1 4/4/1 
			
			char* vertEntry;	// Points to string segment of current entry (e.g. "1/4/6")
			char entryBuf[32];	// Temporarily store entries here, as strtok modifies original string.
			char* tokenPointer; // Needed for nested strtok - stores internal contex for strtok_s

			lineVals = strtok(NULL, coordDelimiter);	// Fetch first entry
			while (lineVals != NULL && lineVals[0] != '\n') {
				strcpy(entryBuf, lineVals);

				vertEntry = strtok_s(entryBuf, elimDelimiter, &tokenPointer);	// Fetch first value from entry (i.e. the vertex ID)
				while (vertEntry != NULL && vertEntry[0] != '\n') {
					tempIndices[elementIndex] = atoi(vertEntry) - 1;	// Indices are 1-based. Must be converted to 0-based.
					elementIndex++;

					vertEntry = strtok_s(NULL, elimDelimiter, &tokenPointer);	// Fetch next value from entry
				}

				preparedVertCount++;
				lineVals = strtok(NULL, coordDelimiter);	// Fetch next entry
			}

		}

	} // Finished storing values

	// Assertions:
	// elementIndex-1 = 3 * elementSize * elementCount
	// 

	//
	// Allocate memory to store prepared data in model
	//
	model->vertexCount = preparedVertCount;

	model->vertices = malloc(preparedVertCount * sizeof(vertex3));
	model->normals = malloc(preparedVertCount * sizeof(vertex3));
	model->textureCoords = malloc(preparedVertCount * sizeof(vertex2));

	//
	// Prepare data for OpenGL. Number of verts,normals and texture coords must be the same, with matching indices for each attribute.
	//

	// Loop element indices

	int j;
	for (j = 0; j < preparedVertCount; j++) {
		// Get 3 indices at a time. Order is important!
		int vertexIndex = tempIndices[3*j];
		int texCoordIndex = tempIndices[3 * j + 1];
		int normalIndex = tempIndices[3 * j + 2];

		memcpy(&(model->vertices[j]), &(tempVertices[vertexIndex]), sizeof(vertex3));
		memcpy(&(model->textureCoords[j]), &(tempTexCoords[texCoordIndex]), sizeof(vertex2));
		memcpy(&(model->normals[j]), &(tempNormals[normalIndex]), sizeof(vertex3));

	}
	

	//
	// Cleanup
	//

	free(tempVertices);
	free(tempNormals);
	free(tempTexCoords);
	free(tempIndices);

	fclose(objFile);

}