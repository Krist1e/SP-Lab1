#include "BitmapLoader.h"

ID2D1BitmapPtr BitmapLoader::LoadBitmapFromFile(ID2D1RenderTarget& renderTarget, const wchar_t* uri)
{
    IWICImagingFactoryPtr wicFactory;
    IWICBitmapDecoderPtr wicDecoder;
    IWICBitmapFrameDecodePtr wicFrame;
    IWICFormatConverterPtr wicConverter;
    ID2D1BitmapPtr d2dBitmap;

    CoInitialize(nullptr);
    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
                     reinterpret_cast<LPVOID*>(&wicFactory));
    wicFactory->CreateDecoderFromFilename(uri, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);
    wicDecoder->GetFrame(0, &wicFrame);
    wicFactory->CreateFormatConverter(&wicConverter);
    wicConverter->Initialize(wicFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0,
                             WICBitmapPaletteTypeCustom);
    renderTarget.CreateBitmapFromWicBitmap(wicConverter, nullptr, &d2dBitmap);

    return d2dBitmap;
}
