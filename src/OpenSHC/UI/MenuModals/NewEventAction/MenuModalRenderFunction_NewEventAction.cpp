#include "../NewEventAction.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004ABAB0
        void NewEventAction::MenuModalRenderFunction_NewEventAction(int x, int y, int width, int height)
        {
            char* pcVar1;
            int xParam;
            int iVar2;
            TextAlignment TVar3;
            BGR24 BVar4;
            int iVar5;
            int iVar6;
            BOOLEnum BVar7;
            int blendStrength;
            /*
              added by script: "Event Actions"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(199, 0x67, x, y, width, height);
            switch (DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.scenario.ScenarioEventType) {
            case 5:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x1d:
            case 0x1e:
                blendStrength = 0;
                BVar7 = FALSE;
                iVar5 = 0x12;
                BVar4 = 0xccfaff;
                TVar3 = OpenSHC::Text::TTA_LEFT;
                iVar2 = y + 0x1cd;
                xParam = x + 0x186;
                iVar6 = xParam;
                /*
                  added by script: "Repeat (months)"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xaf),
                    iVar6, iVar2, TVar3, BVar4, iVar5, BVar7, blendStrength);
                iVar5 = 0;
                BVar7 = FALSE;
                iVar6 = 0x12;
                BVar4 = 0xccfaff;
                TVar3 = OpenSHC::Text::TTA_LEFT;
                iVar2 = y + 0x1f0;
                /*
                  added by script: "Repeat Count"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 0xb0),
                    xParam, iVar2, TVar3, BVar4, iVar6, BVar7, iVar5);
            }
        }

    }
}
}
