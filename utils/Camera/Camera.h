#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../shader_program/LocSet.h"
#include "../shader_program/shader_program.h"
#include <string>

class Camera {
public:
    Camera(glm::vec3 InitialPos, float Speed, float Sensitivity, float Width, float Hieght);
    void Use_Camera_Movement();
    void Set_Mouse();
    glm::mat4 Get_View();
    float GetFPS();
private:
    const bool* Key_States = SDL_GetKeyboardState(nullptr);
    float FPS = 1.0f / ((float)DeltaTime / 1000.0f);
    glm::vec3 Direction;
    glm::vec3 CameraPos;
    glm::vec3 CameraFront;
    glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float Pitch = 0.0f;
    float Yaw = -90.0f;
    float LastX;
    float LastY;
    float Xoffset;
    float Yoffset;
    float Speed;
    float FirstMouse;
    float Sensitivity;
    uint32_t DeltaTime = 0;
    uint32_t LastFrame = 0;
    glm::mat4 View = glm::mat4(1.0f);
};
