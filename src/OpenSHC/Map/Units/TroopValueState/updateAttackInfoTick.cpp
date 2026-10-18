#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FE80
        void TroopValueState::updateAttackInfoTick()
        {
            BOOLEnum canMoveFromKeep;
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID = 1;
                DAT_TroopValueState::instance.attackInfo.playerID_0x2c850 = 2;
            } else {
                DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID
                    = MACRO_CALL(Map::Units_Func::FindFirstOpponentWithKeep)();
                DAT_TroopValueState::instance.attackInfo.playerID_0x2c850 = 1;
            }
            if (!DAT_TroopValueState::instance.attackInfo.aiTickPhase) {
                DAT_TroopValueState::instance.attackInfo.unitsSentToKeepFlag
                    = DAT_TroopValueState::instance.attackInfo.aiTickPhase;
                DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount
                    = DAT_TroopValueState::instance.attackInfo.aiTickPhase;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::collectArcherUnitsByLocation, this)();
                MACRO_CALL_MEMBER(
                    Map::Units::TroopValueState_Func::assignMacemenAndKnightsNotFromPlayer1ToTribes, this)();
            } else if (DAT_TroopValueState::instance.attackInfo.aiTickPhase == 1) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateArcherBrazierProximityFlags, this)();
            } else if ((DAT_TroopValueState::instance.attackInfo.aiTickPhase != 0x32)
                && (DAT_TroopValueState::instance.attackInfo.aiTickPhase != 100)) {
                if (DAT_TroopValueState::instance.attackInfo.aiTickPhase == 0x46) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::trySendMacemenTribeToAttack, this)();
                } else if (DAT_TroopValueState::instance.attackInfo.aiTickPhase == 0x3c) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::trySendKnightTribeToAttack, this)();
                }
            }
            if (!(DAT_TroopValueState::instance.attackInfo.aiTickPhase & 0xfU)) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::queueOilThrowForIdleArchers, this)();
            }
            if ((DAT_TroopValueState::instance.attackInfo.aiTickPhase & 0xf) == 8) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::redeployArchersToDefensivePositions, this)();
            }
            DAT_TroopValueState::instance.attackInfo.aiTickPhase
                = DAT_TroopValueState::instance.attackInfo.aiTickPhase + 1;
            if (100 < DAT_TroopValueState::instance.attackInfo.aiTickPhase) {
                DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount
                    = DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount + 1;
                DAT_TroopValueState::instance.attackInfo.aiTickPhase = 2;
            }
            canMoveFromKeep = MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::unitsCanMoveFromKeepOfPlayerToAnotherArea, DAT_GameState::ptr)(1);
            if ((canMoveFromKeep) && (!DAT_TroopValueState::instance.attackInfo.unitsSentToKeepFlag)) {
                DAT_TroopValueState::instance.attackInfo.unitsSentToKeepFlag = 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::commandUnitsToMoveToKeep, this)();
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::processSpottedEnemyTiles, this)();
        }

    }
}
}
