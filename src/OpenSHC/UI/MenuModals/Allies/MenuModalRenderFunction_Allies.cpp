#include "../Allies.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df42b0.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_Time_Allies1.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004AC6E0
        void Allies::MenuModalRenderFunction_Allies(int x, int y, int width, int height)
        {
            DWORD _now;
            char* pcVar1;
            int xParam;
            int iVar2;
            TextAlignment TVar3;
            BGR24 BVar4;
            int iVar5;
            int iVar6;
            BOOLEnum BVar7;
            int blendStrength;
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::RecalculateAllies)();
            _now = timeGetTime();
            if (500 < _now - DAT_Time_Allies1::instance) {
                DAT_00df42b0::instance = DAT_00df42b0::instance + 1;
                DAT_Time_Allies1::instance = _now;
                if (1 < DAT_00df42b0::instance) {
                    DAT_00df42b0::instance = 0;
                }
            }
            blendStrength = 0;
            BVar7 = FALSE;
            iVar5 = 0xf;
            BVar4 = 0xccfaff;
            TVar3 = OpenSHC::Text::TTA_LEFT;
            iVar2 = y + 0x19;
            xParam = x + 0x27;
            iVar6 = xParam;
            /*
              added by script: "Allies"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 0), iVar6, iVar2, TVar3, BVar4, iVar5, BVar7, blendStrength);
            if (DAT_AlliesCount::instance < 1) {
                iVar5 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar4 = 0xccfaff;
                TVar3 = OpenSHC::Text::TTA_LEFT;
                iVar2 = y + 100;
                /*
                  added by script: "You have no Allies!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 0x13), xParam, iVar2, TVar3, BVar4, iVar6, BVar7, iVar5);
            }
        }

    }
}
}
