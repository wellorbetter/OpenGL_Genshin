#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"




void PlayerIdleState::Update(GLFWwindow* window)
{
	// �������
	// ����wasd���߷���� �ͱ�ʾ�ƶ���
	__super::Update(window);

	// ���ƶ�
	if (this->getMoveDirection(window) != MoveDirection::NONE)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // û���ƶ�
	else
	{
		player->isMoving = false;
	}
}