#include "GameObject.h"

void gameObjUpdatePhysics(GameObject* obj, float dt) {
	Transform* transform = &(obj->transform);
	PhysicsObject* phys = &(obj->physics);


	// 1 - Update position
	vec3 deltaPos;
	mathVector3MultiplyScalar(dt, phys->velocity, deltaPos);
	mathVector3Add(deltaPos, transform->position, transform->position);

	// 2 - Update velocity
	float dv[3];
	mathVector3MultiplyScalar(dt, phys->acceleration, dv);
	mathVector3Add(dv, phys->velocity, phys->velocity);

	// Apply gravity
	phys->velocity[1] += phys->gravityFactor * -9.81 * dt;
}

void gameObjDrawModel(GameObject* obj) {
	Model* model = &(obj->model);
	Transform* tf = &(obj->transform);

	//
	// Apply transforms (pos,scale,rot)
	//
	glPushMatrix();

	glTranslatef(tf->position[0], tf->position[1], tf->position[2]);
	glScalef(tf->scale[0], tf->scale[1], tf->scale[2]);
	
	// Rotate around each axis.
	// Note: Yes, we could use quaternions, but more difficult to set up
	glRotatef(tf->rotationAngles[0], 1, 0, 0);
	glRotatef(tf->rotationAngles[1], 0, 1, 0);
	glRotatef(tf->rotationAngles[2], 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, model->textureID);

	// Load data arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, model->vertices);
	glNormalPointer(GL_FLOAT, 0, model->normals);
	glTexCoordPointer(2, GL_FLOAT, 0, model->textureCoords);

	glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

/*
* gameObjCreate
*
* Constructs a new game object with all the necessities.
* Loads a model from an OBJ file, and a BMP texture.
* Transform and physics defaults are loaded.
*/
GameObject gameObjCreate(char* modelPath, char* texturePath) {
	GameObject obj;
	
	Model model;
	objLoadModel(&model, modelPath);
	model.textureID = imgLoadBitmapToTexture(texturePath);

	Transform trans;
	transformSetDefaults(&trans);

	PhysicsObject physics;
	physObjSetDefaults(&physics);

	obj.model = model;
	obj.transform = trans;
	obj.physics = physics;
	
	return obj;
}

/*
// Old crappy version of gameObjCreate which requires some manual setup
GameObject* gameObjCreate(Model* model, Transform* transform, PhysicsObject* physics) {
	GameObject* obj = malloc(sizeof(GameObject));
	obj->model = *model;
	obj->transform = *transform;
	obj->physics = *physics;

	return obj;
}
*/