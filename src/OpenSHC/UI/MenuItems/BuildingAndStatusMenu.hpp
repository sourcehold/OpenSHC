/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/BuildingAndStatusMenu.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            using OpenSHC::Game::Resources::ResourceType;

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_StopBuildingOrPeasantBinkPlayback();

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Countdown();

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuildingHelpTextButton();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuildingHelpTextButton(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BarracksAndMercenaryPostHelpText(
                int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextUpperRight(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_AvailablePeasantsTextDownRight(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_StatusMenuButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_StatusMainMenuButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_PopularityMenuSwitchButtonUnk();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_PopularityMenuSwitchButton(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_DisableFoodType(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_DisableFoodType(int foodType, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ArmySwitchButton();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusSwitchButton();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ReturnToBuildMenu(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_Unknown_Min1();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BarracksWeaponAvailability(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_UnknownMin1Unk();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_WorkshopWeaponSelection(
                ResourceType _weapon, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_WorkshopWeaponSelection(ResourceType weapon, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_DrawbridgeOpenClose(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_GatehouseOpenClose(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_GatehouseOpenClose(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TaxSlider(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_HorizontalSlider(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOL isDragged);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TaxArrowButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_TaxArrowButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_ChangeRations(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_GeneralButtonRender(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_MarketMenuChangeButtons(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_SelectBuySellGoods(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuildingSleep();

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_RepairBuildingButton();

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_RepairBuildingButton(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostUnitSelection(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderSize(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_OutpostSliderDelay(
                int param_1, int param_2, int* minValue, int* maxValue, int* currentValue);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BarrackUnitPortraits(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_MercenaryPostPortraits(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_EngineerAndMonkPortraits(int param_1, ...);

            void __cdecl MenuItemRenderFunction_BuildingAndStatusMenu_TunnelerPortrait(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int param_1, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick(int barrackUnitIdUnk, ...);

            void __cdecl MenuItemActionHandler_BuildingAndStatusMenu_MercenaryPostPortraits(int param_1, ...);

        } // namespace BuildingAndStatusMenu
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
