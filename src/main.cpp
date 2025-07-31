/* Copyright 2022 Felice Pantaleo, Andrea Bocci, Jan Stephan
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define SDL_MAIN_USE_CALLBACKS
#include <alpaka/alpaka.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window* window = NULL;
static SDL_GPUDevice* device = NULL;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
    window = SDL_CreateWindow("Hello!", 1920, 1080, SDL_WINDOW_FULLSCREEN);
    if(!window)
    {
        SDL_Log("Couldn't create window : %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, false, NULL);
    SDL_ClaimWindowForGPUDevice(device, window);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    // acquire the command buffer
    SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);

    // get the swapchain texture
    SDL_GPUTexture* swapchainTexture;
    uint32_t width, height;
    SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, &width, &height);

    // end the frame early if a swapchain texture is not available
    if(swapchainTexture == NULL)
    {
        // you must always submit the command buffer
        SDL_SubmitGPUCommandBuffer(commandBuffer);
        return SDL_APP_CONTINUE;
    }

    // create the color target
    SDL_GPUColorTargetInfo colorTargetInfo{};
    colorTargetInfo.clear_color = {240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 255 / 255.0f};
    colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
    colorTargetInfo.texture = swapchainTexture;

    // begin a render pass
    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, NULL);

    // draw something

    alpaka::onHost::Device host = alpaka::onHost::makeHostDevice();

    std::cout << "Use host device:\n";
    std::cout << "  - " << alpaka::onHost::getName(host) << "\n\n";

    // create a blocking host queue and submit some work to it
    alpaka::onHost::Queue queue = host.makeQueue();

    std::cout << "Enqueue some work\n";

    queue.enqueue(
        []() noexcept
        {
            std::cout << "  - host task running...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1u));
            std::cout << "  - host task complete\n";
        });

    // wait for the work to complete
    std::cout << "Wait for the enqueue work to complete...\n";
    alpaka::onHost::wait(queue);
    std::cout << "All work has completed\n";


    // end the render pass
    SDL_EndGPURenderPass(renderPass);

    // submit the command buffer
    SDL_SubmitGPUCommandBuffer(commandBuffer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    // close the window
    if(event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED
       || event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
}
