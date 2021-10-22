#include "Object.h"

#include <memory>
#include <string>

using namespace std;

class Transform
{
public:
    Transform() = default;
};
class GameObject
{
public:
    string tag;
    Transform * transform;

    GameObject() {tag = nullptr; transform = new Transform();}

    inline bool CompareTag(const string& _tag) const{
        return tag == _tag;
    }

    template <typename T> bool TryGetComponent(T& outComponent);
    template <typename T> T GetComponent();
    template <typename T> T GetComponentInChildren();
    template <typename T> T GetComponentInParent();
    template <typename T> T* GetComponents();
    template <typename T> T* GetComponentsInChildren();
    template <typename T> T* GetComponentsInParent();
};


namespace DivisionCore
{
	class Component : public Object<Component> {
	public:
        GameObject * gameObject;
        string tag;

        Component();
        explicit Component(GameObject* parent);

		inline Transform * transform() const {
            if (gameObject != nullptr)
            {
                if (gameObject->transform != nullptr) {
                    return gameObject->transform;
                }
            }
            return nullptr;
		}

		inline bool CompareTag(const string& _tag) const
		{
			return gameObject->CompareTag(_tag);
		}

		void SendMessageLocal(const void* Method);
		void SendMessageChildren(const void* Method);
		void SendMessageParent(const void* Method);

		template <typename T> bool TryGetComponent(T& outComponent)
		{
			return gameObject->TryGetComponent(outComponent);
		}

		template <typename T> T GetComponent()
		{
			return gameObject->GetComponent<T>();
		}
		template <typename T> T GetComponentInChildren()
		{
			return gameObject->GetComponentInChildren<T>();
		}
		template <typename T> T GetComponentInParent()
		{
			return gameObject->GetComponentInParent<T>();
		}
		template <typename T> T* GetComponents()
		{
			return gameObject->GetComponents<T>();
		}
		template <typename T> T* GetComponentsInChildren()
		{
			return gameObject->GetComponentsInChildren<T>();
		}
		template <typename T> T* GetComponentsInParent()
		{
			return gameObject->GetComponentsInParent<T>();
		}
	};
}