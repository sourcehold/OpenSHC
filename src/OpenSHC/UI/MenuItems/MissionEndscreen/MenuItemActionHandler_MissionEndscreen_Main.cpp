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

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D6BC0
        void MissionEndscreen::MenuItemActionHandler_MissionEndscreen_Main(int param_1, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                switch (param_1) {
                case -0x65:
                    if ((char)INT_00eb0e44::instance == '\0') {
                        if (DAT_00ec082c::instance < 2) {
                            DAT_00ec082c::instance = 1;
                            DAT_GameCore::instance.activeMenuTab.tabType
                                = OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
                        }
                        DAT_00ec082c::instance = 3;
                        DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK;
                    }
                    break;
                case -100:
                    if ((char)INT_00eb0e44::instance == '\0') {
                        if (1 < DAT_00ec082c::instance) {
                            DAT_00ec082c::instance = 2;
                            DAT_GameCore::instance.activeMenuTab.tabType
                                = (OpenSHC::UI::Enums::BuildingsAndStatusMenuTabTypeInt)2;
                        }
                        DAT_00ec082c::instance = 0;
                        DAT_GameCore::instance.activeMenuTab.tabType = ((BuildingsAndStatusMenuTabType)0);
                    }
                    break;
                case -10:
                    break;
                case -2:
                    param_1 = 0;
                default:
                    *(char*)&INT_00eb0e44::instance = 0;
                    DAT_FinalResultsOrderByColumn::instance = param_1;
                    break;
                case -1:
                    if ((char)INT_00eb0e44::instance == '\0') {
                        INT_00ed279c::instance = 1;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                        DAT_WindowAndDirectDraw::instance.resolutionY, (ushort)((int)(COL_BLACK::instance.shortValue)));
                    *(char*)&INT_00eb0e44::instance = 0;
                }
            }
        }

    }
}
}
