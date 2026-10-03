#include "../ChooseRandomNumberOfEnemies.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AE070
        void ChooseRandomNumberOfEnemies::MenuModalRenderFunction_ChooseRandomNumberOfEnemies(
            int x, int y, int width, int height)
        {
            char* pcVar1;
            int iVar2;
            int iVar3;
            TextAlignment alignment;
            BGR24 color;
            int iVar4;
            uint color_00;
            BOOLEnum keepOffsetX;
            int iVar5;
            int blendStrength;
            iVar5 = 0;
            keepOffsetX = FALSE;
            iVar4 = 0x11;
            color = 0xccfaff;
            alignment = OpenSHC::Text::TTA_CENTER;
            iVar2 = y + 100;
            iVar3 = x + 300;
            /*
              added by script: "How many opponents can you handle!"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 1), iVar3, iVar2, alignment, color, iVar4, keepOffsetX, iVar5);
            blendStrength = 0;
            iVar5 = 0x12;
            color_00 = 0xccfaff;
            iVar4 = 400;
            iVar2 = y + 300;
            iVar3 = x + 100;
            /*
              added by script: "This will create some random opponents for you. You can   still change opponent types
              afterwards."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_NEW_TEXT, 2), iVar3, iVar2, iVar4, color_00, iVar5, blendStrength);
        }

    }
}
}
