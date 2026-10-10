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

        using DE::SHCDE::eGM;
        using DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9DB0
        void TacticalPowerBar::MenuModalRenderFunction_TacticalPowerBar(int x, int y, int width, int height)
        {
            char* text;
            int xPos;
            int iVar1;
            int maxWidth;
            uint color1;
            uint color2;
            int fontSize;
            int blendStrength;
            iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .tacticalPowersBarLevel;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, y + -10, x + 0x2d, y + 0x12e, (ushort)(COL_BLACK::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                x + 0x28, y + -10, x + 0x2d, y + 0x12e, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(x + 0x2a,
                (y - (iVar1 * 0x134) / 7000) + 300, x + 0x2b, y + 300, (ushort)(COL_WHITE::instance.shortValue));
            if (DAT_TacticalPowersHelpTextDisplayBool::instance != false) {
                blendStrength = 0;
                fontSize = 0x12;
                color2 = 0;
                color1 = 0xffffff;
                maxWidth = 0xc3;
                iVar1 = y + 0xfa;
                xPos = x + -200;
                /*
                  added by script: "Click on an Icon to use Tactical Powers"
                 */
                text = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_EXTREME_DEMO, 7);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    text, xPos, iVar1, maxWidth, color1, color2, fontSize, blendStrength);
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, 0x1d4, x + -0x1b, y + 0x10b);
            }
        }

    }
}
}
