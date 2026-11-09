#include "../SingleplayerMapChoice.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SinglePlayerMapChoice.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"
#include "OpenSHC/Globals/Menu_SingleplayerMapChoice.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Game::GameMode;
        using Game::GameMode2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00448D40
        void SingleplayerMapChoice::MenuView_SingleplayerMapChoice_Prepare()
        {
            Menu* pMVar1;
            char* tgxFileName;
            Menu_SingleplayerMapChoice::instance.thousand = 0;
            DAT_MenuTextInputState::instance.lastListClickTime = 0;
            DAT_MenuTextInputState::instance.lastClickedListIndex = 0xffffffff;
            DAT_GameSynchronyState::instance.currentGameMode = Game::GM_SOLITARY;
            DAT_GameCore::instance.gameMode_2 = Game::GM_BUILDERUnk;
            if (INT_00b95b64::instance != 0) {
                DAT_MenuTextInputState::instance.fileListSortOrder = 0;
                DAT_GameSynchronyState::instance.isHost = TRUE;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
                DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
                DAT_GameSynchronyState::instance.mapName[0] = '\0';
                DAT_GameCore::instance.mapDescription[0] = '\0';
                MACRO_CALL(OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                DAT_SH1_SiegeAdvancedMode::instance = 0;
                DAT_SiegeRemainingPoints::instance = 0;
            } else {
                MACRO_CALL(UI::MenuItems::SinglePlayerMapChoice_Func::
                        MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                DAT_GameSynchronyState::instance.skirmishRelated1 = 1;
            }
            DAT_ButtonBackgroundBlendStrength::instance = 0x20;
            DAT_00b960dc::instance = 0xfffffffd;
            DWORD_00b95b1c::instance = timeGetTime();
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            if ((int)DAT_MapMissionType::instance < 2) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("frontend_economics2.tgx");
            } else {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("frontend_combat2.tgx");
            }
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            int borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            pMVar1->xPosition = borderWidth;
            pMVar1->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(4);
            MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
            INT_00b95b64::instance = 0;
            DAT_GameCore::instance.activeMenuTab.tabType
                = (UI::Enums::BuildingsAndStatusMenuTabTypeInt)(DAT_MapMissionType::instance != 0);
        }

    }
}
}
