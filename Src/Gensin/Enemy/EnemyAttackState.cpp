#include "../../../Including/Gensin/Enemy/EnemyAttackState.h"
#include "../../../Including/Gensin/Enemy/Enemy.h"

void EnemyAttackState::Enter()
{
	__super::Enter();
	isDelaying = true;
	isCoolDown = false;
	Timer = delayTime;
}

void EnemyAttackState::Update(GLFWwindow* window, float deltaTime)
{
	__super::Update(window, deltaTime);
	//std::cout << "Attack" << std::endl;
	if (isDelaying && Timer < 0)
	{
		isDelaying = false;
		isCoolDown = true;
		Timer = coolDown;
	}
	if (isCoolDown && Timer < 0)
	{
		isCoolDown = false;
		Timer = delayTime;
		stateMachine->ChangeState(enemy->idleState);
	}
}