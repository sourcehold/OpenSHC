#include "../TacticalPowerBar.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TacticalPowersHelpTextDisplayBool.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9DB0
        void TacticalPowerBar::MenuModalRenderFunction_TacticalPowerBar(int x, int y, int width, int height)
        {
            int barFillHeight
                = (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .tacticalPowersBarLevel
                      * 0x134)
                / 7000;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, y + -10, x + 0x2d, y + 0x12e, (ushort)(COL_BLACK::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, y + -10, x + 0x2d, y + 0x12e, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                x + 0x2a, (y - barFillHeight) + 300, x + 0x2b, y + 300, (ushort)(COL_WHITE::instance.shortValue));
            if (DAT_TacticalPowersHelpTextDisplayBool::instance != false) {
                /*
                  added by script: "Click on an Icon to use Tactical Powers"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_EXTREME_DEMO, 7),
                    x + -200, y + 0xfa, 0xc3, 0xffffff, 0, 0x12, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x1d4, x + -0x1b, y + 0x10b);
            }
        }
    }
}
}
