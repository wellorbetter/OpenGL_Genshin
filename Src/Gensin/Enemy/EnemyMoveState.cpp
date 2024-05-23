#include "../../../Including/Gensin/Enemy/EnemyMoveState.h"
#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Player/Player.h"

void EnemyMoveState::Update(GLFWwindow* window, float deltaTime)
{
	__super::Update(window, deltaTime);
	//std::cout << "Move" << std::endl;
	// 只需要直挺挺的往player脸上走就行了
	glm::vec3 newVelocity = enemy->getDirection() * enemy->getSpeed();
	enemy->setVelocity(newVelocity);
	glm::vec3 newPosition = enemy->getPosition() + newVelocity * deltaTime;
	enemy->setPosition(newPosition);
	//printf("%lf %lf %lf\n", newVelocity.x, newVelocity.y, newVelocity.z);
	// 如果很近了，就攻击
	if (glm::distance(enemy->getPosition(), enemy->player->getPosition()) < 0.2f)
	{
		stateMachine->ChangeState(enemy->attackState);
	}
}