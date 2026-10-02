#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::UI::Enums::MenuViewType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00463A00
        BOOLEnum AlphaAndButtonSurface::SelectUnitAndOpenStatusMenu(int unitIndex)
        {
            if ((((0 < unitIndex)
                     && (DAT_UnitsState::instance.units[unitIndex].owner
                         == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                    && (DAT_UnitsState::instance.units[unitIndex].isSelectable_OR_matchTime == 0))
                && (((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                         && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                    && ((DAT_GameCore::instance.gamePausedLogical == 0
                        && (DAT_UnitsState::instance.units[unitIndex].unitType
                            != OpenSHC::Map::Units::UT_S_TOWER)))))) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x46;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                DAT_BuildingsState::instance.newSelectedUnitID = unitIndex;
                DAT_BuildingsState::instance.newSelectedBuildingID = 0;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
