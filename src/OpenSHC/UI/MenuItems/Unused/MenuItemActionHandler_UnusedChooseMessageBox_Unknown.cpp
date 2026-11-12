#include "../Unused.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BF720
        void Unused::MenuItemActionHandler_UnusedChooseMessageBox_Unknown(int row, ...)
        {
            DWORD const currentTime = timeGetTime();
            int const absoluteIndex = DAT_MapPropertiesState::instance.offset + row;
            if (absoluteIndex < (int)DAT_MapPropertiesState::instance.total) {
                DAT_MapPropertiesState::instance.indexStored = row;
                DAT_MapPropertiesState::instance.value
                    = DAT_MapPropertiesState::instance.unknownArray_01[absoluteIndex];
                DAT_MapPropertiesState::instance.selectedAbsoluteIndex = absoluteIndex;
                DAT_MapPropertiesState::instance.selectionTime = currentTime;
            }
        }

    }
}
}
