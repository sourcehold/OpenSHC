#include "../TacticalPowerBar.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9DB0
        void TacticalPowerBar::MenuModalRenderFunction_TacticalPowerBar(int x, int y, int width, int height)
        {
            int barFillHeight
                = (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .tacticalPowersBarLevel
                      * 308)
                / 7000;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                x + 40, y - 10, x + 45, y + 302, COL_BLACK::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                x + 40, y - 10, x + 45, y + 302, COL_VERY_SOFT_YELLOW::instance.shortValue);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                x + 42, y - barFillHeight + 300, x + 43, y + 300, COL_WHITE::instance.shortValue);
            if (DAT_TacticalPowersHelpTextDisplayBool::instance) {
                // "Click on an Icon to use Tactical Powers"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_EXTREME_DEMO, 7),
                    x - 200, y + 250, 195, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 18, 0);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 468, x - 27, y + 267);
            }
        }

    }
}
}
