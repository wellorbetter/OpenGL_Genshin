#include "../../Including/Utils/Cinemachine.h"

#include "../../Including/Lib/stb_image.h"
#include <iostream>

VirtualCamera::VirtualCamera(Camera* cam, const glm::vec3& offset, bool isFree)
    : camera(cam), offset(offset), isFreeCamera(isFree) {
    updateTimer = updateTime;
}

void VirtualCamera::UpdatePosition(const glm::vec3& targetPosition, float deltaTime) {
    updateTimer -= deltaTime;
    if (!isFreeCamera) {
        updateTimer = updateTime;

        // ���Բ�ֵ����
        float interpFactor = 0.2f; // ������������Կ��Ʋ�ֵ�ٶ�

        // ���㵱ǰλ�õ�Ŀ��λ�õ�����
        glm::vec3 currentPos = camera->Position;
        glm::vec3 bacOffset = glm::vec3(-camera->Front.x, 0.0f, -camera->Front.z);
        glm::vec3 targetPos = targetPosition + offset + glm::normalize(bacOffset) * .3f;
        glm::vec3 direction = targetPos - currentPos;

        // ���в�ֵ
        glm::vec3 interpolatedPos = currentPos + interpFactor * direction;

        camera->Position = interpolatedPos;
        camera->updateCameraVectors();
    }
}

void VirtualCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    if (isFreeCamera) {
        camera->ProcessKeyboard(direction, deltaTime);
    }
}

Cinemachine::Cinemachine(Camera* cam) {
    activeCameraIndex = 1;
    switchTime = 1.0f;
    switchTimer = switchTime;
    // Ĭ�����һ�������˳������һ����һ�˳����
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 0.0f))); // �����˳�
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 0.25f, 0.0f))); // ��һ�˳�
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 0.0f, 0.0f), true)); // �ϵ��ӽ�
}

void Cinemachine::AddVirtualCamera(const VirtualCamera& vc) {
    virtualCameras.push_back(vc);
}

void Cinemachine::SwitchCamera() {
    activeCameraIndex++;
    activeCameraIndex %= 3;
    std::cout << activeCameraIndex << std::endl;
    switch (activeCameraIndex) {
    case 0:
        std::cout << "�����˳�" << std::endl;
        break;
    case 1:
        std::cout << "��һ�˳�" << std::endl;
        break;
    case 2:
        std::cout << "�ϵ��ӽ�" << std::endl;
        break;
    }
}

void Cinemachine::Update(const glm::vec3& targetPosition, float deltaTime) {
    virtualCameras[activeCameraIndex].UpdatePosition(targetPosition, deltaTime);
}

void Cinemachine::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
}