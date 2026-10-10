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

        using DE::SHCDE::eTextSections;
        using Rendering::Colors::BGR24;
        using Text::TextAlignment;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC6E0
        void Allies::MenuModalRenderFunction_Allies(int x, int y, int width, int height)
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
            MACRO_CALL(Game::Skirmish_Func::RecalculateAllies)();
            DWORD _now = timeGetTime();
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
            TVar3 = Text::TTA_LEFT;
            iVar2 = y + 0x19;
            xParam = x + 0x27;
            iVar6 = xParam;
            /*
              added by script: "Allies"
             */
            pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES, 0);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar1, iVar6, iVar2, TVar3, BVar4, iVar5, BVar7, blendStrength);
            if (DAT_AlliesCount::instance <= 0) {
                iVar5 = 0;
                BVar7 = FALSE;
                iVar6 = 0x11;
                BVar4 = 0xccfaff;
                TVar3 = Text::TTA_LEFT;
                iVar2 = y + 100;
                /*
                  added by script: "You have no Allies!"
                 */
                pcVar1 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ALLIES, 0x13);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar1, xParam, iVar2, TVar3, BVar4, iVar6, BVar7, iVar5);
            }
        }

    }
}
}
