#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// 初始化动画 setAnim直接拿
	// 创建某些状态 加载东西
	
	Animator::Init();
	this->stateMachine = new PlayerStateMachine();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->moveState = new PlayerMoveState(this, this->stateMachine, "Move");
}

void Player::Start()
{
	// 开始进入状态渲染
	this->stateMachine->InitialState(this->idleState);
	// 设定移动速度
	glm::vec3 speed = glm::vec3(2.0f, 2.0f, 2.0f);
	this->setSpeed(speed);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	// 退出游戏
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		cinemachine->SwitchCamera(); // 切换相机
	stateMachine->currentState->Update(window);
}

void Player::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);

	// 相机的移动 只有上帝视角可以移动
	if (this->cinemachine->activeCameraIndex == 2)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(RIGHT, deltaTime);
	}

	// 状态的更新
	stateMachine->currentState->Update(window);

	// 位置的更新 这里不用 * this->getDirection() 因为速度包括了方向，之前乘过了
	glm::vec3 newPosition = deltaTime * this->getVelocity() + this->getPosition();
	this->setPosition(newPosition);
}

Player::Player(Cinemachine* _cinemachine):Entity()
{
	this->cinemachine = _cinemachine;
	// 拿到相机的第一人称的位置 以及朝向
	this->setPosition(this->cinemachine->virtualCameras[1].camera->Position);
	this->setDirection(this->cinemachine->virtualCameras[1].camera->Front);
}