#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
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
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00439440
    void BuildingMenus::RenderBuildingMenu_WorkshopWeaponProduction()
    {
        int iVar1;
        BOOLEnum BVar2;
        char* pcVar3;
        int iVar4;
        int _textNumInGroup;
        int iVar5;
        TextAlignment TVar6;
        BGR24 BVar7;
        int iVar8;
        int iVar9;
        iVar4 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        if ((((DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
                  == OpenSHC::Map::Buildings::BT_FLETCHER)
                 && (iVar1
                     = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                         .workerID[0],
                     iVar1 != 0))
                && (DAT_UnitsState::instance.units[iVar1].state.generic == OpenSHC::Map::Units::States::US_STAND_UPUnk))
            && (BVar2 = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(iVar1), BVar2 == FALSE)) {
            /*
              added by script: "Not producing - No Wood"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 0xb, DAT_MenuHandlerState::instance.x + 0xaf,
                DAT_MenuHandlerState::instance.y + 0x1f9, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
        } else if (((DAT_BuildingsState::instance.buildings[iVar4].buildingType
                        == OpenSHC::Map::Buildings::BT_POLETURNER)
                       && (iVar1 = (int)DAT_BuildingsState::instance.buildings[iVar4].workerID[0], iVar1 != 0))
            && ((DAT_UnitsState::instance.units[iVar1].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk
                && (BVar2 = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(iVar1), BVar2 == FALSE)))) {
            /*
              added by script: "Not producing - No Wood"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 0xb, DAT_MenuHandlerState::instance.x + 0xaf,
                DAT_MenuHandlerState::instance.y + 0x1f9, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
        } else if (((DAT_BuildingsState::instance.buildings[iVar4].buildingType
                        == OpenSHC::Map::Buildings::BT_BLACKSMITH)
                       && (iVar1 = (int)DAT_BuildingsState::instance.buildings[iVar4].workerID[0], iVar1 != 0))
            && ((DAT_UnitsState::instance.units[iVar1].state.generic
                    == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)
                && (BVar2 = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(iVar1), BVar2 == FALSE)))) {
            /*
              added by script: "Not producing - No Iron"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 0xc, DAT_MenuHandlerState::instance.x + 0xaf,
                DAT_MenuHandlerState::instance.y + 0x1f9, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
        } else {
            iVar9 = 0;
            BVar2 = FALSE;
            iVar8 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar1 = DAT_MenuHandlerState::instance.y + 0x1f9;
            iVar5 = DAT_MenuHandlerState::instance.x + 0xaf;
            /*
              added by script: "Producing:"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 3),
                iVar5, iVar1, TVar6, BVar7, iVar8, BVar2, iVar9);
            switch (DAT_BuildingsState::instance.buildings[iVar4].producedItemTypeNext) {
            case OpenSHC::Game::Resources::RT_BOW:
                _textNumInGroup = 7;
                break;
            case OpenSHC::Game::Resources::RT_CROSSBOW:
                _textNumInGroup = 8;
                break;
            case OpenSHC::Game::Resources::RT_SPEAR:
                _textNumInGroup = 9;
                break;
            case OpenSHC::Game::Resources::RT_PIKE:
                _textNumInGroup = 10;
                break;
            case OpenSHC::Game::Resources::RT_MACE:
                _textNumInGroup = 6;
                break;
            case OpenSHC::Game::Resources::RT_SWORD:
                _textNumInGroup = 5;
            }
            iVar9 = 0;
            BVar2 = TRUE;
            iVar8 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar1 = DAT_MenuHandlerState::instance.y + 0x1f9;
            iVar5 = DAT_MenuHandlerState::instance.x + 0xb4;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, _textNumInGroup),
                iVar5, iVar1, TVar6, BVar7, iVar8, BVar2, iVar9);
        }
        iVar9 = 0;
        BVar2 = FALSE;
        iVar8 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x212;
        iVar5 = DAT_MenuHandlerState::instance.x + 0xaf;
        /*
          added by script: "Next:"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 4),
            iVar5, iVar1, TVar6, BVar7, iVar8, BVar2, iVar9);
        switch (DAT_BuildingsState::instance.buildings[iVar4].producedItemType) {
        case OpenSHC::Game::Resources::RT_BOW:
            _textNumInGroup = 7;
            break;
        case OpenSHC::Game::Resources::RT_CROSSBOW:
            _textNumInGroup = 8;
            break;
        case OpenSHC::Game::Resources::RT_SPEAR:
            _textNumInGroup = 9;
            break;
        case OpenSHC::Game::Resources::RT_PIKE:
            _textNumInGroup = 10;
            break;
        case OpenSHC::Game::Resources::RT_MACE:
            _textNumInGroup = 6;
            break;
        case OpenSHC::Game::Resources::RT_SWORD:
            _textNumInGroup = 5;
        }
        iVar8 = 0;
        BVar2 = TRUE;
        iVar5 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x212;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xb4;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, _textNumInGroup),
            iVar1, iVar4, TVar6, BVar7, iVar5, BVar2, iVar8);
    }

}
}
