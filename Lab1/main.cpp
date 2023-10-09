#include <chrono>
#include <windows.h>
#include <comdef.h>

#include "BitmapLoader.h"
#include "KeyboardInput.h"
#include "Sprite.h"

_COM_SMARTPTR_TYPEDEF(ID2D1Factory, __uuidof(ID2D1Factory));
_COM_SMARTPTR_TYPEDEF(ID2D1HwndRenderTarget, __uuidof(ID2D1HwndRenderTarget));

constexpr wchar_t sprite_uri[] = L"sprite.bmp";

KeyboardInput* keyboardInput = new KeyboardInput();
Sprite sprite = Sprite(keyboardInput);
ID2D1FactoryPtr factory;
ID2D1HwndRenderTargetPtr renderTarget;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT CreateGraphicsResources(HWND hwnd);
bool Render(HWND hwnd);

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, const int nCmdShow)
{
    constexpr wchar_t class_name[] = L"Lab1";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    const HWND hwnd = CreateWindowEx(
        0,
        class_name,
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
        if (PeekMessage(&messageQueue, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&messageQueue);
            DispatchMessage(&messageQueue);
        }

        if (messageQueue.message == WM_QUIT)
            break;

        auto currentTime = std::chrono::high_resolution_clock::now();
        const float deltaTime = std::chrono::duration<float>(currentTime - startTime).count();
        startTime = currentTime;
        sprite.Update(deltaTime);
        if (!Render(hwnd)) break;
    }

    return 0;
}

HRESULT CreateGraphicsResources(const HWND hwnd)
{
    HRESULT hr = S_OK;
    if (renderTarget == NULL)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        const D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hwnd, size),
            &renderTarget);
    }
    return hr;
}

bool Render(const HWND hwnd)
{
    if (FAILED(CreateGraphicsResources(hwnd)))
        return false;

    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);

    renderTarget->BeginDraw();

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    sprite.Draw(renderTarget);

    renderTarget->EndDraw();

    EndPaint(hwnd, &ps);
    return true;
}

LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
            if (SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory)) && SUCCEEDED(
                CreateGraphicsResources(hWnd)))
            {
                sprite.SetBitmap(BitmapLoader::LoadBitmapFromFile(*renderTarget, sprite_uri));
                return 0;
            }
            return -1;
        }
    case WM_MOUSEMOVE:
        {
            break;
        }
    case WM_MOUSEWHEEL:
        {
            break;
        }
    case WM_KEYDOWN:
        {
            keyboardInput->OnKeyDown(wParam);
            break;
        }
    case WM_KEYUP:
        {
            keyboardInput->OnKeyUp(wParam);
            break;
        }
    case WM_SIZE:
        {
            if (renderTarget != nullptr)
            {
                const D2D1_SIZE_U size = D2D1::SizeU(LOWORD(lParam), HIWORD(lParam));
                renderTarget->Resize(size);
            }
            break;
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
