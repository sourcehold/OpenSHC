#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043FAC0
    void StatusMenus::RenderStatusMenu_Food()
    {
        int iVar1;
        char* pcVar2;
        int iVar3;
        int iVar4;
        int* piVar5;
        int iVar6;
        TextAlignment TVar7;
        BGR24 BVar8;
        int iVar9;
        BOOLEnum BVar10;
        int blendStrength;
        iVar4 = DAT_MenuHandlerState::instance.y;
        iVar6 = DAT_MenuHandlerState::instance.x;
        blendStrength = 0;
        BVar10 = FALSE;
        iVar9 = 0x11;
        BVar8 = 0;
        TVar7 = OpenSHC::Text::TTA_LEFT;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar1 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Food"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 4),
            iVar1, iVar3, TVar7, BVar8, iVar9, BVar10, blendStrength);
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            iVar9 = 0;
            BVar10 = FALSE;
            iVar3 = 0x12;
            BVar8 = 0;
            TVar7 = OpenSHC::Text::TTA_CENTER;
            iVar4 = iVar4 + 0x246;
            iVar1 = DAT_MenuHandlerState::instance.x + 0x13c;
            /*
              added by script: "Clicking on a food toggles consumption"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x17),
                iVar1, iVar4, TVar7, BVar8, iVar3, BVar10, iVar9);
        }
        iVar6 = iVar6 + 0xbe;
        piVar5 = DAT_RenderingDefinedData::instance.field1050_0x55720;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[*piVar5],
                iVar6, DAT_MenuHandlerState::instance.y + 0x225, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
            piVar5 = piVar5 + 1;
            iVar6 = iVar6 + 0x50;
        } while (piVar5 < DAT_RenderingDefinedData::instance.field1050_0x55720 + 4);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
