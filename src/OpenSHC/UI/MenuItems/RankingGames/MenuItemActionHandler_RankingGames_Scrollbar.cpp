#include "../RankingGames.func.hpp"

#include "OpenSHC/Globals/INT_00eb9b60.hpp"
#include "OpenSHC/Globals/INT_00ed3120.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9B30
        void RankingGames::MenuItemActionHandler_RankingGames_Scrollbar(
            int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
        {
            // eight games fit in the list
            switch (scrollbarEvent) {
            case 1:
                *minValue = 0;
                *maxValue = 1;
                *currentValue = 0;
                return;
            case 2:
            case 3:
                // stores only on a change, as the original does (plain store: quick_diff 0.8679 -> 0.7308)
                if (*currentValue != INT_00ed3120::instance) {
                    INT_00ed3120::instance = *currentValue;
                }
                return;
            case 4: {
                *minValue = 0;
                // one read of the count (reading it again for the test: quick_diff 0.8679 -> 0.7593)
                int const lastOffset = INT_00eb9b60::instance - 8;
                *maxValue = lastOffset;
                if (lastOffset < 0) {
                    *maxValue = 0;
                }
                // stores only on a change, as the original does (plain store: quick_diff 0.8679 -> 0.6538)
                if (*currentValue != INT_00ed3120::instance) {
                    *currentValue = INT_00ed3120::instance;
                }
                return;
            }
            case 7:
                // a click on the track pages by 6 of the 8 games
                *currentValue = 6;
                return;
            case 5:
                if (INT_00ed3120::instance > 0) {
                    --INT_00ed3120::instance;
                }
                *currentValue = INT_00ed3120::instance;
                return;
            case 6:
                if (INT_00ed3120::instance < INT_00eb9b60::instance - 8) {
                    ++INT_00ed3120::instance;
                }
                *currentValue = INT_00ed3120::instance;
                return;
            }
        }

    }
}
}
