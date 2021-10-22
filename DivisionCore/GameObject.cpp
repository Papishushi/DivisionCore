#include "Component.h"
#include "GameObject.h"


#include <list>

using namespace std;

namespace DivisionCore
{
    GameObject::GameObject() {
        name = "GameObject" + to_string(GetInstanceID());
        hideFlags = HideFlags::VISIBLE;
        attachedComponents = list<Component>();
        instancedGameObjects = list<GameObject>();
        isActive = true;

        isStatic = false;
        activeInHierarchy = true;
        layer = 0;
        scene = 0;
        sceneCullingMask = 0;
        tag = nullptr;
        transform = Transform();
    }
}