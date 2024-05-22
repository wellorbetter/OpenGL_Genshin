#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Player/Player.h"

void Enemy::Awake()
{
	modelPath = "Animation/WeirdQiuqiuren/";
	// 初始化状态机
	stateMachine = new EnemyStateMachine();
	// 初始化状态
	idleState = new EnemyIdleState(this, stateMachine, "Idle");
	moveState = new EnemyMoveState(this, stateMachine, "Move");
	attackState = new EnemyAttackState(this, stateMachine, "Attack");
}

void Enemy::Start()
{
	// 当前的位置当然不能和player重合
	this->position = glm::vec3(2.0f, 0.0f, 2.0f);
	stateMachine->InitialState(this->idleState);
}

void Enemy::Update(GLFWwindow* window, float deltaTime)
{
	stateMachine->currentState->Update(window, deltaTime);
}

void Enemy::Damage()
{
	__super::Damage();
}

Enemy::Enemy(Player* _player)
{
	this->player = _player;
}