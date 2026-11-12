#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00428A60
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDescScrollbar(
            int unused, int thumbYPos, int sliderValue, int thumbHeight, BOOLEnum isDragged)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_ROUNDTABLE
                && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_BASIC_AI_LORD_SELECT
                && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                if (MACRO_CALL(UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonH::instance, thumbYPos, isDragged,
                    thumbHeight, DAT_ButtonBackgroundBlendStrength::instance);
            }
        }

    }
}
}
