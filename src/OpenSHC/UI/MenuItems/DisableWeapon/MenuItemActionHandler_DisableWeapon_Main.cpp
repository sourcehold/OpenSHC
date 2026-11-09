#include "../DisableWeapon.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BB740
        void DisableWeapon::MenuItemActionHandler_DisableWeapon_Main(int param_1, ...)
        {
            if (!param_1) {
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
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
            }
        }

    }
}
}
