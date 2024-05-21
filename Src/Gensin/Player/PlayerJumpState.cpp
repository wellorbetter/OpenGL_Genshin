#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerJumpState.h"

// 假设一个简单的重力常数
const float gravity = 9.81f;
const float groundHeight = 0.0f;

void PlayerJumpState::Update(GLFWwindow* window)
{
    __super::Update(window); // 调用基类的Update函数
}

void PlayerJumpState::Update(GLFWwindow* window, float deltaTime)
{
    this->Update(window); // 调用无参Update函数

    if (this->upTimer >= 0)
    {
        this->upTimer -= deltaTime;

        // 更新速度和位置
        glm::vec3 newVelocity = this->player->getVelocity() + glm::vec3(0, this->player->getSpeed().y * deltaTime, 0);
        this->player->setVelocity(newVelocity);

        glm::vec3 newPosition = this->player->getPosition() + newVelocity * deltaTime;
        this->player->setPosition(newPosition);

        //std::cout << "上升" << std::endl;
    }
    else // 下降阶段
    {
        this->downTimer -= deltaTime;
        //std::cout << "下降" << std::endl;

        if (this->downTimer >= 0)
        {
            // 考虑重力的速度更新
            glm::vec3 newVelocity = this->player->getVelocity() - glm::vec3(0, gravity * deltaTime, 0);
            this->player->setVelocity(newVelocity);

            glm::vec3 newPosition = this->player->getPosition() + newVelocity * deltaTime;

            // 检查是否到达地面
            if (newPosition.y <= groundHeight)
            {
                newPosition.y = groundHeight;
                glm::vec3 newVelocity = glm::vec3(this->player->getVelocity().x, 0, this->player->getVelocity().z);
                this->player->setVelocity(newVelocity);

                // 重置计时器并切换到Idle状态
                this->upTimer = this->upTime;
                this->downTimer = this->downTime;
                //std::cout << "跳跃结束，切换到Idle状态" << std::endl;
                this->stateMachine->ChangeState(this->player->idleState);
            }

            this->player->setPosition(newPosition);
        }
        else
        {
            // 确保在计时器结束时，玩家在地面上
            glm::vec3 newPosition = this->player->getPosition();
            newPosition.y = groundHeight;
            this->player->setPosition(newPosition);

            // 重置计时器并切换到Idle状态
            this->upTimer = this->upTime;
            this->downTimer = this->downTime;
            //std::cout << "跳跃结束，切换到Idle状态" << std::endl;
            this->stateMachine->ChangeState(this->player->idleState);
        }
    }
}
