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

    using DE::SHCDE::eTextSections;
    using Map::Units::States::UnitState;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043B9D0
    void BuildingMenus::RenderBuildingMenu_Armourer()
    {
        char* pcVar2;
        int iVar3;
        TextAlignment TVar4;
        BGR24 BVar5;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        iVar8 = 0;
        BVar7 = FALSE;
        iVar6 = 0x10;
        BVar5 = 0;
        TVar4 = Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Armourer’s Workshop"
         */
        pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
            DE::SHCDE::TEXT_IN_ARMOURERS_WORKSHOP, 0);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar2, iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
        iVar1 = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .workerID[0];
        if (iVar1
            && DAT_UnitsState::instance.units[iVar1].state.generic
                == (Map::Units::States::US_STAND_UPUnk | Map::Units::States::US_IDLEUnk)) {
            BVar7 = MACRO_CALL(Map::Units_Func::CheckUnitProductionPaused)(iVar1);
            if (!BVar7) {
                iVar8 = 0;
                BVar7 = FALSE;
                iVar6 = 0x12;
                BVar5 = 0;
                TVar4 = Text::TTA_LEFT;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x1fe;
                iVar3 = DAT_MenuHandlerState::instance.x + 0xaf;
                /*
                  added by script: "Not producing - No Iron"
                 */
                pcVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 0xc);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
            }
        }
    }

}
}
