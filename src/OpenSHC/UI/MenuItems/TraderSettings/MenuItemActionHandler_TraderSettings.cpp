#include "../TraderSettings.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BA780
        void TraderSettings::MenuItemActionHandler_TraderSettings(int param_1, ...)
        {
            BOOLEnum* pBVar1;
            if (param_1 < 0) {
                pBVar1 = DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray
                    + *(int*)((int)DAT_MissionAestheticsDefinedData::ptr + (-1 - param_1) * 4 + 0x345c);
                *pBVar1 = *pBVar1 ^ TRUE;
            }
            if (param_1 == 0x25) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            } else if (param_1 == 0x457) {
                pBVar1 = DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray
                    + DAT_MissionAestheticsDefinedData::instance
                          .field1237_0x345c[DAT_MapPropertiesState::instance.indexStored];
                *pBVar1 = *pBVar1 ^ TRUE;
            }
        }

    }
}
}
