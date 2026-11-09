#include "../DisplayElements.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOL_RelatedToInitialGranaryAndKeepPlacement.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B1C30
    void DisplayElements::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement(
        int posX, int posY, DWORD whichBuildingIsMissing)
    {
        if (!MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
            return;
        }
        int numInGroup = whichBuildingIsMissing + 9;
        char* text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup);
        int const textHeight = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[18])(text, 0, 0, 580, 0, 0, 1);
        text = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup);
        int const textWidth = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[18])(text, 0, 0, 580, 0, 0, 2);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup),
            posX - textWidth, posY - textHeight, 580, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 18, 0);
        if (whichBuildingIsMissing == 1) {
            if (!BOOL_RelatedToInitialGranaryAndKeepPlacement::instance) {
                // "Place a keep to site your castle my liege"
                // "other_warning1.wav"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning1_wav_005a77c0);
                BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = TRUE;
            }
        }

        if (whichBuildingIsMissing == 2) {
            if (!BOOL_RelatedToInitialGranaryAndKeepPlacement::instance) {
                // "Site your granary sire"
                // "other_warning2.wav"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning2_wav_005a77ac);
                BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = TRUE;
            }
        }
    }

}
}
