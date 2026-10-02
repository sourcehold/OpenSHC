#include "../ChooseNetworkServiceProvider.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047CEE0
        void ChooseNetworkServiceProvider::MenuItemRenderFunction_ChooseNetworkServiceProvider_InputLabels(
            int param_1, ...)
        {
            char* pcVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            BGR24 color;
            uint color_00;
            int iVar5;
            int iVar6;
            iVar6 = 1;
            iVar5 = 0;
            color = 0;
            iVar4 = 400;
            iVar3 = 0;
            iVar2 = 0;
            /*
              Text:   0x0e => Phone Number (Only needed if Joining)   0x0C => "Host's IP Address (Only needed if
              Joining)"   0x0D => "Ip port"
             */
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk, &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1), iVar2, iVar3, iVar4, color, iVar5, iVar6);
            iVar6 = 0;
            iVar5 = 0x12;
            color_00 = 0xccfaff;
            iVar4 = 400;
            iVar2 = (DAT_ButtonH::instance - iVar2) + -3 + DAT_ButtonY::instance;
            iVar3 = DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, param_1), iVar3, iVar2, iVar4, color_00, iVar5, iVar6);
        }

    }
}
}
