#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00427740
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            char* textAddress;
            int yParam;
            int numInGroup;
            int iVar3;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            numInGroup = -1;
            iVar3 = 0;
            BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if ((BVar1 == FALSE)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)) {
                if (param_1 == 0) {
                    numInGroup = 0x3e;
                    iVar3 = 8;
                } else if (param_1 == 1) {
                    numInGroup = 0x3d;
                    iVar3 = 2;
                } else if (param_1 == 2) {
                    numInGroup = 0x19a;
                    iVar3 = 2;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                    DAT_PencilRenderCore::ptr)(FALSE, 1, (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                yParam = DAT_ButtonY::instance + 5;
                iVar3 = DAT_ButtonX::instance + iVar3;
                BVar1 = FALSE;
                fontSize = 0x13;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                } else {
                    color = 0xccfaff;
                }
                alignment = OpenSHC::Text::TTA_LEFT;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, numInGroup),
                    iVar3, yParam, alignment, color, fontSize, BVar1, iVar2);
            }
        }

    }
}
}
