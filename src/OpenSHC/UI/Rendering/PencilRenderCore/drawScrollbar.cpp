#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using DE::SHCDE::eGM;
        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004690E0
        void PencilRenderCore::drawScrollbar(
            uint xPos, int yPos, int height, int thumbYPos, BOOLEnum isDragged, int thumbHeight, int blendStrength)
        {
            int _yPosEnd;
            int _yPos;
            int alphaImageID;
            _yPosEnd = height + yPos;
            _yPos = yPos;
            if (yPos <= _yPosEnd + -0x14) {
                do {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x4f, (int)(xPos), _yPos,
                        IO::Graphics::GID_INTERFACE_ICONS_3, 0x50, blendStrength);
                    _yPos = _yPos + 0x14;
                } while (_yPos <= _yPosEnd + -0x14);
            }
            for (; _yPos < _yPosEnd; _yPos = _yPos + 1) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x5f, (int)(xPos), _yPos,
                    IO::Graphics::GID_INTERFACE_ICONS_3, 0x60, blendStrength);
            }
            if (isDragged) {
                if (thumbHeight < 0x15) {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        DE::SHCDE::GM_INTERFACE_ICONS3, 0x59, (int)(xPos), yPos + thumbYPos);
                }
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS3, 100, (int)(xPos), thumbYPos + yPos);
                _yPos = thumbYPos + 10;
                if (10 < thumbHeight + -10) {
                    _yPosEnd = thumbHeight + -0x14;
                    do {
                        MACRO_CALL_MEMBER(
                            UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            DE::SHCDE::GM_INTERFACE_ICONS3, 0x65, (int)(xPos), _yPos + yPos);
                        _yPos = _yPos + 1;
                        _yPosEnd = _yPosEnd + -1;
                    } while (_yPosEnd);
                }
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS3, 0x66, (int)(xPos), yPos + _yPos);
            }
            if (thumbHeight < 0x15) {
                alphaImageID = 0x5a;
                _yPosEnd = 0x59;
                _yPos = thumbYPos;
            } else {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 100, (int)(xPos),
                    thumbYPos + yPos, IO::Graphics::GID_INTERFACE_ICONS_3, 0x67, blendStrength);
                _yPos = thumbYPos + 10;
                if (10 < thumbHeight + -10) {
                    thumbYPos = thumbHeight + -0x14;
                    do {
                        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x65, (int)(xPos),
                            _yPos + yPos, IO::Graphics::GID_INTERFACE_ICONS_3, 0x68, blendStrength);
                        _yPos = _yPos + 1;
                        thumbYPos = thumbYPos + -1;
                    } while (thumbYPos);
                }
                alphaImageID = 0x69;
                _yPosEnd = 0x66;
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, _yPosEnd, (int)(xPos),
                yPos + _yPos, IO::Graphics::GID_INTERFACE_ICONS_3, alphaImageID, blendStrength);
        }

    }
}
}
