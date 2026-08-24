#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00ed2788.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::MenuModalType;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004D9D60
void UI::MenuItemActionHandler_DeleteGameRecord_Main(int param_1, ...)

{
    if (param_1 == 0x16) {
        MACRO_CALL(OpenSHC::Game::Skirmish_Func::SkirmishLeaderboard_DeleteEntry)(DAT_00ed2788::instance);
        MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
    }
    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
        OpenSHC::UI::Enums::MMT_NONE, FALSE);
    return;
}

}
