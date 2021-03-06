#include "GameObject.h"

/*
* gameObjUpdatePhysics
*
* Updates the position, velocity & acceleration of a given object.
* Collisions are not considered here. dt determines magnitude of calculations.
*/
void gameObjUpdatePhysics(GameObject* obj, float dt) {
	Transform* transform = &(obj->transform);
	PhysicsObject* phys = &(obj->physics);

	vec3 deltaPos;
	float dv[3];

	if (!phys->isKinetic) return;

	// 1 - Update position
	mathVector3MultiplyScalar(dt, phys->velocity, deltaPos);
	mathVector3Add(deltaPos, transform->position, transform->position);

	// Cheap workaround for debugging until collisions work?
	if (transform->position[1] < 0) {
		transform->position[1] = 0;
		phys->velocity[1] = 0;
	}

	// 2 - Update velocity	
	mathVector3MultiplyScalar(dt, phys->acceleration, dv);
	mathVector3Add(dv, phys->velocity, phys->velocity);

	// 3 - Apply gravity
	phys->velocity[1] += phys->gravityFactor * -9.81f * dt;

	// 4 - Apply friction (subtract from acceleration)
	// A) Make sure to apply friction opposite to the direction of acceleration.
	// B) Make sure not to get a negative velocity by applying friction. Only if object is moving.

	// Apply friction if on ground. Currently with fixed coefficient
	if (transform->position[1] == 0) {
		mathVector3MultiplyScalar(1 - (0.55*dt), phys->velocity, phys->velocity);
	}

}

/*
* gameObjDrawModel
*
* Draws the model of a GameObject on screen.
* A model and texture must have already been loaded.
*/
void gameObjDrawModel(GameObject* obj) {
	Model* model = &(obj->model);
	Transform* tf = &(obj->transform);

	if (model == NULL) return;

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
GameObject* gameObjCreate(char* modelPath, char* texturePath) {
	GameObject* obj;
	Transform trans;
	PhysicsObject physics;
	Model model;
	BoundingBox bbox;

	obj = malloc(sizeof(GameObject));
	
	objLoadModel(&model, modelPath);
	model.textureID = imgLoadBitmapToTexture(texturePath);

	if (&model != NULL){
		bboxCalculateFromModel(&bbox, &model); // Calculate bounding box
	}

	transformSetDefaults(&trans);

	physObjSetDefaults(&physics);

	obj->model = model;
	obj->transform = trans;
	obj->physics = physics;
	obj->bbox = bbox;
	
	return obj;
}

void gameObjScale(GameObject* obj, float scaleX, float scaleY, float scaleZ) {
	obj->transform.scale[0] = obj->transform.scale[0] * scaleX;
	obj->transform.scale[1] = obj->transform.scale[1] * scaleY;
	obj->transform.scale[2] = obj->transform.scale[2] * scaleZ;

	bboxScale(&(obj->bbox), scaleX, scaleY, scaleZ);


}
