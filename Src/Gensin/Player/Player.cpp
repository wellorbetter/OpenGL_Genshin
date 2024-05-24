#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerIdleState.h"
#include "../../../Including/Gensin/Enemy/EnemyManager.h"

std::map<string, Model*> Animator::models;
std::map<std::string, Animation*> Animator::animations;
void Player::Awake()
{
	// 初始化动画 setAnim直接拿
	// 创建某些状态 加载东西
	modelPath = "Animation/Babala/";
	this->collider = new Collider();
	this->stateMachine = new PlayerStateMachine();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->moveState = new PlayerMoveState(this, this->stateMachine, "Move");
	this->jumpState = new PlayerJumpState(this, this->stateMachine, "Jump");
	this->attackState = new PlayerAttackState(this, this->stateMachine, "Attack");
}

void Player::Start()
{
	this->position = glm::vec3(0.0, 0.0, 1.0f);
	// 开始进入状态渲染
	this->stateMachine->InitialState(this->idleState);
	// 设定移动速度
	glm::vec3 speed = glm::vec3(2.0f, 2.0f, 2.0f);
	this->setSpeed(speed);
}

void Player::Update(GLFWwindow* window)
{
	__super::Update(window);
	// 退出游戏

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Player::Update(GLFWwindow* window, float deltaTime)
{
	this->Update(window);
	this->cinemachine->switchTimer -= deltaTime;
	// 相机的移动 只有上帝视角可以移动

	// 这里有问题的，因为每次的update非常非常短，这里的deltaTime是一个很小的数
	// 所以可能我按下了c键但是update已经执行了好几次了
	// 所以切换相机需要一个内置时间 比如1秒

	// 切换相机
	if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) && this->cinemachine->switchTimer < 0)
	{
		cinemachine->SwitchCamera();
		this->cinemachine->switchTimer = this->cinemachine->switchTime;
	}
	// 如果是上帝视角角色不准动
	if (this->cinemachine->activeCameraIndex == 2)
	{
		stateMachine->ChangeState(this->idleState);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cinemachine->ProcessKeyboard(RIGHT, deltaTime);
		// 同时不准进行更新
		//printf("%lf %lf %lf\n", this->getDirection().x, this->getDirection().y, this->getDirection().z);
		return;
	}

	// 状态的更新
	stateMachine->currentState->Update(window, deltaTime);
	
	this->collider->UpdateCollider(this->position);
	//this->collider->RenderCollider();
}

Player::Player(Cinemachine* _cinemachine):Entity()
{
	this->cinemachine = _cinemachine;
	// 拿到相机的第一人称的位置 以及朝向 同时修改了碰撞体的位置

	// 这个位置需要加上一定的偏移量，因为我相机的位置和实际的位置不一样，我加了一个backOffset
	/*glm::vec3 newPositon = this->cinemachine->virtualCameras[1].camera->Position - this->cinemachine->virtualCameras[1].backOffset;
	this->setPosition(newPositon);*/
	this->setDirection(this->cinemachine->virtualCameras[1].camera->Front);
}

void Player::Damage()
{
	__super::Damage();
	// 受伤就响一下受伤音效，然后白光闪两下
	// 白光就是model的材质变成白色，然后再变回来
	// 材质这好像不太好改，算了，就搞个音效之后
}


// 发射子弹
void Player::fireBullet(float len)
{
	// 方向是player正方向
	glm::vec3 direction = this->cinemachine->virtualCameras[1].camera->Front;
	direction.y = 0;
	bullets.push_back(new Bullet(this, this->getPosition(), direction, 1.5f));
}

// 更新子弹位置
void Player::updateBullets(float deltaTime)
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		// 根据deltatime和速度来更新子弹位置
		(*it)->Update(deltaTime);

		// 检查子弹是否超出最大距离，删除子弹
		if (glm::length((*it)->getPosition() - this->getPosition()) > maxBulletDistance)
		{
			delete* it;
			it = bullets.erase(it);
		}
		else
		{// 检测碰撞
			bool isCollision = false;
			for (Enemy* enemy : EnemyManager::getInstance().getEnemies())
			{
				if (!enemy || !enemy->isAlive || !enemy->collider) continue;
				if ((*it)->collider->collisionCheck(enemy->collider))
				{
					enemy->Damage(); // 对敌人造成伤害
					// 不太懂c++ 指针destroy写一堆bug 受不了了
					// 置空写在Main里面了
					delete* it;
					*it = nullptr;
					isCollision = true;
					it = bullets.erase(it);
					break;
				}
			}
			if (isCollision) continue;
			++it;
		}
	}
}