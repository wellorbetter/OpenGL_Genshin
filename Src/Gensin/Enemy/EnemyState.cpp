#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Enemy/EnemyState.h"
#include "../../../Including/Gensin/Enemy/EnemyStateMachine.h"


EnemyState::EnemyState(Enemy* _enemy, EnemyStateMachine* _stateMachine, std::string _stateName)
{
	enemy = _enemy;
	stateMachine = _stateMachine;
	stateName = _stateName;
}

void EnemyState::Update(GLFWwindow* window, float deltaTime)
{
	// 额，Player里面好像没有这么写，实际上这种写法才是对的
	this->Timer -= deltaTime;
}

void EnemyState::Enter()
{
	enemy->setAnimation(this->stateName, true);
}

void EnemyState::Exit()
{
	enemy->setAnimation(this->stateName, false);
}