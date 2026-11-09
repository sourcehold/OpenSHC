#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/TIME_IdentityOptions.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x00491AC0
        void IdentityOptions::MenuModalRenderFunction_IdentityOptions(int x, int y, int width, int height)
        {
            uint animFrame = (timeGetTime() - TIME_IdentityOptions::instance) / 100;
            if (0xf < animFrame) {
                animFrame = 0;
                TIME_IdentityOptions::instance = timeGetTime();
            }
            /*
              added by script: "Set-up Identity"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(74, 45, x, y, width, height);
            int const xPos = x + 310;
            /*
              added by script: "Crusader or Arabic Lord"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 50),
                xPos, y + 110, 165, 0xccfaff, 18, 0);
            /*
              added by script: "Choose Portrait"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 51),
                xPos, y + 210, 165, 0xccfaff, 18, 0);
            int spriteID = 100;
            DAT_CurrentlyRenderedSpriteID::instance = spriteID;
            if (DAT_GameCore::instance.selectedLordTypeUnk != 0) {
                spriteID = 205;
                DAT_CurrentlyRenderedSpriteID::instance = spriteID;
            }
            DAT_RenderedUnitOwner::instance = 1;
            if (spriteID == 100) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_BODY_LORD, (int)(animFrame * 8 + 131), x + 115, y + 75);
                spriteID = DAT_CurrentlyRenderedSpriteID::instance;
            }
            if (spriteID == 205) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_BODY_ARABIC_LORD, (int)(animFrame * 8 + 5), x + 0x78, y + 75);
            }
        }

    }
}
}
