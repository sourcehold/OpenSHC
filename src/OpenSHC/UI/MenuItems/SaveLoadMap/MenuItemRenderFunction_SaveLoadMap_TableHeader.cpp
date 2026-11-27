#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492FD0
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableHeader(int column, ...)
        {
            int textNumInGroup = -1;
            switch (column) {
            case 2:
                textNumInGroup = 29; // "Mission"
                break;
            case 1:
                textNumInGroup = 28; // "Date"
                break;
            case 0:
                textNumInGroup = 27; // "Name"
                break;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(FALSE, 1, 0);
            // one call per hover state, the two the same: the form that compiles to the original's code
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                int const textY = DAT_ButtonY::instance + 3;
                int const textX = DAT_ButtonX::instance + 8;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textNumInGroup),
                    textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            } else {
                int const textY = DAT_ButtonY::instance + 3;
                int const textX = DAT_ButtonX::instance + 8;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textNumInGroup),
                    textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            }
        }

    }
}
}
