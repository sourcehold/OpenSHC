#include "../Chat.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047FFE0
        void Chat::MenuItemRenderFunction_Chat_TauntButtons(int taunt, ...)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (taunt < 10) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    taunt, DAT_ButtonX::instance + 12, DAT_ButtonY::instance + 9, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    taunt, DAT_ButtonX::instance + 9, DAT_ButtonY::instance + 9, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                DAT_GameSynchronyState::instance.DAT_InsultTextIndex = taunt;
            }
        }

    }
}
}
