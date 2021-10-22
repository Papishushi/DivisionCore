#include "Component.h"

namespace DivisionCore
{
    Component::Component() {
        gameObject = new GameObject();
    }
    Component::Component(GameObject * parent) {
        gameObject = parent;
    }
}