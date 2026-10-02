#include "../Unused.func.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BF720
        void Unused::MenuItemActionHandler_UnusedChooseMessageBox_Unknown(int param_1, ...)
        {
            DWORD DVar1;
            int iVar2;
            DVar1 = timeGetTime();
            iVar2 = DAT_MapPropertiesState::instance.offset + param_1;
            if (iVar2 < DAT_MapPropertiesState::instance.total) {
                DAT_MapPropertiesState::instance.indexStored = param_1;
                DAT_MapPropertiesState::instance.value = DAT_MapPropertiesState::instance.unknownArray_01[iVar2];
                DAT_MapPropertiesState::instance.selectedAbsoluteIndex = iVar2;
                DAT_MapPropertiesState::instance.selectionTime = DVar1;
            }
        }

    }
}
}
