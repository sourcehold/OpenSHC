#include "../ScenarioDescription.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventExtra.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0b24.hpp"
#include "OpenSHC/Globals/DAT_00ed2794.hpp"
#include "OpenSHC/Globals/DAT_00ed2798.hpp"
#include "OpenSHC/Globals/DAT_00ed27bc.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuView_TriggerPrepare.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/INT_00ed27c4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using Game::GameMode2;
        using Game::ScenarioEvents::InGameEventExtra;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD100
        void ScenarioDescription::MenuView_ScenarioDescription_Prepare()
        {
            int iVar1;
            int* pIVar3;
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_screen_background.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back0.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back1.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back2.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back3.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back4.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back5.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back6.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back7.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back8.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back9.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back10.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back11.tgx");
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                "briefing_back12.tgx");
            if (DAT_MenuView_TriggerPrepare::instance != 2
                && (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
                    || (DAT_00ed2798::instance = 1,
                        DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1))) {
                DAT_00ed2798::instance = 0;
            }
            if (DAT_MenuModalComposition2::instance.activeModalDialogID == UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
            }
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            MACRO_CALL(Rendering_Func::TicksStartCounter)();
            if (DAT_GameCore::instance.missionNumber1to20 <= 0) {
                DAT_GameCore::instance.missionNumber1to20 = 1;
            }
            int iVar2 = DAT_GameCore::instance.missionNumber1to20;
            if (!DAT_GameCore::instance.gameSuspended) {
                if (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk) {
                    MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::loadMapSiegeHeaderForMissionIndex,
                        DAT_MapPropertiesState::ptr)((char*)DAT_GameCore::instance.missionNumber1to20);
                }
                iVar2 = DAT_GameCore::instance.missionNumber1to20;
                pIVar3 = DAT_MapPropertiesState::instance.SEC_EventsExtra[0].conditionIsTrue;
                for (iVar1 = 8000; iVar1 != 0; iVar1 = iVar1 + -1) {
                    *pIVar3 = 0;
                    pIVar3 = pIVar3 + 1;
                }
                DAT_GameState::instance.mapAndTime.field43_0xf0 = 0;
                DAT_GameState::instance.mapAndTime.field44_0xf4 = 0;
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION)
                && (!DAT_GameCore::instance.gameSuspended)) {
                if (iVar2 < 4) {
                    DAT_GameState::instance.mapAndTime.difficulty = 1;
                } else {
                    DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                }
            }
            DAT_MouseState::instance.waitCursorToggle = 0;
            MACRO_CALL(UI::Helpers_Func::ResetEventStatusUnk)();
            DAT_00eb0b24::instance = 0;
            INT_00ed27c4::instance = 1;
            DAT_ARRAY_00ed26d0::instance[0].y = 0;
            DAT_00ed27bc::instance = 0;
            DAT_00ed2794::instance = 0;
            if ((DAT_MenuView_TriggerPrepare::instance != 2) && (!DAT_GameCore::instance.gameSuspended)) {
                DAT_00ed2794::instance = timeGetTime();
            }
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            return;
        }

    }
}
}
