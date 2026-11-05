#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BA80
    void BuildingMenus::RenderBuildingMenu_Tanner()
    {
        int blendStrength = 0;
        BOOLEnum paused = FALSE;
        int fontSize = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrWorkerID = DAT_MenuHandlerState::instance.y + 467;
        int x = DAT_MenuHandlerState::instance.x + 25;
        // "Tanner's Workshop"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TANNERS_WORKSHOP, 0),
            x, yOrWorkerID, alignment, color, fontSize, paused, blendStrength);
        yOrWorkerID = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .workerID[0];
        if ((yOrWorkerID != 0)
            && (DAT_UnitsState::instance.units[yOrWorkerID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk)) {
            paused = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(yOrWorkerID);
            if (paused == FALSE) {
                blendStrength = 0;
                paused = FALSE;
                fontSize = 18;
                color = 0;
                alignment = OpenSHC::Text::TTA_LEFT;
                yOrWorkerID = DAT_MenuHandlerState::instance.y + 510;
                x = DAT_MenuHandlerState::instance.x + 175;
                // "Not producing - No Cows"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 13),
                    x, yOrWorkerID, alignment, color, fontSize, paused, blendStrength);
            }
        }
    }

}
}
