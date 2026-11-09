#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00425C20
        void Unused::MenuItemActionHandler_UnusedEconomicGametypeSelect_Main(int button, ...)
        {
            switch (button) {
            case 1:
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty2;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 2:
                DAT_GameCore::instance.missionNumber1to20 = 0;
                DAT_GameCore::instance.gameMode_2 = Game::GM_BUILDERUnk;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty_1;
                DAT_MapMissionType::instance = 1;
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.standaloneFilename[0] = '\0';
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 3:
                DAT_GameCore::instance.missionNumber1to20 = 0;
                DAT_GameCore::instance.gameMode_2 = Game::GM_BUILDERUnk;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_MapMissionType::instance = 0;
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.standaloneFilename[0] = '\0';
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty_0;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 4:
                return;
            case 5:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
            }
        }

    }
}
}
