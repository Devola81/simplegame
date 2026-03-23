#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL with video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* Window = SDL_CreateWindow("WAMA", 800, 600, 0);
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, NULL);
    SDL_FRect Rectangle = {0.0f, 0.0f, 100.0f, 100.0f};

    SDL_SetRenderVSync(Renderer, 0);

    if (!Window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    const bool* Key_States = SDL_GetKeyboardState(nullptr);
    SDL_Event event;

    uint32_t LastTime = 0;
    uint32_t DeltaTime = 0;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT || event.key.key == SDLK_ESCAPE) {
                running = false;
            }

        }

            uint32_t TickTime = SDL_GetTicks();
            DeltaTime = TickTime - LastTime;
            LastTime = TickTime;
            float Speed = 120.0f * (float)(DeltaTime / 1000.0f);

            if(Key_States[SDL_SCANCODE_W]){
                Rectangle.y -= Speed;
            }

            if(Key_States[SDL_SCANCODE_S]){
                Rectangle.y += Speed;
            }

            if(Key_States[SDL_SCANCODE_D]){
                Rectangle.x += Speed;
            }

            if(Key_States[SDL_SCANCODE_A]){
                Rectangle.x -= Speed;
            }
        
             SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
             SDL_RenderClear(Renderer);

            SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(Renderer, &Rectangle);

             SDL_RenderPresent(Renderer);

       
    }

    // Cleanup
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
    return 0;
}