#include "../TriggerInvasion.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BBD90
        void TriggerInvasion::MenuItemActionHandler_TriggerInvasion_Main(int param_1, ...)
        {
            int value;
            int maximum;
            int iVar1;
            iVar1 = 0;
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sumInvasionEventUnitCount, DAT_MapPropertiesState::ptr)();
            value = DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType[param_1];
            maximum = (value - DAT_MapPropertiesState::instance.DAT_InvasionEventItemUnitCountSum) + 500;
            if (DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[param_1] < maximum) {
                maximum = DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[param_1];
            }
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                maximum, value,
                (undefined*)((int)(

                    (DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType + param_1))),
                (void*)MACRO_CALL(Global_Func::DoNothing));
            switch (param_1) {
            case 0:
                iVar1 = 0x5b;
                break;
            case 1:
                iVar1 = 0x5c;
                break;
            case 2:
                iVar1 = 0x5d;
                break;
            case 3:
                iVar1 = 0x5e;
                break;
            case 4:
                iVar1 = 0x5f;
                break;
            case 5:
                iVar1 = 0x60;
                break;
            case 6:
                iVar1 = 0x61;
                break;
            case 7:
                iVar1 = 0x62;
                break;
            case 8:
                iVar1 = 99;
                break;
            case 9:
                iVar1 = 0x9d;
                break;
            case 10:
                iVar1 = 0x9e;
                break;
            case 0xb:
                iVar1 = 0x9f;
                break;
            case 0xc:
                iVar1 = 0xa0;
                break;
            case 0xd:
                iVar1 = 0xa1;
                break;
            case 0xe:
                iVar1 = 0xa2;
                break;
            case 0xf:
                iVar1 = 0xaa;
                break;
            case 0x10:
                iVar1 = 0xd5;
                break;
            case 0x11:
                iVar1 = 0xd6;
                break;
            case 0x12:
                iVar1 = 0xd7;
                break;
            case 0x13:
                iVar1 = 0xd8;
                break;
            case 0x14:
                iVar1 = 0xd9;
                break;
            case 0x15:
                iVar1 = 0xda;
                break;
            case 0x16:
                iVar1 = 0xdb;
                break;
            case 0x17:
                iVar1 = 0xdc;
            }
            DAT_MenuModalComposition2::instance.textGroup = 199;
            DAT_MenuModalComposition2::instance.textIndex = iVar1;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_OVERLAY_SLIDER, (int)(DAT_ButtonX::instance + -0x3e),
                (int)(DAT_ButtonY::instance + 0x19));
            return;
        }

    }
}
}
