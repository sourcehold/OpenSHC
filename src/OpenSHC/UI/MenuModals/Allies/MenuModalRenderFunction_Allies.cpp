#include "../Allies.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_00df42b0.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_Time_Allies1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC6E0
        void Allies::MenuModalRenderFunction_Allies(int x, int y, int width, int height)
        {
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::RecalculateAllies)();
            DWORD const now = timeGetTime();
            if (500 < now - DAT_Time_Allies1::instance) {
                DAT_Time_Allies1::instance = now;
                ++DAT_00df42b0::instance;
                if (1 < DAT_00df42b0::instance) {
                    DAT_00df42b0::instance = 0;
                }
            }
            int const titleY = y + 25;
            int const textX = x + 39;
            // "Allies"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 0),
                textX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 15, FALSE, 0);
            if (DAT_AlliesCount::instance < 1) {
                int const messageY = y + 100;
                // "You have no Allies!"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 19),
                    textX, messageY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
            }
        }

    }
}
}
