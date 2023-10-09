#include "GraphicsScene.h"

#include "BitmapLoader.h"

GraphicsScene::GraphicsScene(Sprite* sprite)
{
    windowHandle = nullptr;
    this->sprite = sprite;
}

bool GraphicsScene::Initialize(const HWND hwnd)
{
    windowHandle = hwnd;
    return SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory)) && SUCCEEDED(
        CreateGraphicsResources());
}

bool GraphicsScene::Render()
{
    if (FAILED(CreateGraphicsResources()))
        return false;

    PAINTSTRUCT ps;
    BeginPaint(windowHandle, &ps);

    renderTarget->BeginDraw();

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    sprite->Draw(renderTarget);

    renderTarget->EndDraw();

    EndPaint(windowHandle, &ps);
    return true;
}

void GraphicsScene::Resize(const UINT width, const UINT height) const
{
    renderTarget->Resize(D2D1::SizeU(width, height));
}

HRESULT GraphicsScene::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (renderTarget == NULL)
    {
        RECT rc;
        GetClientRect(windowHandle, &rc);
        const D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(windowHandle, size),
            &renderTarget);
    }
    return hr;
}
