#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043DC60
    void BuildingMenus::RenderBuildingMenu_Statue()
    {
        int x;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        int buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x11;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int y = DAT_MenuHandlerState::instance.y + 0x1d3;
        x = DAT_MenuHandlerState::instance.x + 0x19;
        // "Statue"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STATUE, 0),
            x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
        if (DAT_BuildingsState::instance.buildings[buildingID].owner == 0) {
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            color = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            y = DAT_MenuHandlerState::instance.y + 0x1fb;
            x = DAT_MenuHandlerState::instance.x + 0xaf;
            // "Here lies the poor bones of"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MISC2, 1),
                x, y, alignment, color, fontSize, keepOffsetX, blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.finalResults
                    .names[DAT_BuildingsState::instance.buildings[buildingID].statueCommemoratingPlayerID],
                DAT_MenuHandlerState::instance.x + 0xaf, DAT_MenuHandlerState::instance.y + 0x214,
                OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        }
    }

}
}
