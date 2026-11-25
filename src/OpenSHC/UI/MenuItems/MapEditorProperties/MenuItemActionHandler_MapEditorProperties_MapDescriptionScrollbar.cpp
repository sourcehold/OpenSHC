#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/INT_00b95b74.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorProperties {

            // FUNCTION: STRONGHOLDCRUSADER 0x0042EE80
            void MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
                int unused, int scrollbarEvent, int* minValue, int* maxValue, int* currentValue)
            {
                // Only a multiplayer map has the description box.
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                    return;
                }
                // The text scrolls in steps of 14, up to its height less the 231 the box shows.
                switch (scrollbarEvent) {
                case 1:
                    *minValue = 0;
                    *maxValue = INT_00b95b74::instance - 231;
                    *currentValue = 0;
                    return;
                case 2:
                case 3:
                    DAT_00b960f4::instance = *currentValue;
                    return;
                case 4:
                    *minValue = 0;
                    *maxValue = INT_00b95b74::instance - 231;
                    *currentValue = DAT_00b960f4::instance;
                    return;
                case 7:
                    // A click on the track beside the thumb moves the text by 252, 18 steps of 14.
                    *currentValue = 252;
                    return;
                case 5:
                    if (DAT_00b960f4::instance > 0) {
                        DAT_00b960f4::instance -= 14;
                    }
                    if (DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                    }
                    *currentValue = DAT_00b960f4::instance;
                    return;
                case 6:
                    if (DAT_00b960f4::instance < INT_00b95b74::instance - 231) {
                        DAT_00b960f4::instance += 14;
                        if (DAT_00b960f4::instance > INT_00b95b74::instance - 231) {
                            DAT_00b960f4::instance = INT_00b95b74::instance - 231;
                        }
                    }
                    *currentValue = DAT_00b960f4::instance;
                    return;
                }
            }

        }
    }
}
}
