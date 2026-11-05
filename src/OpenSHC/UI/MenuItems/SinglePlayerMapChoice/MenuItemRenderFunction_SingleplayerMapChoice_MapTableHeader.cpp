#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042DBB0
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_MapTableHeader(int column, ...)
        {
            int textIndex = -1;
            switch (column) {
            case 0:
                // "Name"
                textIndex = 27;
                break;
            case 1:
                // "Date"
                textIndex = 28;
                break;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                DAT_ButtonCurrentlyInteracting::instance, 1, DAT_ButtonBackgroundBlendStrength::instance);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (textIndex == -1) {
                return;
            }
            // one variable in two steps: as two const locals the compiler folds the * 32 / 32 away
            int blendStrength = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
            blendStrength = blendStrength / 32 + 32;
            // y before x: x first loses the match
            int const textY = DAT_ButtonY::instance + 3;
            int const textX = DAT_ButtonX::instance + 8;
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textIndex),
                    textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                    blendStrength);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, textIndex),
                textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 18, FALSE,
                blendStrength);
        }

    }
}
}
