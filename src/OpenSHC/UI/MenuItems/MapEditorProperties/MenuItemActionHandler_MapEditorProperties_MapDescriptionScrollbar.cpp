#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042EE80
        void MapEditorProperties::MenuItemActionHandler_MapEditorProperties_MapDescriptionScrollbar(
            int param_1, int param_2, int* minValue, int* maxValue, int* currentValue)
        {
            int iVar1;
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti != 0) {
                switch (param_2) {
                case 1:
                    *minValue = 0;
                    *maxValue = DAT_00b95b74::instance + -0xe7;
                    *currentValue = 0;
                    return;
                case 2:
                case 3:
                    DAT_00b960f4::instance = *currentValue;
                    return;
                case 4:
                    *minValue = 0;
                    *maxValue = DAT_00b95b74::instance + -0xe7;
                    *currentValue = DAT_00b960f4::instance;
                    return;
                case 5:
                    if (0 < DAT_00b960f4::instance) {
                        DAT_00b960f4::instance = DAT_00b960f4::instance + -0xe;
                    }
                    if (DAT_00b960f4::instance < 0) {
                        DAT_00b960f4::instance = 0;
                    }
                    *currentValue = DAT_00b960f4::instance;
                    return;
                case 6:
                    iVar1 = DAT_00b95b74::instance + -0xe7;
                    if ((DAT_00b960f4::instance < iVar1)
                        && (DAT_00b960f4::instance = DAT_00b960f4::instance + 0xe, iVar1 < DAT_00b960f4::instance)) {
                        DAT_00b960f4::instance = iVar1;
                    }
                    *currentValue = DAT_00b960f4::instance;
                    break;
                case 7:
                    *currentValue = 0xfc;
                }
            }
        }

    }
}
}
