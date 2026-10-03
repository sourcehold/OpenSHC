#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0043A960
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight(
            int param_1, ...)
        {
            char* textAddress;
            int xParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            backgroundColor = 0;
            foregroundColor = 0xb8eefb;
            alignment = OpenSHC::Text::TTA_RIGHT;
            int yParam = DAT_ButtonY::instance + 0x98;
            xParam = DAT_ButtonX::instance + -5;
            /*
              added by script: "Available Peasants"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BARRACKS, 3),
                xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .availablePeasantsOrHousedPeasants
                    - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .count,
                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 0x98), OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0,
                0x12, FALSE, 0);
        }

    }
}
}
