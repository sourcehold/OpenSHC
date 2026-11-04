#include "../NewEventCondition.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004C01B0
        void NewEventCondition::MenuItemRenderFunction_NewEventCondition_Main(int param_1, ...)
        {
            DAT_ButtonUnknownZero::instance = 0;
            if (5000 < param_1) {
                return;
            }
            int iVar1;
            switch (param_1) {
            case -1:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .header.month
                            + 12,
                        (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                        OpenSHC::Text::TTA_CENTER, 12775659, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .header.month
                            + 12,
                        (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                }
                break;
            case 126:
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 15)
                    == '\0') {
                    param_1 = 127;
                }
            case 19:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                return;
            case 104:
                if (*(short*)((int)&DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data
                        + 8)
                    != 0) {
                    param_1 = 105;
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                return;
            case 209: {
                int iVar3 = 0;
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 19)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 31)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 35)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 39)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 43)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 83)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 95)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 99)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 103)
                    != '\0') {
                    iVar3 = 1;
                }
                if (*(char*)((int)&DAT_MapPropertiesState::instance
                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                 .data
                        + 107)
                        == '\0'
                    && iVar3 == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
            }
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
            case 208: {
                iVar1 = param_1 - 64;
                goto switchD_004c01f4_caseD_6a;
            }
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
            case 125: {
                iVar1 = param_1;
            switchD_004c01f4_caseD_6a:
                DAT_ButtonCurrentlyInteracting::instance
                    = (BOOLEnum)(DAT_MapPropertiesState::instance.invasionTroopIndex == iVar1 - 106);
                uint uVar2 = 12775659;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    uVar2 = OpenSHC::Rendering::Colors::COL_CCFAFF;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (param_1 == 111 || param_1 == 112 || param_1 == 113 || param_1 == 123) {
                    param_1 = 113;
                }
                if (*(char*)((int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags
                        + DAT_MapPropertiesState::instance.currentEventID * 228 + iVar1 * 4 + 511)
                    != '\0') {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1, (int)(DAT_ButtonX::instance + 5),
                        (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, uVar2, 18, FALSE);
                    if (DAT_MissionAestheticsDefinedData::instance.unknown3[iVar1 + 862] == 0) {
                        return;
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionMinValue[iVar1 + 14] == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                            (int)(DAT_MissionAestheticsDefinedData::instance.EventConditionOptionTextOffsets[(
                                char)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                                + DAT_MapPropertiesState::instance.currentEventID * 114 + 255]]),
                            (int)(DAT_ButtonX::instance + 14), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_LEFT, uVar2, 18, TRUE);
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.EventConditionMinValue[iVar1 + 14] == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                            (int)(DAT_MissionAestheticsDefinedData::instance.field_0x170[(
                                char)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                                + DAT_MapPropertiesState::instance.currentEventID * 114 + 255]]),
                            (int)(DAT_ButtonX::instance + 14), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_LEFT, uVar2, 18, TRUE);
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                        (int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                            + DAT_MapPropertiesState::instance.currentEventID * 114 + 254]
                            * DAT_MissionAestheticsDefinedData::instance.unknown3[iVar1 + 902],
                        (int)(DAT_ButtonW::instance - 8 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                        OpenSHC::Text::TTA_RIGHT, uVar2, 18, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1, (int)(DAT_ButtonX::instance + 5),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, 8355711, 18, FALSE);
                return;
            }
            case 1001: {
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            }
            case 1000: {
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            }
            case 2000: {
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            }
            default: {
            switchD_004c01f4_caseD_0:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                return;
            }
            case 2002: {
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                        (int)(DAT_MissionAestheticsDefinedData::instance.EventConditionOptionTextOffsets[*(
                            char*)(&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)]),
                        (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                        OpenSHC::Text::TTA_CENTER, 12775659, 18, FALSE);
                }
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    != 2) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                    (int)(DAT_MissionAestheticsDefinedData::instance
                            .field_0x170[*(char*)(&DAT_MapPropertiesState::instance
                                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                      .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 14)]),
                    (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 8),
                    OpenSHC::Text::TTA_CENTER, 12775659, 18, FALSE);
                return;
                return;
            }
            case 2001:
                if (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionParamKind[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                    return;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), (ushort)(COL_BLUE::instance.shortValue),
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonW::instance + DAT_ButtonX::instance),
                        (int)(DAT_ButtonH::instance + DAT_ButtonY::instance), OpenSHC::UI::Enums::RBERL_SLIGHT);
                }
                return;
            }
        }

    }
}
}
