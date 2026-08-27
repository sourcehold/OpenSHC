#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {

using OpenSHC::Game::GameMode2;

// FUNCTION: STRONGHOLDCRUSADER 0x00434230
void UI::MenuItemRenderFunction_BuildMenu_BuildingKeepSubcategoryButton(int param_1, ...)
{
    if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
        DAT_ButtonUnknownZero::instance = 1;
        return;
    }
    DAT_ButtonUnknownZero::instance = 0;
    MACRO_CALL(
        OpenSHC::UI_Func::MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
}

}
