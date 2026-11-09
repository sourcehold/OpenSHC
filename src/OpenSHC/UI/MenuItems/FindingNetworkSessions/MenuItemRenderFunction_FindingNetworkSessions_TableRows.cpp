#include "../FindingNetworkSessions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x0047D410
        void FindingNetworkSessions::MenuItemRenderFunction_FindingNetworkSessions_TableRows(int row, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(row == DAT_GameSynchronyState::instance.scrollBarIndex, row, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameSynchronyState::instance.scrollBarItemOffset + row
                >= DAT_GameSynchronyState::instance.DPLAY_SessionsCount) {
                return;
            }
            uint color;
            if (row == DAT_GameSynchronyState::instance.scrollBarIndex || DAT_ButtonCurrentlyInteracting::instance) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderWideText, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance
                    .DPLAY_SessionNames[DAT_GameSynchronyState::instance.scrollBarItemOffset + row],
                DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 4, OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
        }

    }
}
}
