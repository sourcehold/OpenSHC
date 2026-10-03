#include "../DisplayElements.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOL_RelatedToInitialGranaryAndKeepPlacement.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B1C30
    void DisplayElements::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement(
        int posX, int posY, DWORD whichBuildingIsMissing)
    {
        int numInGroup;
        BOOLEnum BVar1;
        char* pcVar2;
        int iVar3;
        int iVar4;
        int maxWidth;
        uint color1;
        uint color2;
        int fontSize;
        int blendStrength;
        BVar1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((BVar1 == FALSE) || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL)) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
            return;
        }
        numInGroup = whichBuildingIsMissing + 9;
        iVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup),
            0, 0, 0x244, 0, 0, 1);
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup),
            0, 0, 0x244, 0, 0, 2);
        blendStrength = 0;
        fontSize = 0x12;
        color2 = 0;
        color1 = 0xccfaff;
        maxWidth = 0x244;
        iVar3 = posY - iVar3;
        iVar4 = posX - iVar4;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_FEEDBACK, numInGroup),
            iVar4, iVar3, maxWidth, color1, color2, fontSize, blendStrength);
        if (whichBuildingIsMissing == 1) {
            if (BOOL_RelatedToInitialGranaryAndKeepPlacement::instance == FALSE) {
                /*
                  "Place a keep to site your castle my liege"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning1.wav");
                BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = TRUE;
            }
            return;
        }

        if (whichBuildingIsMissing == 2) {
            if (BOOL_RelatedToInitialGranaryAndKeepPlacement::instance == FALSE) {
                /*
                  "Site your granary sire"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning2.wav");
                BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = TRUE;
            }
        }
    }

}
}
