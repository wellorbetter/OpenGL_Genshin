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

    // ����w�����ϼ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		// �����޸� ��x����������
		glm::vec3 newDir = glm::vec3(1.0f, 0.0f, 0.0f);
		player->setDirection(newDir);
		glm::vec3 newVelovity = player->getDirection() * player->getSpeed();
		player->setVelocity(newVelovity);
		// �л����ܲ�״̬
		
	}
}