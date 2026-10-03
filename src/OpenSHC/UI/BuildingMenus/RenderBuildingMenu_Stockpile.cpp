#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::MenuViewType;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C6A0
    void BuildingMenus::RenderBuildingMenu_Stockpile()
    {
        int number;
        char* _pText;
        BOOLEnum BVar2;
        int _textY;
        int _x;
        Position* _nudges;
        int _index4;
        int _fontSize;
        BOOLEnum _retainX;
        int _blendStrength;
        TextAlignment _alignment;
        BGR24 _color;
        int _y;
        _index4 = 0;
        _blendStrength = 0;
        _retainX = FALSE;
        _fontSize = 0x10;
        _color = 0;
        _y = DAT_MenuHandlerState::instance.y + 0x200;
        _alignment = OpenSHC::Text::TTA_LEFT;
        _textY = DAT_MenuHandlerState::instance.y + 0x1d3;
        _x = DAT_MenuHandlerState::instance.x + 0x1e;
        int _textX = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          Render stockpile title
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GOODS_YARD, 0), _textX, _textY, _alignment, _color, _fontSize, _retainX, _blendStrength);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        _nudges = DAT_RenderingDefinedData::instance.StockpileIconsPositionNudges;
        do {
            number
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .currentResources[*(int*)((int)DAT_RenderingDefinedData::instance.field1038_0x55464 + _index4)];
            /*
              Render resource image
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                *(int*)((int)DAT_RenderingDefinedData::instance.field1039_0x55484 + _index4), _nudges->x + _x,
                _nudges->y + _y);
            if (DAT_MouseState::instance.leftClickStart != 0) {
                int iVar1 = *(int*)((int)DAT_RenderingDefinedData::instance.field1039_0x55484 + _index4);
                BVar2 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    _nudges->x + _x, _nudges->y + _y,
                    (int)(DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x2e] + -1]
                            .width),
                    (int)(DAT_GMImageHeaders::instance.imh[iVar1 + GMTotalPicturesProcessed::instance[0x2e] + -1]
                            .height));
                if ((BVar2 != FALSE)
                    && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketplace.id
                        != 0)) {
                    BVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                        *(ResourceType*)((int)DAT_RenderingDefinedData::instance.field1038_0x55464 + _index4));
                    if (BVar2 != FALSE) {
                        DAT_BuildingsState::instance.newSelectedBuildingID
                            = DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .marketplace.id;
                        DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x39;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType
                            = *(ResourceTypeInt*)((int)DAT_RenderingDefinedData::instance.field1038_0x55464 + _index4);
                    }
                }
            }
            /*
              Render textfields for resources
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                number, _x + 0xc, DAT_MenuHandlerState::instance.y + 0x22f, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
            _nudges = _nudges + 1;
            _x = _x + 0x3c;
            _index4 = _index4 + 4;
        } while ((int)_nudges < 0x617f50);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
