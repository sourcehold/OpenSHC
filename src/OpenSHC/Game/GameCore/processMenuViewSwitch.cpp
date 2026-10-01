#include "../GameCore.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MenuHandlerState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_ModifierKeyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B980
    void GameCore::processMenuViewSwitch()
    {
        if (this->menuSwitchDelay != -1) {
            if (this->menuSwitchDelay != 0 && timeGetTime() - this->menuRenderMoment < (uint)this->menuSwitchDelay) {
                return;
            }

            DAT_BuildingsState::instance.menuSelectedBuildingID = DAT_BuildingsState::instance.newSelectedBuildingID;
            DAT_BuildingsState::instance.menuSelectedUnitID = DAT_BuildingsState::instance.newSelectedUnitID;
            if (this->currentMenuViewType == this->menuViewToSwitchTo
                && this->activeMenuTab.tabType == this->menuTabToSwitchTo.tabType) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_MenuView_TriggerPrepare::instance = TRUE;
                this->menuSwitchDelay = -1;
                return;
            }

            if (this->menuType7_MenuItemClickHandlerUnk != NULL) {
                (*this->menuType7_MenuItemClickHandlerUnk)(0);
                this->menuType7_MenuItemClickHandlerUnk = NULL;
            }
            if (this->menuViewToSwitchTo == UI::Enums::MVT_MAIN_MENU
                && DAT_GameSynchronyState::instance.currentGameMode == GM_SKIRMISH_SINGLE_PLAYER) {
                DAT_GameSynchronyState::instance.currentGameMode = GM_SOLITARY;
            }

            // this code is executed when changing menus
            this->currentMenuViewType = this->menuViewToSwitchTo;
            this->activeMenuTab = this->menuTabToSwitchTo;
            MACRO_CALL_MEMBER(
                Rendering::ViewportRenderState_Func::resetupViewportThunk, DAT_ViewportRenderState::ptr)();
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
            DAT_MenuView_TriggerPrepare::instance = TRUE;
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            MACRO_CALL_MEMBER(UI::MenuHandlerState_Func::setupMenuForRendering, DAT_MenuHandlerState::ptr)(
                (MenuViewType)this->currentMenuViewType);
            UI::Menu* const currentMenu = DAT_MenuHandlerState::instance.currentMenu;
            currentMenu->xPosition = 0;
            currentMenu->yPosition = 0;
            DAT_MenuHandlerState::instance.x = 0;
            DAT_MenuHandlerState::instance.y = 0;

            // clear the bottom left text tooltip
            MACRO_CALL_MEMBER(UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(0, 0, 0, UI::TextMessageBLLookupStructUnion(), 50, 0);
            MACRO_CALL_MEMBER(
                UI::Rendering::TextureRenderCore_Func::setActiveMenuTabIndexToZero, DAT_TextureRenderCoreObject::ptr)();
            this->menuSwitchDelay = -1;
            if (this->currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                DAT_GameCore::instance.currentlyInGameUnk_0xa4 = TRUE;
            }
        }

        if (this->newPlayerID == 0) {
            return;
        }

        for (int i = 0; i < 9; ++i) {
            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
        }
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->newPlayerID] = 1;
        if (DAT_ModifierKeyState::instance.shift) {
            MACRO_CALL_MEMBER(GameStateStructures_Func::changePlayerOwnership, DAT_GameState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, this->newPlayerID);
        }
        DAT_GameSynchronyState::instance.currentPlayerSlotID = this->newPlayerID;
        this->newPlayerID = 0;
    }

}
}
