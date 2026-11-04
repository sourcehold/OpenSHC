#include "../MissionEndscreen.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"
#include "OpenSHC/Globals/INT_00ed279c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D6BC0
        void MissionEndscreen::MenuItemActionHandler_MissionEndscreen_Main(int action, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                return;
            }
            // DAT_00ec082c is the page: 0 and 1 are the 800x600 layout, 2 and 3 the larger one
            switch (action) {
            case -1:
                if (INT_00eb0e44::instance != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                        DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
                    INT_00eb0e44::instance = 0;
                    return;
                }
                INT_00ed279c::instance = 1;
                return;
            case -100:
                if (INT_00eb0e44::instance != 0) {
                    return;
                }
                if (DAT_00ec082c::instance >= 2) {
                    DAT_00ec082c::instance = 2;
                    DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                    return;
                }
                DAT_00ec082c::instance = 0;
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                return;
            case -101:
                if (INT_00eb0e44::instance != 0) {
                    return;
                }
                if (DAT_00ec082c::instance < 2) {
                    DAT_00ec082c::instance = 1;
                    DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
                    return;
                }
                DAT_00ec082c::instance = 3;
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK;
                return;
            case -10:
                return;
            case -2:
                // -2 sorts by the first column
                action = 0;
            default:
                DAT_FinalResultsOrderByColumn::instance = action;
                INT_00eb0e44::instance = 0;
                return;
            }
        }

    }
}
}
