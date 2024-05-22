#include "../../../Including/Gensin/GameObject/GameObject.h"


bool Collider::collisionCheck(Collider* other)
{
	if (leftDown.x < other->rightUp.x && rightUp.x > other->leftDown.x && leftDown.y < other->rightUp.y && rightUp.y > other->leftDown.y)
	{
		return true;
	}
	return false;
}

