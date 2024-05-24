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

        // 线性插值参数
        float interpFactor = 0.2f; // 调整这个参数以控制插值速度

        // 计算当前位置到目标位置的向量
        glm::vec3 currentPos = camera->Position;

        // 我这里每次都会添加一个backset，这是为了让这个相机每次都会在目标的背后
        // 方便看到目标，但是呢，我这样会导致实际的位置出现错误
        // 很好，不是这个问题，就算是，这个.3f也是很小的，没这么远才对
        glm::vec3 targetPos = targetPosition + offset + -this->camera->Front * .3f;
        this->backOffset = -this->camera->Front * .3f;
        glm::vec3 direction = targetPos - currentPos;

        // 进行插值
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
    // 默认添加一个第三人称相机和一个第一人称相机
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 0.0f))); // 第三人称
    virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 0.25f, 0.0f))); // 第一人称
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

void Cinemachine::Update(const glm::vec3& targetPosition, float deltaTime) {
    virtualCameras[activeCameraIndex].UpdatePosition(targetPosition, deltaTime);
}

void Cinemachine::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
}