#include <chrono>
#include <windows.h>

#include "BitmapLoader.h"
#include "GraphicsScene.h"
#include "Input.h"
#include "Sprite.h"

constexpr wchar_t spritePath[] = L"cat.png";

Input* input = new Input();
Borders* borders = new Borders();
Sprite sprite = Sprite(input, borders);
GraphicsScene scene = GraphicsScene(&sprite);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, const int nCmdShow)
{
    constexpr wchar_t className[] = L"Lab1";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    const HWND hwnd = CreateWindowEx(
        0,
        className,
        L"MainWindow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG messageQueue = {};
    auto startTime = std::chrono::high_resolution_clock::now();
    while (true)
    {
        while (PeekMessage(&messageQueue, nullptr, 0, 0, PM_REMOVE))
        {
            if (messageQueue.message == WM_QUIT)
                break;

            TranslateMessage(&messageQueue);
            DispatchMessage(&messageQueue);
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        const float deltaTime = std::chrono::duration<float>(currentTime - startTime).count();
        startTime = currentTime;
        sprite.Update(deltaTime);
        if (!scene.Render())
            break;
    }

    return 0;
}

LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
            if (scene.Initialize(hWnd))
            {
                sprite.SetBitmap(BitmapLoader::LoadBitmapFromFile(scene.GetRenderTarget(), spritePath), 0.5f);
                return 0;
            }
            return -1;
        }
    case WM_MOUSEMOVE:
        {
            input->OnMouseMove(lParam);
            break;
        }
    case WM_LBUTTONDOWN:
        {
            input->OnMouseDown(wParam, lParam);
            sprite.SetSelected(input->IsMouseOver(sprite.GetRect()));
            break;
        }
    case WM_LBUTTONUP:
        {
            input->OnMouseUp(wParam, lParam);
            break;
        }
    case WM_MOUSEWHEEL:
        {
            input->OnMouseWheel(wParam);
            break;
        }
    case WM_KEYDOWN:
        {
            input->OnKeyDown(wParam);
            break;
        }
    case WM_KEYUP:
        {
            input->OnKeyUp(wParam);
            break;
        }
    case WM_SIZE:
        {
            const UINT width = LOWORD(lParam);
            const UINT height = HIWORD(lParam);
            scene.Resize(width, height);
            borders->SetSize(width, height);
            break;
        }
    case WM_DESTROY:
        delete input;
        delete borders;
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
