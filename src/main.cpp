#include "../utils/Camera/Camera.h"
#include "../utils/VAO/VAO.h"
#include "../utils/VBO/VBO.h"
#include "../utils/shader_program/shader_program.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <stdio.h>
#include <string>

#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

using namespace std;

void ErrorHandleWindow(SDL_Window *Window) {
  if (!Window) {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }
}

void IntializeSDL() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
  }
}

void IntializeGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  IntializeSDL();

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

  int Initial_WIDTH = 800;
  int Initial_HIEGHT = 600;

  SDL_Window *Window =
      SDL_CreateWindow("GAME", Initial_WIDTH, Initial_HIEGHT,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  SDL_GLContext OpenglContext = SDL_GL_CreateContext(Window);

  int WIDTH;
  int HIEGHT;

  IntializeGLAD();
  ErrorHandleWindow(Window);

  cgltf_options Options = {};
  cgltf_data *Data = NULL;
  cgltf_result Result =
      cgltf_parse_file(&Options, "Modeltest/Untitled.glb", &Data);

  if (Result == cgltf_result_success) {
    cout << "Succefull parsing" << endl;
    // cout << Data->meshes[0] << endl;
    cgltf_free(Data);
  } else {
    cout << "failed to parse" << endl;
  }

  Shader ShaderSource = Shader(std::string("shaders/vertex.vert"),
                               std::string("shaders/fragment.frag"));

  GLfloat Vertices[] = {0.0f,  0.8f,  1.0f, 1.0f, 0.0f, 0.0f,
                        -0.8f, -0.8f, 1.0f, 0.0f, 1.0f, 0.0f,
                        0.8f,  -0.8f, 1.0f, 0.0f, 0.0f, 1.0f};

  VAO VertexArray = VAO();
  VBO VertexBuffer = VBO(Vertices, sizeof(Vertices));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  bool running = true;
  SDL_Event event;
  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
  float speed = 5.0f;
  float sensitivity = 0.5f;
  Camera MainCam(pos, speed, sensitivity, Initial_WIDTH, Initial_HIEGHT);

  ShaderSource.UseShader();

  while (running) {
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    MainCam.Set_Mouse();
    MainCam.Use_Camera_Movement();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = MainCam.Get_View();
    glm::mat4 projection = glm::mat4(1.0f);

    float aspect = 1.0f;
    if (width > 0 && height > 0) {
      aspect = static_cast<float>(width) / static_cast<float>(height);
    }

    projection = glm::perspective(glm::radians(45.0f),
                                  aspect, 0.1f, 100.0f);

    ShaderSource.SetMat4("model", model);
    ShaderSource.SetMat4("view", view);
    ShaderSource.SetMat4("proj", projection);

    SDL_GetWindowSize(Window, &WIDTH, &HIEGHT);
    glViewport(0, 0, WIDTH, HIEGHT);

    // fps calc
    printf("%f\n", 1 / MainCam.GetFPS());

    VertexArray.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    SDL_GL_SwapWindow(Window);
  }

  SDL_DestroyWindow(Window);
  SDL_Quit();
  return 0;
}
