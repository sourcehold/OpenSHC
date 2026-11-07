#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004690E0
        void PencilRenderCore::drawScrollbar(
            uint xPos, int yPos, int height, int thumbYPos, BOOLEnum isDragged, int thumbHeight, int blendStrength)
        {
            int alphaImageID;
            int _yPosEnd = height + yPos;
            int _yPos = yPos;
            if (yPos <= _yPosEnd - 20) {
                do {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 79, (int)(xPos),
                        _yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 80, blendStrength);
                    _yPos += 20;
                } while (_yPos <= _yPosEnd - 20);
            }
            for (; _yPos < _yPosEnd; ++_yPos) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 95, (int)(xPos),
                    _yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 96, blendStrength);
            }
            if (isDragged) {
                if (thumbHeight <= 20) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 89, (int)(xPos), yPos + thumbYPos);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 100, (int)(xPos), thumbYPos + yPos);
                _yPos = thumbYPos + 10;
                if (10 < thumbHeight - 10) {
                    _yPosEnd = thumbHeight - 20;
                    do {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 101, (int)(xPos), _yPos + yPos);
                        ++_yPos;
                        --_yPosEnd;
                    } while (_yPosEnd != 0);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 102, (int)(xPos), yPos + _yPos);
            }
            if (thumbHeight <= 20) {
                alphaImageID = 90;
                _yPosEnd = 89;
                _yPos = thumbYPos;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 100, (int)(xPos),
                    thumbYPos + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 103, blendStrength);
                _yPos = thumbYPos + 10;
                if (10 < thumbHeight - 10) {
                    thumbYPos = thumbHeight - 20;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 101,
                            (int)(xPos), _yPos + yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 104,
                            blendStrength);
                        ++_yPos;
                        --thumbYPos;
                    } while (thumbYPos != 0);
                }
                alphaImageID = 105;
                _yPosEnd = 102;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _yPosEnd, (int)(xPos),
                yPos + _yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, alphaImageID, blendStrength);
        }

    }
}
}
