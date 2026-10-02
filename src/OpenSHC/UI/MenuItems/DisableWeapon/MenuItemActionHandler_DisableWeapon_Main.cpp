#include "../DisableWeapon.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BB740
        void DisableWeapon::MenuItemActionHandler_DisableWeapon_Main(int param_1, ...)
        {
            if (param_1 == 0) {
                DAT_MapPropertiesState::instance.SEC_XbowProducible_save
                    = DAT_MapPropertiesState::instance.SEC_XbowProducible_save ^ 1;
            }
            if (param_1 == 1) {
                DAT_MapPropertiesState::instance.SEC_PikeProducible_save
                    = DAT_MapPropertiesState::instance.SEC_PikeProducible_save ^ 1;
            }
            if (param_1 == 2) {
                DAT_MapPropertiesState::instance.SEC_SwordProducible_save
                    = DAT_MapPropertiesState::instance.SEC_SwordProducible_save ^ 1;
            }
            if (param_1 == 3) {
                DAT_MapPropertiesState::instance.SEC_BowProducible_save
                    = DAT_MapPropertiesState::instance.SEC_BowProducible_save ^ 1;
            }
            if (param_1 == 4) {
                DAT_MapPropertiesState::instance.SEC_SpearProducible_save
                    = DAT_MapPropertiesState::instance.SEC_SpearProducible_save ^ 1;
            }
            if (param_1 == 5) {
                DAT_MapPropertiesState::instance.SEC_MaceProducible_save
                    = DAT_MapPropertiesState::instance.SEC_MaceProducible_save ^ 1;
            }
            if (param_1 == -3) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
            }
        }

    }
}
}
