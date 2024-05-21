#include "../../../Including/Gensin/Player/PlayerState.h"
#include "../../../Including/Gensin/Player/Player.h"

PlayerState::PlayerState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName)
{
	player = _player;
	stateMachine = _stateMachine;
	stateName = _stateName;
}

void PlayerState::Update(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 按下w键和上键
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// 方向修改 往x轴正方向走
		glm::vec3 newDir = glm::vec3(1.0f, 0.0f, 0.0f);
		player->setDirection(newDir);
		glm::vec3 newVelovity = player->getDirection() * player->getSpeed();
		player->setVelocity(newVelovity);
		// 切换到跑步状态
		
	}
}