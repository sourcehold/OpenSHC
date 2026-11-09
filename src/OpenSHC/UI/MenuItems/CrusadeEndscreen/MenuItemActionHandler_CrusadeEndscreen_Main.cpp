#include "../CrusadeEndscreen.func.hpp"

#include "OpenSHC/UI/MenuItems/SelectCrusade.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Game/TrailTypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::TrailType;
        using Game::TrailTypeInt;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9230
        void CrusadeEndscreen::MenuItemActionHandler_CrusadeEndscreen_Main(int param_1, ...)
        {
            if (param_1 != 10) {
                return;
            }

            TrailTypeInt const trailType = DAT_GameCore::instance.currentTrailType;
            if (trailType == Game::TT_EXTREME) {
                MACRO_CALL(UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(4);
                return;
            }
            if (trailType == Game::TT_WARCHEST) {
                MACRO_CALL(UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(3);
                return;
            }
            MACRO_CALL(UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(1);
        }

    }
}
}
