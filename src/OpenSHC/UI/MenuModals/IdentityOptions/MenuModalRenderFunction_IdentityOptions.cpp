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

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491AC0
        void IdentityOptions::MenuModalRenderFunction_IdentityOptions(int x, int y, int width, int height)
        {
            DWORD DVar1;
            char* pcVar2;
            int iVar3;
            uint uVar4;
            int xPos;
            int iVar5;
            int iVar6;
            uint uVar7;
            int iVar8;
            int blendStrength;
            DVar1 = timeGetTime();
            uVar4 = (DVar1 - TIME_IdentityOptions::instance) / 100;
            if (0xf < uVar4) {
                uVar4 = 0;
                TIME_IdentityOptions::instance = timeGetTime();
            }
            /*
              added by script: "Set-up Identity"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4a, 0x2d, x, y, width, height);
            blendStrength = 0;
            iVar8 = 0x12;
            uVar7 = 0xccfaff;
            iVar5 = 0xa5;
            iVar3 = y + 0x6e;
            xPos = x + 0x136;
            iVar6 = xPos;
            /*
              added by script: "Crusader or Arabic Lord"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x32),
                iVar6, iVar3, iVar5, uVar7, iVar8, blendStrength);
            iVar8 = 0;
            iVar5 = 0x12;
            uVar7 = 0xccfaff;
            iVar6 = 0xa5;
            iVar3 = y + 0xd2;
            /*
              added by script: "Choose Portrait"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x33),
                xPos, iVar3, iVar6, uVar7, iVar5, iVar8);
            iVar3 = 100;
            DAT_CurrentlyRenderedSpriteID::instance = 100;
            if (DAT_GameCore::instance.selectedLordTypeUnk != 0) {
                iVar3 = 0xcd;
                DAT_CurrentlyRenderedSpriteID::instance = 0xcd;
            }
            DAT_RenderedUnitOwner::instance = 1;
            if (iVar3 == 100) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_BODY_LORD, (int)((int)(uVar4 * 8 + 0x83)), x + 0x73, y + 0x4b);
                iVar3 = DAT_CurrentlyRenderedSpriteID::instance;
            }
            if (iVar3 == 0xcd) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_BODY_ARABIC_LORD, (int)((int)(uVar4 * 8 + 5)), x + 0x78, y + 0x4b);
            }
        }

    }
}
}
