#include "../NewEventAction.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004C0860
        void NewEventAction::MenuItemRenderFunction_NewEventAction_Main(int param_1, ...)
        {
            int iVar1;
            int textNumInGroup;
            int iVar2;
            iVar2 = -1;
            DAT_ButtonUnknownZero::instance = 0;
            iVar1 = param_1;
            switch (param_1) {
            case 0x25:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                return;
            case 0x26:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 0x1b) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1 + 2);
                }
                break;
            case 0x27:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 0x1a) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1 + 1);
                }
                break;
            case 0x28:
                if (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType
                    == 2) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
                }
                break;
            default:
                DAT_ButtonUnknownZero::instance = 0;
                return;
            case 0xb1:
            case 0xb2:
            case 0xb3:
            case 0xb4:
            case 0xb5:
            case 0xb6:
            case 0xb7:
            case 0xb8:
            case 0xb9:
            case 0xba:
            case 0xbb:
                iVar1 = param_1 + -0x15;
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x85:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8a:
            case 0x8b:
            case 0x8c:
            case 0x8d:
            case 0x8e:
            case 0x8f:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
            case 0x95:
            case 0x96:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9a:
            case 0x9b:
                if (param_1 == 0x94) {
                    iVar2 = 0;
                    textNumInGroup = 0x92;
                } else {
                    textNumInGroup = param_1;
                    if (param_1 == 0x92) {
                        iVar2 = 2;
                    }
                }
                if (iVar1 + -0x80
                    == DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.ScenarioEventType) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup, (int)((int)(DAT_ButtonX::instance + 0xe)),
                        (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE);
                    if (-1 < iVar2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(" - ", (int)((int)(DAT_ButtonX::instance + 0x14)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 0x80,
                            (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x17
                                + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 3)));
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (((*(int*)&DAT_MapPropertiesState::instance.padding_0x145cc[0]) != 0)
                        && ((*(int*)&DAT_MapPropertiesState::instance.padding_0x145cc[0])
                            = (*(int*)&DAT_MapPropertiesState::instance.padding_0x145cc[0]) + -1,
                            (*(int*)&DAT_MapPropertiesState::instance.padding_0x145cc[0]) == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::setExtraActiveModalDialog,
                            DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_OVERLAY_SLIDER,
                            (int)((int)(DAT_MapPropertiesState::instance.field131_0x145d0)),
                            (int)((int)(DAT_MapPropertiesState::instance.field132_0x145d4)));
                    }
                    switch (param_1) {
                    case 0x84:
                    case 0x8b:
                    case 0x91:
                    case 0x92:
                    case 0x94:
                    case 0xb3:
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData,
                            (int)((int)(DAT_ButtonW::instance + -0xe + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12, FALSE,
                            0);
                        return;
                    default:
                        return;
                    case 0xb2:
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
                            (int)((int)(DAT_ButtonW::instance + -0xe + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12, FALSE,
                            0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_MapPropertiesState::instance
                                .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                .data.scenario.actionData,
                            (int)((int)(DAT_ButtonW::instance + -0x1c + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xccfaff, 0x12, FALSE,
                            0);
                    }
                }
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup, (int)((int)(DAT_ButtonX::instance + 0xe)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, FALSE);
                if (iVar2 < 0) {}
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " - ", (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 0x80,
                    (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x17 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 3)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_ButtonUnknownZero::instance = 1;
        }

    }
}
}
