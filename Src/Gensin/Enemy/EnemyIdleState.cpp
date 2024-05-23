#include "../../../Including/Gensin/Enemy/EnemyIdleState.h"
#include "../../../Including/Gensin/Enemy/Enemy.h"


void EnemyIdleState::Update(GLFWwindow* window, float deltaTime)
{
	__super::Update(window, deltaTime);
	//std::cout << "IDLE" << std::endl;
	if (Timer < 0)
	{
		Timer = IdleTime;
		stateMachine->ChangeState(enemy->moveState);
	}
}
void EnemyIdleState::Enter()
{
	__super::Enter();
	Timer = IdleTime;
	enemy->zeroVelocity();
}