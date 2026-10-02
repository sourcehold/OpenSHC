#include "../NewEventCondition.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004C01B0
        void NewEventCondition::MenuItemRenderFunction_NewEventCondition_Main(int param_1, ...)
        {
            int iVar1;
            uint uVar2;
            DAT_ButtonUnknownZero::instance = 0;
            if (5000 < param_1) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            if (param_1 < 0xd2) {
                if (param_1 != 0xd1) {
                    iVar1 = param_1;
                    switch (param_1) {
                    default:
                        goto switchD_004c01f4_caseD_0;
                    case 0x68:
                        if (*(short*)((int)&DAT_MapPropertiesState::instance
                                          .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                          .data
                                + 8)
                            != 0) {
                            param_1 = 0x69;
                        }
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                        return;
                    case 0x6a:
                    case 0x6b:
                    case 0x6c:
                    case 0x6d:
                    case 0x6e:
                    case 0x6f:
                    case 0x70:
                    case 0x71:
                    case 0x72:
                    case 0x73:
                    case 0x74:
                    case 0x75:
                    case 0x76:
                    case 0x77:
                    case 0x78:
                    case 0x79:
                    case 0x7a:
                    case 0x7b:
                    case 0x7c:
                    case 0x7d:
                    switchD_004c01f4_caseD_6a:
                        DAT_ButtonCurrentlyInteracting::instance
                            = (BOOLEnum)(DAT_MapPropertiesState::instance.invasionTroopIndex == iVar1 + -0x6a);
                        uVar2 = 0xc2f0eb;
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            uVar2 = 0xccfaff;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if ((((param_1 == 0x6f) || (param_1 == 0x70)) || (param_1 == 0x71)) || (param_1 == 0x7b)) {
                            param_1 = 0x71;
                        }
                        if (*(char*)((int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags
                                + DAT_MapPropertiesState::instance.currentEventID * 0xe4 + iVar1 * 4 + 0x1ff)
                            != '\0') {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1, (int)((int)(DAT_ButtonX::instance + 5)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, uVar2, 0x12, FALSE);
                            if (DAT_MissionAestheticsDefinedData::instance.unknown3[iVar1 + 0x35e] == 0) {}
                            if (DAT_MissionAestheticsDefinedData::instance.field1227_0x21c4[iVar1 + 0xe] == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                    (int)((int)(DAT_MissionAestheticsDefinedData::instance.field1235_0x33e4[(
                                        char)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                                        + DAT_MapPropertiesState::instance.currentEventID * 0x72 + 0xff]])),
                                    (int)((int)(DAT_ButtonX::instance + 0xe)), (int)((int)(DAT_ButtonY::instance + 7)),
                                    OpenSHC::Text::TTA_LEFT, uVar2, 0x12, TRUE);
                            }
                            if (DAT_MissionAestheticsDefinedData::instance.field1227_0x21c4[iVar1 + 0xe] == 2) {
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                                    (int)((int)(DAT_MissionAestheticsDefinedData::instance.field92_0x170[(
                                        char)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                                        + DAT_MapPropertiesState::instance.currentEventID * 0x72 + 0xff]])),
                                    (int)((int)(DAT_ButtonX::instance + 0xe)), (int)((int)(DAT_ButtonY::instance + 7)),
                                    OpenSHC::Text::TTA_LEFT, uVar2, 0x12, TRUE);
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                                (int)DAT_MapPropertiesState::instance.buildingAvailabilityRelatedFlags[iVar1 * 2
                                    + DAT_MapPropertiesState::instance.currentEventID * 0x72 + 0xfe]
                                    * DAT_MissionAestheticsDefinedData::instance.unknown3[iVar1 + 0x386],
                                (int)((int)(DAT_ButtonW::instance + -8 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, uVar2, 0x12, FALSE);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1, (int)((int)(DAT_ButtonX::instance + 5)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, 0x7f7f7f, 0x12, FALSE);
                        return;
                    case 0x7e:
                        if (*(char*)((int)&DAT_MapPropertiesState::instance
                                         .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                         .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xf)
                            == '\0') {
                            param_1 = 0x7f;
                        }
                    case 0x13:
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                        return;
                    case 0xbe:
                    case 0xbf:
                    case 0xc0:
                    case 0xc1:
                    case 0xc2:
                    case 0xc3:
                    case 0xc4:
                    case 0xc5:
                    case 0xc6:
                    case 199:
                    case 200:
                    case 0xc9:
                    case 0xca:
                    case 0xcb:
                    case 0xcc:
                    case 0xcd:
                    case 0xce:
                    case 0xcf:
                    case 0xd0:
                        goto switchD_004c01f4_caseD_be;
                    case -1:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                            uVar2 = 0xc2f0eb;
                        } else {
                            uVar2 = 0xccfaff;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MONTHS,
                            DAT_MapPropertiesState::instance
                                    .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                    .header.month
                                + 0xc,
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, uVar2, 0x12, FALSE);
                    }
                }
                if ((*(char*)((int)&DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data
                         + 0x6b)
                        == '\0')
                    && (*(char*)((int)&DAT_MapPropertiesState::instance
                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                     .data
                            + 0x67)
                            == '\0'
                        && (*(char*)((int)&DAT_MapPropertiesState::instance
                                         .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                         .data
                                + 99)
                                == '\0'
                            && (*(char*)((int)&DAT_MapPropertiesState::instance
                                             .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                             .data
                                    + 0x5f)
                                    == '\0'
                                && (*(char*)((int)&DAT_MapPropertiesState::instance
                                                 .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                 .data
                                        + 0x53)
                                        == '\0'
                                    && (*(char*)((int)&DAT_MapPropertiesState::instance
                                                     .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                     .data
                                            + 0x2b)
                                            == '\0'
                                        && (*(char*)((int)&DAT_MapPropertiesState::instance
                                                         .scenarioEvents[DAT_MapPropertiesState::instance
                                                                 .currentEventID]
                                                         .data
                                                + 0x27)
                                                == '\0'
                                            && (*(char*)((int)&DAT_MapPropertiesState::instance
                                                             .scenarioEvents[DAT_MapPropertiesState::instance
                                                                     .currentEventID]
                                                             .data
                                                    + 0x23)
                                                    == '\0'
                                                && (*(char*)((int)&DAT_MapPropertiesState::instance
                                                                 .scenarioEvents[DAT_MapPropertiesState::instance
                                                                         .currentEventID]
                                                                 .data
                                                        + 0x1f)
                                                        == '\0'
                                                    && *(char*)((int)&DAT_MapPropertiesState::instance
                                                                    .scenarioEvents[DAT_MapPropertiesState::instance
                                                                            .currentEventID]
                                                                    .data
                                                           + 0x13)
                                                        == '\0'))))))))) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            switchD_004c01f4_caseD_be:
                iVar1 = param_1 + -0x40;
                goto switchD_004c01f4_caseD_6a;
            }
            if (param_1 < 2000) {
                if (param_1 == 2000) {
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        == 0) {
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                            DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                            (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                            OpenSHC::UI::Enums::RBERL_SLIGHT);
                    }
                } else {
                    if (param_1 != 1000) {
                        if (param_1 != 1001)
                            goto switchD_004c01f4_caseD_0;
                        iVar1 = DAT_MissionAestheticsDefinedData::instance
                                    .field1228_0x2264[DAT_MapPropertiesState::instance.invasionTroopIndex];
                        goto joined_r0x004c072d;
                    }
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1228_0x2264[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        == 0) {
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                            DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                            (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                            OpenSHC::UI::Enums::RBERL_SLIGHT);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_BLUE::instance.shortValue)), OpenSHC::UI::Enums::RBERL_SLIGHT);
            }
            if (param_1 != 2001) {
                if (param_1 == 0x7d2) {
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                            (int)((int)(DAT_MissionAestheticsDefinedData::instance.field1235_0x33e4[*(
                                char*)(&DAT_MapPropertiesState::instance
                                           .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                           .data
                                + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)])),
                            (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE);
                    }
                    if (DAT_MissionAestheticsDefinedData::instance
                            .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        != 2) {}
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO,
                        (int)((int)(DAT_MissionAestheticsDefinedData::instance.field92_0x170[*(
                            char*)(&DAT_MapPropertiesState::instance
                                       .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                       .data
                            + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 0xe)])),
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 8)), OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE);
                }
            switchD_004c01f4_caseD_0:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
            }
            iVar1 = DAT_MissionAestheticsDefinedData::instance
                        .field1230_0x23a4[DAT_MapPropertiesState::instance.invasionTroopIndex];
        joined_r0x004c072d:
            if (iVar1 == 0) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)), OpenSHC::UI::Enums::RBERL_SLIGHT);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                (ushort)((int)(COL_BLUE::instance.shortValue)), OpenSHC::UI::Enums::RBERL_SLIGHT);
        }

    }
}
}
