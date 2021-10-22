#include "Vector2.h"
#include "Vector3Euler.h"
#include "Component.h"

using namespace std;

namespace DivisionCore
{
    class Transform : public Component
	{
	public:

        Transform() = default;

        Vectors::Vector2 position;
		Vectors::Vector3Euler rotation;
		Vectors::Vector2 scale;

		inline bool operator == (const Transform& other) const
		{
			return std::tie(position, rotation, scale) == std::tie(other.position, other.rotation, other.scale);
		}
		inline bool operator != (const Transform& other) const
		{
			return std::tie(position, rotation, scale) != std::tie(other.position, other.rotation, other.scale);
		}

	};
}