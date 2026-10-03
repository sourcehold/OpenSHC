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
#include "OpenSHC/IO/Graphics/GmID.hpp"
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
    using OpenSHC::IO::Graphics::GmID;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C840
    void BuildingMenus::RenderBuildingMenu_Armory()
    {
        char* textAddress;
        int iVar3;
        int iVar4;
        Position* _positionPtr;
        int iVar5;
        TextAlignment alignment;
        BGR24 color;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        iVar5 = 0;
        iVar8 = 0;
        BVar7 = FALSE;
        iVar6 = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1fb;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x1e;
        int iVar2 = DAT_MenuHandlerState::instance.x + 0x19;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_ARMOURY, 0),
            iVar2, iVar3, alignment, color, iVar6, BVar7, iVar8);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        _positionPtr = DAT_RenderingDefinedData::instance.field1043_0x55524;
        do {
            iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[*(int*)((int)DAT_RenderingDefinedData::instance.field1041_0x554e4 + iVar5)];
            iVar6 = _positionPtr->y + iVar1;
            iVar8 = _positionPtr->x + iVar4;
            iVar3 = *(int*)((int)DAT_RenderingDefinedData::instance.field1042_0x55504 + iVar5);
            if (iVar2 < 1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar3, iVar8, iVar6, 0x10);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3, iVar8, iVar6);
            }
            if (DAT_MouseState::instance.leftClickStart != 0) {
                iVar3 = *(int*)((int)DAT_RenderingDefinedData::instance.field1042_0x55504 + iVar5);
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    _positionPtr->x + iVar4, _positionPtr->y + iVar1,
                    (int)(DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x2e] + iVar3 + -1]
                            .width),
                    (int)(DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x2e] + iVar3 + -1]
                            .height));
                if ((BVar7 != FALSE)
                    && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketplace.id
                        != 0)) {
                    BVar7 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::isResourceTypeTradeable, DAT_GameState::ptr)(
                        *(ResourceType*)((int)DAT_RenderingDefinedData::instance.field1041_0x554e4 + iVar5));
                    if (BVar7 != FALSE) {
                        DAT_BuildingsState::instance.newSelectedBuildingID
                            = DAT_GameState::instance
                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                  .marketplace.id;
                        DAT_GameCore::instance.buildingandstatusmenuMenuTabToSwitchTo = 0x39;
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU, 0);
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType
                            = *(ResourceTypeInt*)((int)DAT_RenderingDefinedData::instance.field1041_0x554e4 + iVar5);
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar2,
                iVar4 + 0xc, DAT_MenuHandlerState::instance.y + 0x22f, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
            _positionPtr = _positionPtr + 1;
            iVar4 = iVar4 + 0x3c;
            iVar5 = iVar5 + 4;
        } while ((int)_positionPtr < 0x617fd0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
