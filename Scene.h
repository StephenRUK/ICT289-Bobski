#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

typedef struct SceneItem {
	GameObject* obj;
	struct SceneItem* next;		// Must be referred to as struct here
} SceneItem;

typedef struct SceneList {
	SceneItem* first;
	SceneItem* last;

} SceneList;


void sceneAddItem(SceneList* list, GameObject* obj);

#endif