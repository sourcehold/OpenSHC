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

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00448D40
        void SingleplayerMapChoice::MenuView_SingleplayerMapChoice_Prepare()
        {
            Menu* pMVar1;
            char* tgxFileName;
            Menu_SingleplayerMapChoice::instance.thousand = 0;
            DAT_MenuTextInputState::instance.field39_0x90 = 0;
            DAT_MenuTextInputState::instance.field38_0x8c = 0xffffffff;
            DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_SOLITARY;
            DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_BUILDERUnk;
            if (INT_00b95b64::instance == 0) {
                MACRO_CALL(OpenSHC::UI::MenuItems::SinglePlayerMapChoice_Func::
                        MenuItemActionHandler_SingleplayerMapChoice_MapTable)(
                    DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected);
                DAT_GameSynchronyState::instance.skirmishRelated1 = 1;
            } else {
                DAT_MenuTextInputState::instance.field33_0x78 = 0;
                DAT_GameSynchronyState::instance.isHost = TRUE;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
                DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
                DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected = -1;
                DAT_GameSynchronyState::instance.mapName[0] = '\0';
                DAT_GameCore::instance.mapDescription[0] = '\0';
                MACRO_CALL(OpenSHC::OS_Func::_memset)(DAT_MinimapViewState::instance.loadedMiniMap, 0, 80000);
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                DAT_SH1_SiegeAdvancedMode::instance = 0;
                DAT_SiegeRemainingPoints::instance = 0;
            }
            DAT_ButtonBackgroundBlendStrength::instance = 0x20;
            DAT_00b960dc::instance = 0xfffffffd;
            DWORD_00b95b1c::instance = timeGetTime();
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            if (DAT_MapMissionType::instance < 2) {
                tgxFileName = "frontend_economics2.tgx";
            } else {
                tgxFileName = "frontend_combat2.tgx";
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(tgxFileName);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(4);
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
            INT_00b95b64::instance = 0;
            DAT_GameCore::instance.activeMenuTab.tabType
                = (OpenSHC::UI::Enums::BuildingsAndStatusMenuTabTypeInt)(DAT_MapMissionType::instance != 0);
        }

    }
}
}
