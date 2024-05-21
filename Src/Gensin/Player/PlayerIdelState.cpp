#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"




void PlayerIdleState::Update(GLFWwindow* window)
{
	// �������
	// ����wasd���߷���� �ͱ�ʾ�ƶ���
	__super::Update(window);

	// ���ƶ�
	if (   glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS 
		|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player->isMoving = true;
		stateMachine->ChangeState(player->moveState);
	} // û���ƶ�
	else
	{
		player->isMoving = false;
	}
}