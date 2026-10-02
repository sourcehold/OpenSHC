#include "../LobbyMenu.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042B8F0
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectScrollbar(
            int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged)
        {
            BOOLEnum BVar1;
            BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar1 == FALSE) {
                if (((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                        && (DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                    && (DAT_MenuModalComposition1::instance.activeModalDialogID
                        != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT)) {
                    DAT_ButtonUnknownZero::instance = 0;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonH::instance)), thumbYPos, isDragged, thumbHeight,
                        (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                }
                DAT_ButtonUnknownZero::instance = 1;
            }
        }

    }
}
}
