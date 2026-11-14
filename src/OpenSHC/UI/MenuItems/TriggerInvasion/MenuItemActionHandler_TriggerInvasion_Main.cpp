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

        // FUNCTION: STRONGHOLDCRUSADER 0x004bbd90
        void __cdecl TriggerInvasion::MenuItemActionHandler_TriggerInvasion_Main(int param_1, ...)
        {
            int textIndex = 0;
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sumInvasionEventUnitCount, DAT_MapPropertiesState::ptr)();
            int* countPtr = &DAT_MapPropertiesState::instance.invasionEventContent.unitCountsPerUnitType[param_1];
            // the slider maximum is a min() of the unit limit and the room left below 500 units: written as the
            // expanded macro (both operands repeated), which gives the original's register choice
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[param_1]
                        < *countPtr - (int)DAT_MapPropertiesState::instance.DAT_InvasionEventItemUnitCountSum + 500
                    ? DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[param_1]
                    : *countPtr - (int)DAT_MapPropertiesState::instance.DAT_InvasionEventItemUnitCountSum + 500,
                *countPtr, (undefined*)countPtr,
                (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(Global_Func::DoNothing));

            switch (param_1) {
            case 0:
                textIndex = 91;
                break;
            case 1:
                textIndex = 92;
                break;
            case 2:
                textIndex = 93;
                break;
            case 3:
                textIndex = 94;
                break;
            case 4:
                textIndex = 95;
                break;
            case 5:
                textIndex = 96;
                break;
            case 6:
                textIndex = 97;
                break;
            case 7:
                textIndex = 98;
                break;
            case 8:
                textIndex = 99;
                break;
            case 9:
                textIndex = 157;
                break;
            case 10:
                textIndex = 158;
                break;
            case 11:
                textIndex = 159;
                break;
            case 12:
                textIndex = 160;
                break;
            case 13:
                textIndex = 161;
                break;
            case 14:
                textIndex = 162;
                break;
            case 15:
                textIndex = 170;
                break;
            case 16:
                textIndex = 213;
                break;
            case 17:
                textIndex = 214;
                break;
            case 18:
                textIndex = 215;
                break;
            case 19:
                textIndex = 216;
                break;
            case 20:
                textIndex = 217;
                break;
            case 21:
                textIndex = 218;
                break;
            case 22:
                textIndex = 219;
                break;
            case 23:
                textIndex = 220;
                break;
            }

            DAT_MenuModalComposition2::instance.textGroup = 199;
            DAT_MenuModalComposition2::instance.textIndex = textIndex;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 62, DAT_ButtonY::instance + 25);
        }

    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
