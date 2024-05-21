#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"


void PlayerIdleState::Enter()
{
	__super::Enter();
	// 闲置状态没有速度
	player->zeroVelocity();
}

void PlayerIdleState::Update(GLFWwindow* window)
{
	// 检查输入
	// 按下wasd或者方向键 就表示移动了
	__super::Update(window);

	// 感觉可以抽象出一个Input了.... 好麻烦
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
	
}

void PlayerIdleState::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);
}