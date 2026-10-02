#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047D410
        void FindingNetworkSessions::MenuItemRenderFunction_FindingNetworkSessions_TableRows(int param_1, ...)
        {
            uint color;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_GameSynchronyState::instance.scrollBarIndex), param_1, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1
                < DAT_GameSynchronyState::instance.DPLAY_SessionsCount) {
                if ((param_1 == DAT_GameSynchronyState::instance.scrollBarIndex)
                    || (color = 0xc2f0eb, DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                    color = 0xccfaff;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderWideText, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance
                        .DPLAY_SessionNames[DAT_GameSynchronyState::instance.scrollBarItemOffset + param_1],
                    (int)((int)(DAT_ButtonX::instance + 8)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, color, 0x12, 0, 0);
            }
        }

    }
}
}
