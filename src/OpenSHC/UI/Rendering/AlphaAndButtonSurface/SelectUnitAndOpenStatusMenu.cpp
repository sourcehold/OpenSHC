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

        using Game::GameMode2;
        using Map::Units::UnitType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00463A00
        BOOLEnum AlphaAndButtonSurface::SelectUnitAndOpenStatusMenu(int unitIndex)
        {
            if (0 < unitIndex
                && DAT_UnitsState::instance.units[unitIndex].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_UnitsState::instance.units[unitIndex].isSelectable_OR_matchTime == 0
                && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT && !DAT_GameCore::instance.gamePausedLogical
                && DAT_UnitsState::instance.units[unitIndex].unitType != Map::Units::UT_S_TOWER) {
                MACRO_CALL_MEMBER(
                    Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, DAT_TextEditorState::ptr)();
                DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x46;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                DAT_BuildingsState::instance.newSelectedUnitID = unitIndex;
                DAT_BuildingsState::instance.newSelectedBuildingID = 0;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
