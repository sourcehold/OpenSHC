#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
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

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00428A60
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDescScrollbar(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged)
        {
            BOOLEnum BVar1;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_ROUNDTABLE
                && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_BASIC_AI_LORD_SELECT
                && DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                BVar1 = MACRO_CALL(UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
                if (!BVar1) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = BVar1;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawScrollbar, DAT_PencilRenderCore::ptr)(
                        DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)), (int)((int)(DAT_ButtonH::instance)),
                        thumbYPos, isDragged, thumbHeight, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                }
            }
        }

    }
}
}
