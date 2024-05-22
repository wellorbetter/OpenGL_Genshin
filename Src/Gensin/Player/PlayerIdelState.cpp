#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"


void PlayerIdleState::Enter()
{
	__super::Enter();
	// ����״̬û���ٶ�
	player->zeroVelocity();
}

void PlayerIdleState::Update(GLFWwindow* window)
{
	// �������
	// ����wasd���߷���� �ͱ�ʾ�ƶ���
	__super::Update(window);

	// �о����Գ����һ��Input��.... ���鷳
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		stateMachine->ChangeState(player->jumpState);
	}
	// ���ƶ�
	if (this->getMoveDirection(window) != MoveDirection::NONE)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // û���ƶ�
	
}

void PlayerIdleState::Update(GLFWwindow* window, float deltaTime)
{
	attackCDTimer -= deltaTime;
	this->Update(window);
	if (attackCDTimer < 0 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		attackCDTimer = attackCDTime;
		stateMachine->ChangeState(player->attackState);
	}
}