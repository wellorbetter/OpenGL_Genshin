#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Player/Player.h"




void PlayerIdleState::Update(GLFWwindow* window)
{
	// 检查输入
	// 按下wasd或者方向键 就表示移动了
	__super::Update(window);

	// 在移动
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
	} // 没有移动
	else
	{
		player->isMoving = false;
	}
}