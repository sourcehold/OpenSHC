#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/BuildingMenus.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using DE::SHCDE::eTextSections;
    using Map::Buildings::BuildingTypeShort;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00447D30
    void BuildingMenus::RenderBuildingMenu_Tower()
    {
        int BVar1;
        char* pcVar3;
        int iVar4;
        TextAlignment alignment;
        BGR24 color;
        int iVar5;
        uint color_00;
        BOOLEnum keepOffsetX;
        int iVar6;
        int blendStrength;
        BVar1
            = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType;
        iVar6 = 0;
        keepOffsetX = FALSE;
        iVar5 = 0x10;
        color = 0;
        alignment = Text::TTA_LEFT;
        int iVar2 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Tower"
         */
        pcVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TOWER, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar3, iVar4, iVar2, alignment, color, iVar5, keepOffsetX, iVar6);
        blendStrength = 0;
        iVar6 = 0x12;
        color_00 = 0;
        iVar5 = 0x136;
        iVar2 = DAT_MenuHandlerState::instance.y + 0x1fb;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xaf;
        pcVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TOWER, (int)((short)BVar1 + -0x49));
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            pcVar3, iVar4, iVar2, iVar5, color_00, iVar6, blendStrength);
        MACRO_CALL(UI::BuildingMenus_Func::RenderBuildingMenu_RenderTowerAndGateHealth)();
    }

}
}
