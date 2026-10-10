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

    using DE::SHCDE::eTextSections;
    using Game::GameMode2;
    using UI::Enums::DisplayElementID;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004B1C30
    void DisplayElements::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement(
        int posX, int posY, DWORD whichBuildingIsMissing)
    {
        char* pcVar2;
        int iVar3;
        int iVar4;
        int maxWidth;
        uint color1;
        uint color2;
        int fontSize;
        int blendStrength;
        BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if ((!BVar1) || (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL)) {
            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
        }
        int numInGroup = whichBuildingIsMissing + 9;
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
            DE::SHCDE::TEXT_FEEDBACK, numInGroup);
        iVar3 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(pcVar2, 0, 0, 0x244, 0, 0, 1);
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
            DE::SHCDE::TEXT_FEEDBACK, numInGroup);
        iVar4 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
            &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(pcVar2, 0, 0, 0x244, 0, 0, 2);
        blendStrength = 0;
        fontSize = 0x12;
        color2 = 0;
        color1 = 0xccfaff;
        maxWidth = 0x244;
        iVar3 = posY - iVar3;
        iVar4 = posX - iVar4;
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
            DE::SHCDE::TEXT_FEEDBACK, numInGroup);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
            pcVar2, iVar4, iVar3, maxWidth, color1, color2, fontSize, blendStrength);
        if (whichBuildingIsMissing == 1) {
            if (BOOL_RelatedToInitialGranaryAndKeepPlacement::instance) {}
            /*
              "Place a keep to site your castle my liege"
             */
            pcVar2 = "other_warning1.wav";
        } else {
            if (whichBuildingIsMissing != 2) {}
            if (BOOL_RelatedToInitialGranaryAndKeepPlacement::instance) {}
            /*
              "Site your granary sire"
             */
            pcVar2 = "other_warning2.wav";
        }
        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(pcVar2);
        BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = TRUE;
    }

}
}
