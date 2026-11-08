#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // Pictures in GID_INTERFACE_ICONS_3. The track's two and the small thumb are each followed by its alpha mask;
        // the thumb's top, middle row and bottom are followed by their three masks.
        enum {
            SCROLLBAR_TRACK_PICTURE = 79,
            SCROLLBAR_TRACK_ROW_PICTURE = 95,
            SCROLLBAR_SMALL_THUMB_PICTURE = 89,
            SCROLLBAR_THUMB_TOP_PICTURE = 100,
            SCROLLBAR_THUMB_ROW_PICTURE = 101,
            SCROLLBAR_THUMB_BOTTOM_PICTURE = 102,
            SCROLLBAR_TRACK_PICTURE_HEIGHT = 20,
            SCROLLBAR_SMALL_THUMB_HEIGHT = 20,
            SCROLLBAR_THUMB_END_HEIGHT = 10
        };

        // FUNCTION: STRONGHOLDCRUSADER 0x004690E0
        void PencilRenderCore::drawScrollbar(
            uint xPos, int yPos, int height, int thumbYPos, BOOLEnum isDragged, int thumbHeight, int blendStrength)
        {
            int const top = yPos;
            int const bottom = yPos + height;
            // The track in whole pictures, then single rows down to the bottom
            for (; yPos <= bottom - SCROLLBAR_TRACK_PICTURE_HEIGHT; yPos += SCROLLBAR_TRACK_PICTURE_HEIGHT) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_TRACK_PICTURE, xPos, yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_TRACK_PICTURE + 1, blendStrength);
            }
            for (; yPos < bottom; ++yPos) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_TRACK_ROW_PICTURE, xPos, yPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_TRACK_ROW_PICTURE + 1, blendStrength);
            }
            // A dragged thumb is drawn without its masks
            if (isDragged) {
                if (thumbHeight <= SCROLLBAR_SMALL_THUMB_HEIGHT) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, SCROLLBAR_SMALL_THUMB_PICTURE, xPos, top + thumbYPos);
                    return;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, SCROLLBAR_THUMB_TOP_PICTURE, xPos, top + thumbYPos);
                // The top and bottom pieces are 10 pixels high, single middle rows fill the rest
                thumbYPos += SCROLLBAR_THUMB_END_HEIGHT;
                thumbHeight -= SCROLLBAR_THUMB_END_HEIGHT;
                for (int row = SCROLLBAR_THUMB_END_HEIGHT; row < thumbHeight; ++row) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, SCROLLBAR_THUMB_ROW_PICTURE, xPos, top + thumbYPos);
                    ++thumbYPos;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, SCROLLBAR_THUMB_BOTTOM_PICTURE, xPos, top + thumbYPos);
                return;
            }
            if (thumbHeight <= SCROLLBAR_SMALL_THUMB_HEIGHT) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_SMALL_THUMB_PICTURE, xPos, top + thumbYPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_SMALL_THUMB_PICTURE + 1, blendStrength);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                SCROLLBAR_THUMB_TOP_PICTURE, xPos, top + thumbYPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                SCROLLBAR_THUMB_TOP_PICTURE + 3, blendStrength);
            // The top and bottom pieces are 10 pixels high, single middle rows fill the rest
            thumbYPos += SCROLLBAR_THUMB_END_HEIGHT;
            thumbHeight -= SCROLLBAR_THUMB_END_HEIGHT;
            for (int row = SCROLLBAR_THUMB_END_HEIGHT; row < thumbHeight; ++row) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_THUMB_ROW_PICTURE, xPos, top + thumbYPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    SCROLLBAR_THUMB_ROW_PICTURE + 3, blendStrength);
                ++thumbYPos;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                SCROLLBAR_THUMB_BOTTOM_PICTURE, xPos, top + thumbYPos, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                SCROLLBAR_THUMB_BOTTOM_PICTURE + 3, blendStrength);
        }

    }
}
}
