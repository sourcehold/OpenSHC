#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005360A0
        BOOLEnum UnitsState::isUnitShortcutAvailable(int unitHotKeyNumber)
        {
            if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILD_MENU) {
                return FALSE;
            }
            if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                && DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD) {
                return FALSE;
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].isSelected == 0) {
                    for (int i = 0; i < 2500; ++i) {
                        /* unitID is listed in this hotkey unit list and not selected */
                        if (DAT_GameState::instance.hotkeyTribes[unitHotKeyNumber].units[i].id == unitID) {
                            return FALSE;
                        }
                    }
                    continue;
                }
                int _isListed = 0;
                for (int i = 0; i < 2500; ++i) {
                    if (DAT_GameState::instance.hotkeyTribes[unitHotKeyNumber].units[i].id == unitID) {
                        _isListed = 1;
                    }
                }
                /* unitID is listed in this hotkey unit list and is selected */
                if (_isListed == 0) {
                    return FALSE;
                }
            }
            /* There is no unitID to be found in a normal non-dead state that is selectable */
            return TRUE;
        }

    }
}
}
