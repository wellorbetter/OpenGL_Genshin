#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"

void PlayerIdleState::Enter()
{
	player->setAnimation("Idle", true);
}

void PlayerIdleState::Exit()
{
	player->setAnimation("Idle", false);
}



void PlayerIdleState::Update(GLFWwindow* window)
{
	// �������
	// ���������processInput(GLFWwindow* window)����

}