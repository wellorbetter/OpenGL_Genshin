#pragma once

#include "camera.h"
#include <vector>
#include <glm/glm.hpp>

class VirtualCamera {
public:
    glm::vec3 offset;
    Camera* camera;
    bool isFreeCamera;

    VirtualCamera(Camera* cam, const glm::vec3& offset, bool isFree = false);

    void UpdatePosition(const glm::vec3& targetPosition);

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
};

class Cinemachine {
public:
    std::vector<VirtualCamera> virtualCameras;
    int activeCameraIndex;
    float switchTime;
    float switchTimer;

    Cinemachine(Camera* cam);

    void AddVirtualCamera(const VirtualCamera& vc);

    void SwitchCamera();

    void Update(const glm::vec3& targetPosition);

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
};