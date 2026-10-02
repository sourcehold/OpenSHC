#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
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

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x004401A0
    void StatusMenus::RenderStatusMenu_Weapons()
    {
        int iVar1;
        int iVar2;
        int iVar3;
        char* textAddress;
        int yParam;
        int iVar4;
        Position* pPVar5;
        int iVar6;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        iVar2 = DAT_MenuHandlerState::instance.y;
        iVar4 = 0;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x11;
        color = 0;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x1fb;
        alignment = OpenSHC::Text::TTA_LEFT;
        yParam = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar6 = DAT_MenuHandlerState::instance.x + 0x69;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Weapons"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 7), iVar3, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
        pPVar5 = DAT_RenderingDefinedData::instance.field1043_0x55524;
        do {
            iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[*(int*)((int)DAT_RenderingDefinedData::instance.field1041_0x554e4 + iVar4)];
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                *(int*)((int)DAT_RenderingDefinedData::instance.field1042_0x55504 + iVar4), pPVar5->x + iVar6,
                pPVar5->y + iVar1);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                iVar3, iVar6 + 0xc, iVar2 + 0x22d, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
            pPVar5 = pPVar5 + 1;
            iVar6 = iVar6 + 0x34;
            iVar4 = iVar4 + 4;
        } while ((int)pPVar5 < 0x617fd0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
