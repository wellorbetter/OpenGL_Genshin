#include "../../../Including/Gensin/Player/Player.h"
#include "../../../Including/Gensin/Player/PlayerJumpState.h"

// ����һ���򵥵���������
const float gravity = 9.81f;
const float groundHeight = 0.0f;

void PlayerJumpState::Update(GLFWwindow* window)
{
    __super::Update(window); // ���û����Update����
}

void PlayerJumpState::Update(GLFWwindow* window, float deltaTime)
{
    this->Update(window); // �����޲�Update����

    if (this->upTimer >= 0)
    {
        this->upTimer -= deltaTime;

        // �����ٶȺ�λ��
        glm::vec3 newVelocity = this->player->getVelocity() + glm::vec3(0, this->player->getSpeed().y * deltaTime, 0);
        this->player->setVelocity(newVelocity);

        glm::vec3 newPosition = this->player->getPosition() + newVelocity * deltaTime;
        this->player->setPosition(newPosition);

        //std::cout << "����" << std::endl;
    }
    else // �½��׶�
    {
        this->downTimer -= deltaTime;
        //std::cout << "�½�" << std::endl;

        if (this->downTimer >= 0)
        {
            // �����������ٶȸ���
            glm::vec3 newVelocity = this->player->getVelocity() - glm::vec3(0, gravity * deltaTime, 0);
            this->player->setVelocity(newVelocity);

            glm::vec3 newPosition = this->player->getPosition() + newVelocity * deltaTime;

            // ����Ƿ񵽴����
            if (newPosition.y <= groundHeight)
            {
                newPosition.y = groundHeight;
                glm::vec3 newVelocity = glm::vec3(this->player->getVelocity().x, 0, this->player->getVelocity().z);
                this->player->setVelocity(newVelocity);

                // ���ü�ʱ�����л���Idle״̬
                this->upTimer = this->upTime;
                this->downTimer = this->downTime;
                //std::cout << "��Ծ�������л���Idle״̬" << std::endl;
                this->stateMachine->ChangeState(this->player->idleState);
            }

            this->player->setPosition(newPosition);
        }
        else
        {
            // ȷ���ڼ�ʱ������ʱ������ڵ�����
            glm::vec3 newPosition = this->player->getPosition();
            newPosition.y = groundHeight;
            this->player->setPosition(newPosition);

            // ���ü�ʱ�����л���Idle״̬
            this->upTimer = this->upTime;
            this->downTimer = this->downTime;
            //std::cout << "��Ծ�������л���Idle״̬" << std::endl;
            this->stateMachine->ChangeState(this->player->idleState);
        }
    }
}
