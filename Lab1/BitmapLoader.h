#pragma once
#include <comdef.h>
#include <d2d1.h>
#include <wincodec.h>
#pragma comment(lib, "windowscodecs.lib")

_COM_SMARTPTR_TYPEDEF(IWICImagingFactory, __uuidof(IWICImagingFactory));
_COM_SMARTPTR_TYPEDEF(IWICBitmapDecoder, __uuidof(IWICBitmapDecoder));
_COM_SMARTPTR_TYPEDEF(IWICBitmapFrameDecode, __uuidof(IWICBitmapFrameDecode));
_COM_SMARTPTR_TYPEDEF(IWICFormatConverter, __uuidof(IWICFormatConverter));
_COM_SMARTPTR_TYPEDEF(ID2D1Bitmap, __uuidof(ID2D1Bitmap));

namespace BitmapLoader
{
    ID2D1BitmapPtr LoadBitmapFromFile(ID2D1RenderTarget& renderTarget, const wchar_t* uri);
}