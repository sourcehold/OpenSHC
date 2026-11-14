#include "../NewEventCondition.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UnknownTime_01.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9620
        void NewEventCondition::MenuItemActionHandler_NewEventCondition_Main(int param_1, ...)
        {
            ushort* puVar1;
            short* destination;
            byte* pbVar2;
            short sVar3;
            byte(*pabVar4)[100];
            DWORD DVar5;
            char* pcVar6;
            int iVar7;
            int iVar8;
            if (param_1 < 1001) {
                if (param_1 == 1000) {
                    sVar3 = *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12);
                    if (DAT_MissionAestheticsDefinedData::instance
                            .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        < (int)sVar3) {
                        *(short*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12) = sVar3 - 1;
                        return;
                    }
                } else {
                    switch (param_1) {
                    case 19:
                        *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                           .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                           .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 15) = 0;
                        return;
                    case 37:
                        if (*(char*)((int)&DAT_MapPropertiesState::instance
                                         .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                         .data
                                + 15)
                            != '\0') {
                            iVar8 = 1;
                            pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                + 19);
                            while (*pcVar6 == '\0') {
                                ++iVar8;
                                pcVar6 += 4;
                                if (39 < iVar8) {
                                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT, FALSE);
                                    return;
                                }
                            }
                            *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                + 15) = 0;
                        }
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NEW_EVENT, FALSE);
                        return;
                    case 104:
                        puVar1 = (ushort*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                            + 8);
                        *puVar1 ^= 1;
                        return;
                    case 190:
                    case 191:
                    case 192:
                    case 193:
                    case 194:
                    case 195:
                    case 196:
                    case 197:
                    case 198:
                    case 199:
                    case 200:
                    case 201:
                    case 202:
                    case 203:
                    case 204:
                    case 205:
                    case 206:
                    case 207:
                    case 208:
                    case 209:
                        param_1 -= 64;
                    case 106:
                    case 107:
                    case 108:
                    case 109:
                    case 110:
                    case 111:
                    case 112:
                    case 113:
                    case 114:
                    case 115:
                    case 116:
                    case 117:
                    case 118:
                    case 119:
                    case 120:
                    case 121:
                    case 122:
                    case 123:
                    case 124:
                    case 125:
                        DAT_MapPropertiesState::instance.invasionTroopIndex = param_1 - 106;
                        *(undefined1*)((int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags
                            + DAT_MapPropertiesState::instance.currentEventID * 228 + param_1 * 4 + 511) = 1;
                        DAT_UnknownTime_01::instance = 0;
                        if ((int)*(short*)((int)&DAT_MapPropertiesState::instance
                                               .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                               .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12)
                            < DAT_MissionAestheticsDefinedData::instance
                                .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                            *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12)
                                = (short)DAT_MissionAestheticsDefinedData::instance
                                      .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex];
                        }
                        if (DAT_MissionAestheticsDefinedData::instance
                                .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            != 0) {
                            destination = (short*)((int)&DAT_MapPropertiesState::instance
                                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                       .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12);
                            MACRO_CALL_MEMBER(
                                UI::MenuModalComposition_Func::setSliderParameters2, DAT_MenuModalComposition2::ptr)(
                                DAT_MissionAestheticsDefinedData::instance
                                    .EventConditionMinValue[DAT_MapPropertiesState::instance.invasionTroopIndex],
                                (dword)((int)(DAT_MissionAestheticsDefinedData::instance
                                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex])),
                                (dword)((int)((int)*destination)), (dword)((int)(destination)),
                                MACRO_CALL(UI::Helpers_Func::CaptureCurrentTimeToUnknownTime01));
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                                DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_OVERLAY_SLIDER,
                                (int)((int)(DAT_ButtonX::instance + 58)), (int)((int)(DAT_ButtonY::instance + 28)));
                            return;
                        }
                    }
                }
            } else if (param_1 < 2003) {
                if (param_1 < 2001) {
                    if (param_1 == 1001) {
                        sVar3 = *(short*)((int)&DAT_MapPropertiesState::instance
                                              .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                              .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12);
                        if ((int)sVar3 < DAT_MissionAestheticsDefinedData::instance
                                .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]) {
                            *(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12) = sVar3 + 1;
                            return;
                        }
                    } else if (param_1 == 2000) {
                        iVar8 = 0;
                        if (DAT_MissionAestheticsDefinedData::instance
                                .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            != 0) {
                            if (DAT_MissionAestheticsDefinedData::instance
                                    .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                == 1) {
                                iVar7
                                    = (int)*(char*)((int)&DAT_MapPropertiesState::instance
                                                        .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                        .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14);
                                pbVar2 = (byte*)((int)&DAT_MapPropertiesState::instance
                                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                     .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14);
                                if (*(int*)DAT_MissionAestheticsDefinedData::instance
                                        .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                    != iVar7) {
                                    pabVar4 = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                    do {
                                        pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                        ++iVar8;
                                    } while (*(int*)*pabVar4 != iVar7);
                                }
                                if (iVar8 - 1 < 0) {
                                    pabVar4 = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                    iVar8 = 0;
                                    do {
                                        iVar7 = iVar8;
                                        if (*(int*)*pabVar4 == -1) {
                                            *pbVar2
                                                = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                                      [DAT_MapPropertiesState::instance.invasionTroopIndex - 1]
                                                      [iVar7 * 4 + 96];
                                            goto LAB_004b98bd;
                                        }
                                        pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                        iVar8 = iVar7 + 1;
                                    } while (iVar7 + 1 < 100);
                                    *pbVar2 = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                                  [DAT_MapPropertiesState::instance.invasionTroopIndex][iVar7 * 4 + 4];
                                } else {
                                    *pbVar2
                                        = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                              [DAT_MapPropertiesState::instance.invasionTroopIndex - 1][iVar8 * 4 + 96];
                                }
                            }
                        LAB_004b98bd:
                            if (DAT_MissionAestheticsDefinedData::instance
                                    .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                == 2) {
                                pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                     .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14);
                                --*pcVar6;
                                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)
                                    < '\0') {
                                    *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                       .data
                                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14) = 4;
                                }
                            }
                        }
                    }
                } else {
                    iVar8 = 0;
                    if (DAT_MissionAestheticsDefinedData::instance
                            .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        != 0) {
                        if (DAT_MissionAestheticsDefinedData::instance
                                .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            == 1) {
                            iVar7 = (int)*(char*)((int)&DAT_MapPropertiesState::instance
                                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                      .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14);
                            if (!iVar7) {
                                *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                   .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                   .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14) = 10;
                                iVar7 = 10;
                            }
                            if (*(int*)DAT_MissionAestheticsDefinedData::instance
                                    .EventConditionOptionValues[DAT_MapPropertiesState::instance.invasionTroopIndex]
                                != iVar7) {
                                pabVar4 = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex;
                                do {
                                    pabVar4 = (byte(*)[100])(*pabVar4 + 4);
                                    ++iVar8;
                                } while (*(int*)*pabVar4 != iVar7);
                            }
                            if (*(int*)(DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                            [DAT_MapPropertiesState::instance.invasionTroopIndex]
                                    + iVar8 * 4 + 4)
                                == -1) {
                                *(byte*)((int)&DAT_MapPropertiesState::instance
                                             .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                             .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)
                                    = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                          [DAT_MapPropertiesState::instance.invasionTroopIndex][0];
                            } else {
                                *(byte*)((int)&DAT_MapPropertiesState::instance
                                             .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                             .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)
                                    = DAT_MissionAestheticsDefinedData::instance.EventConditionOptionValues
                                          [DAT_MapPropertiesState::instance.invasionTroopIndex][iVar8 * 4 + 4];
                            }
                        }
                        if (DAT_MissionAestheticsDefinedData::instance
                                .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                            == 2) {
                            pcVar6 = (char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14);
                            *pcVar6 += '\x01';
                            if ('\x04' < *(char*)((int)&DAT_MapPropertiesState::instance
                                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                      .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)) {
                                *(undefined1*)((int)&DAT_MapPropertiesState::instance
                                                   .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                   .data
                                    + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14) = 0;
                                return;
                            }
                        }
                    }
                }
            } else {
                switch (param_1) {
                case 5190:
                case 5191:
                case 5192:
                case 5193:
                case 5194:
                case 5195:
                case 5196:
                case 5197:
                case 5198:
                case 5199:
                case 5200:
                case 5201:
                case 5202:
                case 5203:
                case 5204:
                case 5205:
                case 5206:
                case 5207:
                case 5208:
                case 5209:
                    param_1 -= 64;
                case 5106:
                case 5107:
                case 5108:
                case 5109:
                case 5110:
                case 5111:
                case 5112:
                case 5113:
                case 5114:
                case 5115:
                case 5116:
                case 5117:
                case 5118:
                case 5119:
                case 5120:
                case 5121:
                case 5122:
                case 5123:
                case 5124:
                case 5125:
                    if ((DAT_MenuModalComposition2::instance.activeModalDialogID == UI::Enums::MMT_NONE)
                        && ((DVar5 = timeGetTime(),
                            1000 < DVar5 - DAT_UnknownTime_01::instance || (!DAT_UnknownTime_01::instance)))) {
                        DAT_UnknownTime_01::instance = 0;
                        ((char*)&DAT_UnitsState::instance.units[2491]
                            + 995)[(DAT_MapPropertiesState::instance.currentEventID * 57 + param_1) * 4] = 0;
                        return;
                    }
                }
            }
        }

    }
}
}
