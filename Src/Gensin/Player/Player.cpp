#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// 初始化动画 setAnim直接拿
	// 创建某些状态 加载东西
	
	Animator::Init();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->stateMachine = new PlayerStateMachine();
}

void Player::Start()
{
	// 开始进入状态渲染
	this->stateMachine->InitialState(this->idleState);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	stateMachine->currentState->Update(window);
}