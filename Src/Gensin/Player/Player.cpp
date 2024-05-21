#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// ��ʼ������ setAnimֱ����
	// ����ĳЩ״̬ ���ض���
	
	Animator::Init();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->stateMachine = new PlayerStateMachine();
}

void Player::Start()
{
	// ��ʼ����״̬��Ⱦ
	this->stateMachine->InitialState(this->idleState);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	stateMachine->currentState->Update(window);
}