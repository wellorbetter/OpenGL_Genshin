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
	this->stateMachine = new PlayerStateMachine();
	this->idleState = new PlayerIdleState(this, this->stateMachine, "Idle");
	this->moveState = new PlayerMoveState(this, this->stateMachine, "Move");
	this->jumpState = new PlayerJumpState(this, this->stateMachine, "Jump");
	this->attackState = new PlayerAttackState(this, this->stateMachine, "Attack");
}

void Player::Start()
{
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

	// 更新玩位置之后就更新相机的位置，相机现在和player重合
	// 只需要z轴加上-0.1即可
	/*this->cinemachine->virtualCameras[0].camera->Position = this->getPosition();
	this->cinemachine->virtualCameras[1].camera->Position = this->getPosition();

	this->cinemachine->virtualCameras[0].camera->Position.z += 
		-glm::normalize(this->cinemachine->virtualCameras[0].camera->Front).z;
	this->cinemachine->virtualCameras[1].camera->Position.z += 
		-glm::normalize(this->cinemachine->virtualCameras[0].camera->Front).z;*/
}

Player::Player(Cinemachine* _cinemachine):Entity()
{
	this->cinemachine = _cinemachine;
	// 拿到相机的第一人称的位置 以及朝向 同时修改了碰撞体的位置
	this->setPosition(this->cinemachine->virtualCameras[1].camera->Position);
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
	bullets.push_back(new Bullet(this, this->getPosition(), direction, 5.0f));
}

// 更新子弹位置
void Player::updateBullets(float deltaTime)
{
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		// 根据deltatime和速度来更新子弹位置
		(*it)->Update(deltaTime);
		// 检测碰撞

		// 检查子弹是否超出最大距离，删除子弹
		if (glm::length((*it)->getPosition() - this->getPosition()) > maxBulletDistance)
		{
			delete* it;
			it = bullets.erase(it);
		}
		else
		{
			bool isCollision = false;
			for (Enemy* enemy : EnemyManager::getInstance().getEnemies())
			{
				if (enemy) continue;
				if ((*it)->collisionCheck(enemy))
				{
					enemy->Damage(); // 对敌人造成伤害
					delete* it;
					isCollision = true;
					it = bullets.erase(it); // 碰撞后销毁子弹
					break;
				}
			}
			if (isCollision) continue;
			++it;
		}
	}
}