#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmImageType.hpp"
#include "OpenSHC/IO/Graphics/GmImageTypeInt.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmImageType;
        using OpenSHC::IO::Graphics::GmImageTypeInt;
        using OpenSHC::Rendering::ColorMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00455930
        void TextureRenderCore::adaptGmColorsToRGB565IfRequired(int gmID, int imageIndex)
        {
            GmImageTypeInt _gmImageType;
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                _gmImageType = this->gmFileHeaderColorpaletteArray[gmID].ImageType;
                if ((_gmImageType == OpenSHC::IO::Graphics::GIT_InterfaceElement)
                    || (_gmImageType == OpenSHC::IO::Graphics::GIT_Font)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxCompressedImageToRGB565, this)(
                        imageIndex);
                } else {
                    if (_gmImageType == OpenSHC::IO::Graphics::GIT_UncompressedImageUnk) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                              transformUncompressedImageWithMarkerUnkToRGB565,
                            this)(imageIndex);
                    }
                    if (_gmImageType == OpenSHC::IO::Graphics::GIT_CompressedImage) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxCompressedImageToRGB565, this)(
                            imageIndex);
                    }
                    if (_gmImageType == OpenSHC::IO::Graphics::GIT_Tileset) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTilesetToRGB565, this)(imageIndex);
                    }
                    if (_gmImageType == OpenSHC::IO::Graphics::GIT_UncompressedImage) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::transformUncompressedImageToRGB565, this)(
                            imageIndex);
                    }
                }
            }
        }

    }
}
}
