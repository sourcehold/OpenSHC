#include "../SiegeAttackingForceAndStartGoods.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004ba5c0
        void __cdecl SiegeAttackingForceAndStartGoods::MenuItemActionHandler_SiegeAttackingForceAndStartGoods_Main(
            int param_1, ...)
        {
            if (param_1 < 0) {
                int idx = -1 - param_1;
                if (idx < 20) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == 0) {
                        return;
                    }
                } else if (idx < 30) {
                    if (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != 0) {
                        return;
                    }
                }
                DAT_MapPropertiesState::instance.indexStored = idx;
                if (idx < 20) {
                    int resIdx = DAT_MissionAestheticsDefinedData::instance.field_0x345c[idx];
                    int maxVal = DAT_MissionAestheticsDefinedData::instance.field_0x34b4[idx];
                    int* resPtr = &DAT_MapPropertiesState::instance.SEC_StartingResources[resIdx];
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters,
                        DAT_MenuModalComposition2::ptr)(0, maxVal, *resPtr, (undefined*)resPtr,
                        (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex
                        = DAT_MissionAestheticsDefinedData::instance
                              .field_0x3554[DAT_MapPropertiesState::instance.indexStored];
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 37, DAT_ButtonY::instance + 25);
                    return;
                }
                // slider maximum = min(unit limit, room left below 500 points), written as the expanded macro with
                // indexStored re-read each time: that gives the original's register choice
                if (idx < 30) {
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    int* countPtr = &DAT_MapPropertiesState::instance
                                         .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5];
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        DAT_MissionAestheticsDefinedData::instance
                                    .field_0x3554[DAT_MapPropertiesState::instance.indexStored]
                                < *countPtr - (int)DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum + 500
                            ? DAT_MissionAestheticsDefinedData::instance
                                  .field_0x3554[DAT_MapPropertiesState::instance.indexStored]
                            : *countPtr - (int)DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum + 500,
                        *countPtr, (undefined*)countPtr,
                        (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex
                        = DAT_MissionAestheticsDefinedData::instance
                              .InvasionUnitLimits[DAT_MapPropertiesState::instance.indexStored + 4];
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 37, DAT_ButtonY::instance + 25);
                } else {
                    if (idx == 30) {
                        return;
                    }
                    if (idx < 40 || idx >= 50) {
                        return;
                    }
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                    int* countPtr = &DAT_MapPropertiesState::instance
                                         .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5];
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                        (int)DAT_MissionAestheticsDefinedData::instance
                                    .field_0x184[30][11 + DAT_MapPropertiesState::instance.indexStored]
                                < *countPtr - (int)DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum + 500
                            ? (int)DAT_MissionAestheticsDefinedData::instance
                                  .field_0x184[30][11 + DAT_MapPropertiesState::instance.indexStored]
                            : *countPtr - (int)DAT_MapPropertiesState::instance.DAT_MapEditorUnitPointsSum + 500,
                        *countPtr, (undefined*)countPtr,
                        (Util::FunctionTypes::NoArgCallback*)MACRO_CALL(UI::Helpers_Func::SumUnitPoints));
                    DAT_MenuModalComposition2::instance.textIndex
                        = (int)DAT_MissionAestheticsDefinedData::instance
                              .field_0xa64[30][11 + DAT_MapPropertiesState::instance.indexStored];
                    DAT_MenuModalComposition2::instance.textGroup = 199;
                    MACRO_CALL_MEMBER(
                        UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                        UI::Enums::MMT_OVERLAY_SLIDER, DAT_ButtonX::instance - 37, DAT_ButtonY::instance + 25);
                }
            } else if (param_1 == 37) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
            }
        }

    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
