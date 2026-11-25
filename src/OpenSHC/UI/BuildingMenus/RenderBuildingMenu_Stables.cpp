#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order, as in RenderBuildingMenu_DogCage.
    // FUNCTION: STRONGHOLDCRUSADER 0x0043D520
    void BuildingMenus::RenderBuildingMenu_Stables()
    {
        int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
        int blendStrength = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSize = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int y = DAT_MenuHandlerState::instance.y + 467;
        int x = DAT_MenuHandlerState::instance.x + 25;
        // "Stables"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 0),
            x, y, alignment, color, fontSize, keepOffsetX, blendStrength);

        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals
                - DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField,
            DAT_MenuHandlerState::instance.x + 175, DAT_MenuHandlerState::instance.y + 517, OpenSHC::Text::TTA_LEFT, 0,
            18, FALSE, 0);
        blendStrength = 0;
        keepOffsetX = TRUE;
        fontSize = 18;
        color = 0;
        y = DAT_MenuHandlerState::instance.y + 517;
        alignment = OpenSHC::Text::TTA_LEFT;
        // offset 1 is the label for any count but one, offset 3 the label for exactly one
        if (DAT_BuildingsState::instance.buildings[buildingID].numberOfAnimals
                - DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField
            != 1) {
            x = DAT_MenuHandlerState::instance.x + 180;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 1),
                x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
        } else {
            x = DAT_MenuHandlerState::instance.x + 180;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 3),
                x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
        }

        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField,
            DAT_MenuHandlerState::instance.x + 175, DAT_MenuHandlerState::instance.y + 537, OpenSHC::Text::TTA_LEFT, 0,
            18, FALSE, 0);
        blendStrength = 0;
        keepOffsetX = TRUE;
        fontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        // "Horse In Use": offset 2 for any count but one, offset 4 for exactly one
        if (DAT_BuildingsState::instance.buildings[buildingID].randomOutpostField != 1) {
            y = DAT_MenuHandlerState::instance.y + 537;
            x = DAT_MenuHandlerState::instance.x + 180;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 2),
                x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
        } else {
            y = DAT_MenuHandlerState::instance.y + 537;
            x = DAT_MenuHandlerState::instance.x + 180;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 4),
                x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
        }
    }

}
}
