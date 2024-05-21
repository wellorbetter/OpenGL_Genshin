#include "../../../Including/Gensin/Player/PlayerMoveState.h"
#include "../../../Including/Gensin/Player/Player.h"



void PlayerMoveState::Update(GLFWwindow* window)
{
	// 在移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player->isMoving = true;
		
	} // 没有移动
	else
	{
		player->isMoving = false;
		stateMachine->ChangeState(player->idleState);
	}
}