#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00442F40
        void SinglePlayerMapChoice::MenuItemActionHandler_SingleplayerMapChoice_Scrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            switch (scrollbarEvent) {
            case 1:
                // the list shows 13 rows
                *minValue = 0;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 13;
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 2:
            case 3:
                // unlike 5 and 6, the selected row is chosen again before the offset changes
                if (*currentValue != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset = *currentValue;
                return;
            case 4:
                if (*currentValue != DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                *maxValue = DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 13;
                return;
            case 7:
                // a click on the track pages by 12 of the 13 rows
                *currentValue = 12;
                return;
            case 5:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset > 0) {
                    --DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            case 6:
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber - 13) {
                    ++DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                    MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                            MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                        DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                }
                *currentValue = DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                return;
            }
        }

    }
}
}
