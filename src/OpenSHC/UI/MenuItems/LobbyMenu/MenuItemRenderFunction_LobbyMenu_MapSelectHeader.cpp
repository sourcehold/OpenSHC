#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00427740
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectHeader(int column, ...)
        {
            // both set before the dialog tests, for the match: set after them, the two swap registers
            int textNumInGroup = -1;
            int xOffset = 0;
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                return;
            }
            // the cases in the original's block order
            switch (column) {
            case 2:
                // "Bl"
                textNumInGroup = 410;
                xOffset = 2;
                break;
            case 1:
                // "No"
                textNumInGroup = 61;
                xOffset = 2;
                break;
            case 0:
                // "Name"
                textNumInGroup = 62;
                xOffset = 8;
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(FALSE, 1, DAT_ButtonBackgroundBlendStrength::instance);
            // the fade written the long way round, for the match; it comes back to the blend strength itself
            int const blendStrength = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32;
            int const textY = DAT_ButtonY::instance + 5;
            // x read in each branch: one read before the branch swaps two registers
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                int const textX = DAT_ButtonX::instance + xOffset;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, textNumInGroup),
                    textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE,
                    blendStrength);
            } else {
                int const textX = DAT_ButtonX::instance + xOffset;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, textNumInGroup),
                    textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE,
                    blendStrength);
            }
        }

    }
}
}
