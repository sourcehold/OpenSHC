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

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00447FA0
    void StatusMenus::RenderStatusMenu_Army()
    {
        char* pcVar1;
        UnitTypeInt(*paUVar2)[9];
        int iVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        TextAlignment TVar7;
        uint foregroundColor;
        BGR24 BVar8;
        int fontSize;
        int iVar9;
        BOOLEnum BVar10;
        int blendStrength;
        int iVar11;
        int local_14;
        int local_10;
        int local_c;
        iVar4 = DAT_MenuHandlerState::instance.y;
        iVar5 = DAT_MenuHandlerState::instance.x;
        iVar11 = DAT_00b95b68::instance;
        iVar9 = DAT_00b95b68::instance * 9;
        DAT_00b9845c::instance = DAT_00b9845c::instance + 1;
        local_14 = 0;
        if (0x28 < DAT_00b9845c::instance) {
            DAT_00b9845c::instance = 0;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::CountPlayerUnitsByType)();
        }
        blendStrength = 0;
        BVar10 = FALSE;
        fontSize = 0x11;
        BVar8 = 0;
        TVar7 = OpenSHC::Text::TTA_LEFT;
        iVar3 = iVar4 + 0x1d3;
        iVar6 = iVar5 + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Army"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 5),
            iVar6, iVar3, TVar7, BVar8, fontSize, BVar10, blendStrength);
        if (DAT_00b95b68::instance == 2) {
            local_c = 8;
            local_14 = -6;
        } else {
            local_c = 9;
        }
        iVar6 = 0;
        if (local_c != 0) {
            local_10 = iVar5 + 0x55;
            iVar3 = 0;
            paUVar2 = DAT_RenderingDefinedData::instance.UnitTypeGroups + iVar11;
            do {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                    DAT_TextureRenderCoreObject::ptr)(iVar9 + 4 + iVar6, local_10, iVar4 + 0x1e7);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_UnitTypeRelatedCounter::instance[(*paUVar2)[0]], local_14 + iVar3 + 0x6f + iVar5, iVar4 + 0x23c,
                    OpenSHC::Text::TTA_CENTER, 0, 0x11, FALSE, 0);
                if (2 < iVar6) {
                    local_14 = 0;
                }
                local_10 = local_10 + 0x2e;
                iVar6 = iVar6 + 1;
                paUVar2 = (UnitTypeInt(*)[9])(*paUVar2 + 1);
                iVar3 = iVar3 + 0x2e;
            } while (iVar6 < local_c);
        }
        if (DAT_00b95b68::instance != 0) {
            iVar3 = 0;
            BVar10 = FALSE;
            iVar6 = 0x12;
            BVar8 = 0;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar9 = iVar5 + 0x74;
            iVar11 = iVar4 + 0x1d8;
            /*
              added by script: "Total Troops"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x10),
                iVar9, iVar11, TVar7, BVar8, iVar6, BVar10, iVar3);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].armySize,
                iVar5 + 0x7a, iVar4 + 0x1d8, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }
        iVar9 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .fearFactorLevel;
        if (iVar9 < 1) {
            if (-1 < iVar9) {
                iVar11 = 0;
                BVar10 = FALSE;
                iVar9 = 0x12;
                BVar8 = 0;
                TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar4 = iVar4 + 0x1d8;
                iVar5 = iVar5 + 0x74;
                /*
                  added by script: "No 'fear factor' bonus."
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1e),
                    iVar5, iVar4, TVar7, BVar8, iVar9, BVar10, iVar11);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb2, iVar5 + 0x74, iVar4 + 0x1d0);
            iVar3 = 0;
            BVar10 = FALSE;
            iVar6 = 0x12;
            BVar8 = 0;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar9 = iVar5 + 0x92;
            iVar11 = iVar4 + 0x1d8;
            /*
              added by script: "Troop combat bonus:"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                iVar9, iVar11, TVar7, BVar8, iVar6, BVar10, iVar3);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                iVar5 + 0x98, iVar4 + 0x1d8, OpenSHC::Text::TTA_LEFT, 0xff, 0, 0x12, TRUE, 0);
            foregroundColor = 0xff;
            iVar5 = iVar5 + 0x9a;
        } else {
            DAT_TextManagerObject::instance.field8_0x20 = 1;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xb1, iVar5 + 0x74, iVar4 + 0x1da);
            iVar3 = 0;
            BVar10 = FALSE;
            iVar6 = 0x12;
            BVar8 = 0;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar9 = iVar5 + 0x9c;
            iVar11 = iVar4 + 0x1d8;
            /*
              added by script: "Troop combat bonus:"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1f),
                iVar9, iVar11, TVar7, BVar8, iVar6, BVar10, iVar3);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .fearFactorLevel
                    * 5,
                iVar5 + 0xa2, iVar4 + 0x1d8, OpenSHC::Text::TTA_LEFT, 0xff00, 0, 0x12, TRUE, 0);
            foregroundColor = 0xff00;
            iVar5 = iVar5 + 0xa4;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            "%", iVar5, iVar4 + 0x1d8, OpenSHC::Text::TTA_LEFT, foregroundColor, 0, 0x12, TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_TextManagerObject::instance.field8_0x20 = 0;
    }

}
}
