#pragma once
#include <comdef.h>
#include <d2d1.h>

#include "Sprite.h"
#pragma comment(lib, "d2d1")

_COM_SMARTPTR_TYPEDEF(ID2D1Factory, __uuidof(ID2D1Factory));
_COM_SMARTPTR_TYPEDEF(ID2D1HwndRenderTarget, __uuidof(ID2D1HwndRenderTarget));

class GraphicsScene
{
public:
    explicit GraphicsScene(Sprite* sprite);
    bool Initialize(HWND hwnd);
    bool Render();
    void Resize(UINT width, UINT height) const;

    ID2D1RenderTarget& GetRenderTarget() const { return *renderTarget; }

private:
    HWND windowHandle;
    ID2D1FactoryPtr factory;
    ID2D1HwndRenderTargetPtr renderTarget;
    Sprite* sprite;
    ID2D1BitmapPtr bitmap;

    HRESULT CreateGraphicsResources();
};
