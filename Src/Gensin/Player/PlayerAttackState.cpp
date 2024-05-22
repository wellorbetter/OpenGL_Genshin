#include "../../../Including/Gensin/Player/PlayerAttackState.h"
#include "../../../Including/Gensin/Player/Player.h"

void PlayerAttackState::Enter()
{
	__super::Enter();
	// 攻击可以到处跑 不用zero速度
	// 进去之后直接发出一个子弹 然后发到鼠标左键的位置上去
	// 也就是当前第一人称对应的Front方向
	Camera* camera = player->cinemachine->virtualCameras[1].camera;
	// 加一个音效 这里
	delayTimer = delayTime;
	std::cout << "Attack" << std::endl;
	player->fireBullet(10);
	// 然后这个攻击要有cd，而且得有后摇，让动画放完
}

void PlayerAttackState::Update(GLFWwindow* window)
{
	// 检查输入
	// 按下wasd或者方向键 就表示移动了
	__super::Update(window);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		stateMachine->ChangeState(player->jumpState);
	}

	// 在移动
	if (this->getMoveDirection(window) != MoveDirection::NONE)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // 没有移动
	else
	{
		player->isMoving = false;
		stateMachine->ChangeState(player->idleState);
	}
}


void PlayerAttackState::Update(GLFWwindow* window, float deltaTime)
{
	// 左键
	// 后摇
	delayTimer -= deltaTime;
	std::cout << "正在后摇" << std::endl;
	if (delayTimer >= 0) return;

	attackCDTimer -= deltaTime;
	std::cout << "正在CD" << std::endl;
	if (attackCDTimer < 0 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		attackCDTimer = attackCDTime;
		stateMachine->ChangeState(player->attackState);
	}
	this->Update(window);
}