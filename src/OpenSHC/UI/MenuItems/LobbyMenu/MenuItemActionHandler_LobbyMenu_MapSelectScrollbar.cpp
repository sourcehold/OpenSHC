#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042B7B0
        void LobbyMenu::MenuItemActionHandler_LobbyMenu_MapSelectScrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            if (DAT_00b960dc::instance != 0 && scrollbarEvent != 1) {
                return;
            }
            switch (scrollbarEvent) {
            case 1:
                // the list shows 8 rows
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 8;
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 2:
            case 3:
                if (*currentValue == DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = *currentValue;
                if (DAT_GameSynchronyState::instance.isHost) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                }
                return;
            case 4:
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 8;
                if (*currentValue == DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    return;
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                if (DAT_GameSynchronyState::instance.isHost) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                }
                return;
            case 7:
                *currentValue = 6;
                return;
            case 5:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset > 0) {
                    --DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    if (DAT_GameSynchronyState::instance.isHost) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 6:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 8) {
                    ++DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    if (DAT_GameSynchronyState::instance.isHost) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                    }
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            }
        }

    }
}
}
