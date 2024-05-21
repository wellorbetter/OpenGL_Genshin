#pragma once

#include "camera.h"
#include <vector>
#include <glm/glm.hpp>

class VirtualCamera {
public:
    glm::vec3 offset;
    Camera* camera;
    bool isFreeCamera; // �Ƿ�Ϊ����������ϵ��ӽǣ�

    VirtualCamera(Camera* cam, const glm::vec3& offset, bool isFree = false)
        : camera(cam), offset(offset), isFreeCamera(isFree) {}

    void UpdatePosition(const glm::vec3& targetPosition) {
        if (!isFreeCamera) {
            camera->Position = targetPosition + offset;
            camera->updateCameraVectors();
        }
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        if (isFreeCamera) {
            camera->ProcessKeyboard(direction, deltaTime);
        }
    }
};

class Cinemachine {
public:
    std::vector<VirtualCamera> virtualCameras;
    int activeCameraIndex;

    Cinemachine(Camera* cam) {
        activeCameraIndex = 0;
        // Ĭ�����һ�������˳������һ����һ�˳����
        // 0 1 2 ---- 3 1 ��
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 2.0f, 5.0f))); // �����˳�
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 1.5f, 0.0f))); // ��һ�˳�
        virtualCameras.push_back(VirtualCamera(cam, glm::vec3(0.0f, 10.0f, 0.0f), true)); // �ϵ��ӽ�
    }

    void AddVirtualCamera(const VirtualCamera& vc) {
        virtualCameras.push_back(vc);
    }

    void SwitchCamera() {
        activeCameraIndex = (activeCameraIndex + 1) % virtualCameras.size();
    }

    void Update(const glm::vec3& targetPosition) {
        virtualCameras[activeCameraIndex].UpdatePosition(targetPosition);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        virtualCameras[activeCameraIndex].ProcessKeyboard(direction, deltaTime);
    }
};
