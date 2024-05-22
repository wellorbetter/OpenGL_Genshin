#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Player/Player.h"

void Enemy::Awake()
{
	modelPath = "Animation/WeirdQiuqiuren/";
	// ��ʼ��״̬��
	stateMachine = new EnemyStateMachine();
	// ��ʼ��״̬
	idleState = new EnemyIdleState(this, stateMachine, "Idle");
	moveState = new EnemyMoveState(this, stateMachine, "Move");
	attackState = new EnemyAttackState(this, stateMachine, "Attack");
}

void Enemy::Start()
{
	// ��ǰ��λ�õ�Ȼ���ܺ�player�غ�
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