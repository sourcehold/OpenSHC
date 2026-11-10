#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BFA0
    void BuildingMenus::RenderBuildingMenu_Apothecary()
    {
        int blendStrength = 0;
        BOOLEnum keepOffsetX = FALSE;
        int fontSize = 16;
        BGR24 color = 0;
        TextAlignment alignment = OpenSHC::Text::TTA_LEFT;
        int yOrHealerCount = DAT_MenuHandlerState::instance.y + 467;
        int x = DAT_MenuHandlerState::instance.x + 25;
        // "Apothecary"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HEALERS, 0),
            x, yOrHealerCount, alignment, color, fontSize, keepOffsetX, blendStrength);
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        yOrHealerCount = DAT_MenuHandlerState::instance.y + 515;
        x = DAT_MenuHandlerState::instance.x + 177;
        // "Immunity From Disease"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HEALERS, 3),
            x, yOrHealerCount, alignment, color, fontSize, keepOffsetX, blendStrength);
        yOrHealerCount
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].healerCount;
        if (yOrHealerCount >= 3) {
            yOrHealerCount = 3;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            yOrHealerCount * 20, DAT_MenuHandlerState::instance.x + 183, DAT_MenuHandlerState::instance.y + 515,
            OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 183, DAT_MenuHandlerState::instance.y + 515, OpenSHC::Text::TTA_LEFT, 0,
            18, TRUE, 0);
    }

}
}
