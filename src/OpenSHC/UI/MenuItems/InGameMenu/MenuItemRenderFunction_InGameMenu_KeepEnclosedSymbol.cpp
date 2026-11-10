#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B65A0
        void InGameMenu::MenuItemRenderFunction_InGameMenu_KeepEnclosedSymbol(int unused, ...)
        {
            BOOLEnum const keepEnclosed = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::checkKeepEnclosed,
                DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
            if (keepEnclosed != DAT_MiniMapDefinedData::instance.cachedKeepEnclosed) {
                DAT_GameCore::instance.countdown = 2;
            }
            DAT_MiniMapDefinedData::instance.cachedKeepEnclosed = keepEnclosed;
            if (!keepEnclosed) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            DAT_ButtonUnknownZero::instance = FALSE;
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
