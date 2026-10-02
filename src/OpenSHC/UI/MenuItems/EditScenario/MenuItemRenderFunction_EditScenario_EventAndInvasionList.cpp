#include "../EditScenario.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B8BF0
        void EditScenario::MenuItemRenderFunction_EditScenario_EventAndInvasionList(int param_1, ...)
        {
            byte bVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            BGR24 color;
            bool bVar5;
            TextAlignment TVar6;
            BGR24 BVar7;
            int iVar8;
            BOOLEnum BVar9;
            int iVar10;
            int blendStrength;
            if (DAT_MapPropertiesState::instance.eventsCount <= DAT_MapPropertiesState::instance.field48_0x13560) {
                DAT_MapPropertiesState::instance.field48_0x13560 = DAT_MapPropertiesState::instance.eventsCount + -1;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_MapPropertiesState::instance.field48_0x13560), param_1, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_MapPropertiesState::instance.eventsCount
                <= DAT_MapPropertiesState::instance.field47_0x1355c + param_1) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if ((param_1 == DAT_MapPropertiesState::instance.field48_0x13560)
                || (color = 0xc2f0eb, DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                color = 0xccfaff;
            }
            iVar10 = 0;
            BVar9 = FALSE;
            iVar8 = 0x12;
            BVar7 = 0xccfaff;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar3 = DAT_ButtonY::instance + 4;
            iVar4 = DAT_ButtonX::instance + 8;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_MapPropertiesState::instance .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1] .header.month), iVar4, iVar3, TVar6, BVar7, iVar8, BVar9, iVar10);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_MapPropertiesState::instance
                    .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                    .header.year,
                (int)((int)(DAT_ButtonX::instance + 0x28)), (int)((int)(DAT_ButtonY::instance + 4)),
                OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
            iVar3 = DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .header.tl_type;
            if (iVar3 == 1) {
                iVar10 = 0;
                BVar9 = FALSE;
                iVar8 = 0x12;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonY::instance + 4;
                iVar4 = DAT_ButtonX::instance + 0x50;
                BVar7 = color;
                /*
                  added by script: "Invasion"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0x2e), iVar4, iVar3, TVar6, BVar7, iVar8, BVar9, iVar10);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.scenario.actionData,
                    (int)((int)(DAT_ButtonX::instance + 0xfa)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, (uint)((int)(color)), 0x12, FALSE, 0);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.invasion.repeatMonths
                    == 0) {}
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("(x",
                    (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, color, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.invasion.repeatMonths,
                    (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, (uint)((int)(color)), 0x12, TRUE, 0);
                bVar5 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                            .data.invasion.repeatMonths
                    == 1;
            } else {
                if (iVar3 != 3) {}
                iVar3 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                            .data.scenario.ScenarioEventType;
                iVar4 = iVar3 + 0x80;
                if (0x9b < iVar4) {
                    iVar4 = iVar3 + 0x95;
                }
                blendStrength = 0;
                BVar9 = FALSE;
                iVar10 = 0x12;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_ButtonY::instance + 4;
                iVar8 = DAT_ButtonX::instance + 0x50;
                BVar7 = color;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar4), iVar8, iVar3, TVar6, BVar7, iVar10, BVar9, blendStrength);
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.scenario.repeat
                    == 0) {}
                if (DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.scenario.repeatMonths
                    == 1) {}
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("(",
                    (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, color, 0x12, FALSE, 0);
                bVar1 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                            .data.scenario.repeatMonths;
                if (bVar1 != 10) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)((uint)bVar1,
                        (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                        OpenSHC::Text::TTA_LEFT, (uint)((int)(color)), 0x12, TRUE);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("x",
                    (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, color, 0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    (uint)DAT_MapPropertiesState::instance
                        .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                        .data.scenario.repeat,
                    (int)((int)(DAT_ButtonX::instance + 0x154)), (int)((int)(DAT_ButtonY::instance + 4)),
                    OpenSHC::Text::TTA_LEFT, (uint)((int)(color)), 0x12, TRUE, 0);
                bVar5 = DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.field47_0x1355c + param_1]
                            .data.scenario.repeat
                    == 1;
            }
            if (bVar5) {
                iVar3 = 0xd2;
            } else {
                iVar3 = 0xd3;
            }
            /*
              added by script: "Months"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_SCENARIO, iVar3, (int)((int)(DAT_ButtonX::instance + 0x15a)),
                (int)((int)(DAT_ButtonY::instance + 4)), OpenSHC::Text::TTA_LEFT, (uint)((int)(color)), 0x12, TRUE);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(")",
                (int)((int)(DAT_ButtonX::instance + 0x15a)), (int)((int)(DAT_ButtonY::instance + 4)),
                OpenSHC::Text::TTA_LEFT, color, 0x12, TRUE, 0);
        }

    }
}
}
