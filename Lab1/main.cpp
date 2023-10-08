#include <windows.h>
#include <comdef.h>
#include "Sprite.h"

_COM_SMARTPTR_TYPEDEF(ID2D1Factory, __uuidof(ID2D1Factory));
_COM_SMARTPTR_TYPEDEF(ID2D1HwndRenderTarget, __uuidof(ID2D1HwndRenderTarget));

Sprite sprite;
ID2D1FactoryPtr factory;
ID2D1HwndRenderTargetPtr renderTarget;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    constexpr wchar_t class_name[] = L"Lab1";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
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
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG messageQueue = {};

    while (GetMessage(&messageQueue, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&messageQueue);
        DispatchMessage(&messageQueue);
    }

    while (true)
    {
        if (PeekMessage(&messageQueue, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&messageQueue);
            DispatchMessage(&messageQueue);
        }

        if (messageQueue.message == WM_QUIT)
        {
            break;
        }

        sprite.Update();
    }

    return 0;
}

HRESULT CreateGraphicsResources(HWND hwnd)
{
    HRESULT hr = S_OK;
    if (renderTarget == NULL)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
        
        hr = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, size),
        &renderTarget);

    }
    return hr;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        {
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
            factory->CreateHwndRenderTarget();
        }
    case WM_MOUSEMOVE:
        {
            /*sprite.x = LOWORD(lParam) - sprite.width / 2;
            sprite.y = HIWORD(lParam) - sprite.height / 2;*/

            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        }
    case WM_MOUSEWHEEL:
        {
            

            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        }
    case WM_KEYDOWN:
        {

            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = GetDC(hWnd);

        BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(255, 255, 255)));

        EndPaint(hWnd, &ps);
        break;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
