#include "../../Including/Utils/Cinemachine.h"

#include <iostream>

VirtualCamera::VirtualCamera(Camera* cam, const glm::vec3& offset, bool isFree)
    : camera(cam), offset(offset), isFreeCamera(isFree) {}

void VirtualCamera::UpdatePosition(const glm::vec3& targetPosition) {
    if (!isFreeCamera) {
        camera->Position = targetPosition + offset;
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
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 2.0f))); // �����˳�
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, .15f, 0.0f))); // ��һ�˳�
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

void Cinemachine::Update(const glm::vec3& targetPosition) {
    virtualCameras[activeCameraIndex].UpdatePosition(targetPosition);
}

void Cinemachine::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
}