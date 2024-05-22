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
	this->jumpState = new PlayerJumpState(this, this->stateMachine, "Jump");
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

	stateMachine->currentState->Update(window);
}

void Player::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);
	this->cinemachine->switchTimer -= deltaTime;
	// 相机的移动 只有上帝视角可以移动

	// 这里有问题的，因为每次的update非常非常短，这里的deltaTime是一个很小的数
	// 所以可能我按下了c键但是update已经执行了好几次了
	// 所以切换相机需要一个内置时间 比如1秒

	// 切换相机
	if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) && this->cinemachine->switchTimer < 0)
	{
		cinemachine->SwitchCamera();
		this->cinemachine->switchTimer = this->cinemachine->switchTime;
	}
	// 如果是上帝视角角色不准动
	if (this->cinemachine->activeCameraIndex == 2)
	{
		stateMachine->ChangeState(this->idleState);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(RIGHT, deltaTime);
		// 同时不准进行更新
		//printf("%lf %lf %lf\n", this->getDirection().x, this->getDirection().y, this->getDirection().z);
		return;
	}

	// 状态的更新
	stateMachine->currentState->Update(window, deltaTime);
}

Player::Player(Cinemachine* _cinemachine):Entity()
{
	this->cinemachine = _cinemachine;
	// 拿到相机的第一人称的位置 以及朝向
	this->setPosition(this->cinemachine->virtualCameras[1].camera->Position);
	this->setDirection(this->cinemachine->virtualCameras[1].camera->Front);
}