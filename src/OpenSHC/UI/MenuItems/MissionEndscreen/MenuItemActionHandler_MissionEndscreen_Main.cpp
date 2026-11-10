#include "../MissionEndscreen.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ed279c.hpp"
#include "OpenSHC/Globals/CHAR_00eb0e44.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ec082c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D6BC0
        void MissionEndscreen::MenuItemActionHandler_MissionEndscreen_Main(int buttonID, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                return;
            }
            switch (buttonID) {
            case -1:
                if (CHAR_00eb0e44::instance != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                        DAT_WindowAndDirectDraw::instance.resolutionY, COL_BLACK::instance.shortValue);
                    CHAR_00eb0e44::instance = 0;
                    break;
                }
                BOOLEnum_00ed279c::instance = TRUE;
                break;
            case -100:
                if (CHAR_00eb0e44::instance != 0) {
                    break;
                }
                if (INT_00ec082c::instance >= 2) {
                    INT_00ec082c::instance = 2;
                    DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                    break;
                }
                INT_00ec082c::instance = 0;
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                break;
            case -101:
                if (CHAR_00eb0e44::instance != 0) {
                    break;
                }
                if (INT_00ec082c::instance < 2) {
                    INT_00ec082c::instance = 1;
                    DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
                    break;
                }
                INT_00ec082c::instance = 3;
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK;
                break;
            case -10:
                break;
            case -2:
                // -2 sorts by the first column; its own two stores cost two instructions
                buttonID = 0;
            default:
                DAT_FinalResultsOrderByColumn::instance = buttonID;
                CHAR_00eb0e44::instance = 0;
                break;
            }
        }

    }
}
}
