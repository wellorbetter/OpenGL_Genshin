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
    // 默认添加一个第三人称相机和一个第一人称相机
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 2.0f))); // 第三人称
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, .15f, 0.0f))); // 第一人称
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 0.0f, 0.0f), true)); // 上帝视角
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
        std::cout << "第三人称" << std::endl;
        break;
    case 1:
        std::cout << "第一人称" << std::endl;
        break;
    case 2:
        std::cout << "上帝视角" << std::endl;
        break;
    }
}

void Cinemachine::Update(const glm::vec3& targetPosition) {
    virtualCameras[activeCameraIndex].UpdatePosition(targetPosition);
}

void Cinemachine::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
}