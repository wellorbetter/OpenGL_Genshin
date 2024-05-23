#include "../../../Including/Gensin/Enemy/Enemy.h"
#include "../../../Including/Gensin/Player/Player.h"

void Enemy::Awake()
{
	modelPath = "Animation/WeirdQiuqiuren/";
	// 初始化状态机
	stateMachine = new EnemyStateMachine();
	// 初始化状态
	idleState = new EnemyIdleState(this, stateMachine, "Idle");
	moveState = new EnemyMoveState(this, stateMachine, "Move");
	attackState = new EnemyAttackState(this, stateMachine, "Attack");
}

void Enemy::Start()
{
	// 当前的位置当然不能和player重合
	this->position = glm::vec3(5.0f, 0.0f, 2.0f);
    glm::vec3 speed = glm::vec3(1.0f, 1.0f, 1.0f);
    this->setSpeed(speed);
	stateMachine->InitialState(this->idleState);
}

void Enemy::Update(GLFWwindow* window, float deltaTime)
{
    // 计算从enemy到player的方向向量
    glm::vec3 directionToPlayer = this->player->getPosition() - this->getPosition();
    directionToPlayer.y = 0; // 不更新y轴

    // 检查向量长度是否为零
    if (glm::length(directionToPlayer) > 0.0001f) {
        glm::vec3 newDirection = glm::normalize(directionToPlayer);

        // 使用线性插值来平滑方向更新
        float smoothingFactor = 0.1f; // 调整这个值来控制平滑程度
        glm::vec3 currentDirection = this->getDirection();
        glm::vec3 smoothedDirection = glm::mix(currentDirection, newDirection, smoothingFactor);

        // 再次规范化新方向
        smoothedDirection = glm::normalize(smoothedDirection);

        // printf("%f %f %f\n", smoothedDirection.x, smoothedDirection.y, smoothedDirection.z);
        this->setDirection(smoothedDirection);
    }

    stateMachine->currentState->Update(window, deltaTime);
}



void Enemy::Damage()
{
	__super::Damage();
    // 如果生命值为0，就销毁
    std::cout << "Enemy HP: " << this->HP << std::endl;
    if (this->HP <= 0) {
        // 这里不会把this给删了，只是把这个对象的状态改为destroyed
        isAlive = false;
		this->Destroy();
	}
}


Enemy::Enemy(Player* _player)
{
	this->player = _player;
}