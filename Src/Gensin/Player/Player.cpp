#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// ��ʼ������ setAnimֱ����
	// ����ĳЩ״̬ ���ض���
	
	Animator::Init();
	this->stateMachine = new PlayerStateMachine();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->moveState = new PlayerMoveState(this, this->stateMachine, "Move");
}

void Player::Start()
{
	// ��ʼ����״̬��Ⱦ
	this->stateMachine->InitialState(this->idleState);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	// �˳���Ϸ
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		cinemachine->SwitchCamera(); // �л����
	stateMachine->currentState->Update(window);
}

void Player::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);

	// ������ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cinemachine->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cinemachine->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cinemachine->ProcessKeyboard(RIGHT, deltaTime);

	// ״̬�ĸ���
	stateMachine->currentState->Update(window);
}

Player::Player(Cinemachine* _cinemachine)
{
	this->cinemachine = _cinemachine;
	// �õ�����ĵ�һ�˳Ƶ�λ�� �Լ�����
	this->setPosition(this->cinemachine->virtualCameras[1].camera->Position);
	this->setDirection(this->cinemachine->virtualCameras[1].camera->Front);
}