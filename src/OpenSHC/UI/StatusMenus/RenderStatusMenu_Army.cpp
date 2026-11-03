#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95b68.hpp"
#include "OpenSHC/Globals/DAT_00b9845c.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeGroups.hpp"
#include "OpenSHC/Globals/DAT_UnitTypeRelatedCounter.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Units::UnitTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00447FA0
    void StatusMenus::RenderStatusMenu_Army()
    {
        int const x = DAT_MenuHandlerState::instance.x;
        int const y = DAT_MenuHandlerState::instance.y;
        int const firstGroupIcon = DAT_00b95b68::instance * 9;
        int const top = y + 0x1bf;
        DAT_00b9845c::instance = DAT_00b9845c::instance + 1;
        int nudge = 0;
        if (40 < (int)DAT_00b9845c::instance) {
            DAT_00b9845c::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::CountPlayerUnitsByType)();
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Army"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 5),
            x + 0x19, y + 0x1d3, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        int groupSize;
        if (DAT_00b95b68::instance == 2) {
            groupSize = 8;
            nudge = -6;
        } else {
            groupSize = 9;
        }
        // an icon and the head count of each unit type in the group
        for (int i = 0; i < groupSize; i++) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(firstGroupIcon + i + 4, x + 0x55 + i * 0x2e, top + 0x28);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_UnitTypeRelatedCounter::instance[DAT_UnitTypeGroups::instance[0][firstGroupIcon + i]],
                nudge + i * 0x2e + x + 0x6f, top + 0x7d, OpenSHC::Text::TTA_CENTER, 0, 0x11, FALSE, 0);
            if (2 < i) {
                nudge = 0;
            }
        }
        if (DAT_00b95b68::instance != 0) {
            // "Total Troops"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x10),
                x + 0x74, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].armySize,
                x + 0x7a, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }
        // the fear factor's combat bonus, green when positive and red when negative
        int const fearFactor
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .fearFactorLevel;
        uint color;
        int percentX;
        if (0 < fearFactor) {
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb1, x + 0x74, top + 0x1b);
            // "Troop combat bonus:"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                x + 0x9c, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                x + 0xa2, top + 0x19, OpenSHC::Text::TTA_LEFT, 0xff00, 0, 0x12, TRUE, 0);
            color = 0xff00;
            percentX = x + 0xa4;
        } else if (fearFactor < 0) {
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb2, x + 0x74, top + 0x11);
            // "Troop combat bonus:"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                x + 0x92, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                x + 0x98, top + 0x19, OpenSHC::Text::TTA_LEFT, 0xff, 0, 0x12, TRUE, 0);
            color = 0xff;
            percentX = x + 0x9a;
        } else {
            // "No 'fear factor' bonus."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1e),
                x + 0x74, top + 0x19, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            "%", percentX, top + 0x19, OpenSHC::Text::TTA_LEFT, color, 0, 0x12, TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_TextManagerObject::instance.field8_0x20 = 0;
    }

}
}
