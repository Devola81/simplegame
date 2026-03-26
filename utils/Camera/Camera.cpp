#include "Camera.h"

Camera::Camera(glm::vec3 InitialPos, float Speed, float Sensitivity,
               float Width, float Hieght) {
  this->CameraPos = InitialPos;
  this->Speed = Speed;
  this->Sensitivity = Sensitivity;
  this->LastX = Width / 2;
  this->LastY = Hieght / 2;
}

void Camera::Use_Camera_Movement() {

  uint32_t CurrentFrame = SDL_GetTicks();
  DeltaTime = CurrentFrame - LastFrame;
  LastFrame = CurrentFrame;
  float CamSpeed = Speed * (float)(DeltaTime / 1000.0f);

  if (Key_States[SDL_SCANCODE_W])
    CameraPos += CamSpeed * CameraFront;
  if (Key_States[SDL_SCANCODE_S])
    CameraPos -= CamSpeed * CameraFront;
  if (Key_States[SDL_SCANCODE_A])
    CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CamSpeed;
  if (Key_States[SDL_SCANCODE_D])
    CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CamSpeed;
  if (Key_States[SDL_SCANCODE_K])
    CameraPos += CameraUp * CamSpeed;
  if (Key_States[SDL_SCANCODE_J])
    CameraPos -= CameraUp * CamSpeed;
  std::cout << "FPS = " << 1.0f / (DeltaTime / 1000.0f);
}

glm::mat4 Camera::Get_View() {
  View = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
  return View;
}

void Camera::Set_Mouse() {
  float Xpos, Ypos;
  SDL_GetMouseState(&Xpos, &Ypos);

  if (FirstMouse) {
    LastX = Xpos;
    LastY = Ypos;
    FirstMouse = false;
  }

  Xoffset = Xpos - LastX;
  Yoffset = LastY - Ypos;
  LastX = Xpos;
  LastY = Ypos;

  Xoffset *= Sensitivity;
  Yoffset *= Sensitivity;

  Yaw += Xoffset;
  Pitch += Yoffset;

  if (Pitch > 90.0f) {
    Pitch = 90.0f;
  }

  if (Pitch < -90.0f) {
    Pitch = -90.0f;
  }

  this->Direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  this->Direction.y = sin(glm::radians(Pitch));
  this->Direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

  CameraFront = glm::normalize(Direction);
}

float Camera::GetFPS() { return DeltaTime; }
