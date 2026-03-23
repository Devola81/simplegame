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

    if (!Window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            else if(event.type == SDL_EVENT_KEY_DOWN){
                switch(event.key.key){
                    case SDLK_D:
                        Rectangle.x += 10.0f;
                        break;

                    case SDLK_A:
                        Rectangle.x -= 10.0f;
                        break;

                    case SDLK_W:
                        Rectangle.y -= 10.0f;
                        break;

                    case SDLK_S:
                        Rectangle.y += 10.0f;
                        break;
                    
                }
            }
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