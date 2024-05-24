#include "../../../Including/Gensin/GameObject/GameObject.h"


bool Collider::collisionCheck(Collider* other)
{
	if (leftDown.x < other->rightUp.x && rightUp.x > other->leftDown.x && leftDown.z < other->rightUp.z && rightUp.z > other->leftDown.z)
	{
		return true;
	}
	return false;
}

