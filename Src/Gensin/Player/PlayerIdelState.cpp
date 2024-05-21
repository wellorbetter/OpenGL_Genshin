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
	// 检查输入
	// 或许可以用processInput(GLFWwindow* window)函数

}