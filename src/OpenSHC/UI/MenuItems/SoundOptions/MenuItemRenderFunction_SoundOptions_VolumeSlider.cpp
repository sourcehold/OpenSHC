#include "../SoundOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004929C0
        void SoundOptions::MenuItemRenderFunction_SoundOptions_VolumeSlider(
            int unused, int thumbXPos, int volume, int thumbWidth, BOOLEnum isDragged)
        {
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            // -1: the plain tiled button (the slider's track)
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            // the thumb: x and y before its colour; in the call they lose the match
            int const thumbX = thumbXPos + DAT_ButtonX::instance;
            int const buttonY = DAT_ButtonY::instance;
            ushort color = COL_GREYISH_YELLOW::instance.shortValue;
            if (isDragged) {
                color = COL_DARK_LIME::instance.shortValue;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                thumbX + 1, buttonY + 2, thumbX + thumbWidth - 2, buttonY + DAT_ButtonH::instance - 4, color);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(volume,
                DAT_ButtonW::instance + DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 7,
                OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, FALSE, 0);
        }

    }
}
}
