#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00492FD0
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableHeader(int param_1, ...)
        {
            int yParam;
            char* textAddress;
            int xParam;
            int numInGroup;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            numInGroup = -1;
            if (param_1 == 0) {
                numInGroup = 0x1b;
            } else if (param_1 == 1) {
                numInGroup = 0x1c;
            } else if (param_1 == 2) {
                numInGroup = 0x1d;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(FALSE, 1, 0);
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            color = 0xccfaff;
            alignment = OpenSHC::Text::TTA_LEFT;
            yParam = DAT_ButtonY::instance + 3;
            xParam = DAT_ButtonX::instance + 8;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, numInGroup),
                xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
