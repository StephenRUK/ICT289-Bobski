#include "Scene.h"

/**
*	Scene contains all game objects, stored in a linked list.
**/

void sceneAddItem(SceneList* list, GameObject* obj) {
	SceneItem* newItem = malloc(sizeof(SceneItem));
	newItem->obj = obj;
	newItem->next = NULL;

	if (list->first == NULL) {
		list->first = newItem;
	} else {
		list->last->next = newItem;
	}

	list->last = newItem;
}
