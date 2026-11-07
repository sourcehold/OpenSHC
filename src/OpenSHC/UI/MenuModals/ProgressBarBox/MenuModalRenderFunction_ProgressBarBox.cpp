#include "../ProgressBarBox.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x00493560
        void ProgressBarBox::MenuModalRenderFunction_ProgressBarBox(int x, int y, int width, int height)
        {
            if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_ENGLISH
                || DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_AMERICAN) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS,
                        (int)(DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter)),
                    width / 2 + x, y + 25, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 16, FALSE,
                    0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS,
                        (int)(DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter)),
                    width / 2 + x, y + 25, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                    0);
            }
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_GameSynchronyState::instance.saveRelated != 0) {
                int barInset = (width - 300) / 2;
                int barY = y + 65;
                int barBottom = y + 80;
                height = barInset + x;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(height,
                    barY, (x - barInset) + width, barBottom, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
                DAT_MenuTextInputState::instance.progressBarY = barY;
                DAT_MenuTextInputState::instance.progressBarX = height;
            } else {
                int barInset = (width - 300) / 2;
                int barY = y + 65;
                int barBottom = y + 80;
                height = barInset + x;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    height, barY, (x - barInset) + width, barBottom);
                DAT_MenuTextInputState::instance.progressBarY = barY;
                DAT_MenuTextInputState::instance.progressBarX = height;
            }
        }
    }
}
}
