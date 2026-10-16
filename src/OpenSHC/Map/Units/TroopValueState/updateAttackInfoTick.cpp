#include "../../../Map.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::MapType2;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051FE80
        void TroopValueState::updateAttackInfoTick()
        {
            BOOLEnum BVar1;
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                this->attackInfo.pitchRelatedPlayerID = 1;
                this->attackInfo.playerID_0x2c850 = 2;
            } else {
                this->attackInfo.pitchRelatedPlayerID
                    = MACRO_CALL(Map::Units_Func::FindFirstOpponentWithKeep)();
                this->attackInfo.playerID_0x2c850 = 1;
            }
            if (!this->attackInfo.aiTickPhase) {
                this->attackInfo.field127523_0x2b578 = this->attackInfo.aiTickPhase;
                this->attackInfo.field_0x2c854 = this->attackInfo.aiTickPhase;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::collectArcherUnitsByLocation, this)();
                MACRO_CALL_MEMBER(
                    Map::Units::TroopValueState_Func::assignMacemenAndKnightsNotFromPlayer1ToTribes, this)();
            } else if (this->attackInfo.aiTickPhase == 1) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::updateArcherBrazierProximityFlags, this)();
            } else if ((this->attackInfo.aiTickPhase != 0x32) && (this->attackInfo.aiTickPhase != 100)) {
                if (this->attackInfo.aiTickPhase == 0x46) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::trySendMacemenTribeToAttack, this)();
                } else if (this->attackInfo.aiTickPhase == 0x3c) {
                    MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::trySendKnightTribeToAttack, this)();
                }
            }
            if (!(this->attackInfo.aiTickPhase & 0xfU)) {
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::queueOilThrowForIdleArchers, this)();
            }
            if (((byte)this->attackInfo.aiTickPhase & 0xf) == 8) {
                MACRO_CALL_MEMBER(
                    Map::Units::TroopValueState_Func::redeployArchersToDefensivePositions, this)();
            }
            this->attackInfo.aiTickPhase = this->attackInfo.aiTickPhase + 1;
            if (100 < this->attackInfo.aiTickPhase) {
                this->attackInfo.field_0x2c854 = this->attackInfo.field_0x2c854 + 1;
                this->attackInfo.aiTickPhase = 2;
            }
            BVar1
                = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::unitsCanMoveFromKeepOfPlayerToAnotherArea,
                    DAT_GameState::ptr)(1);
            if ((BVar1) && (!this->attackInfo.field127523_0x2b578)) {
                this->attackInfo.field127523_0x2b578 = 1;
                MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::commandUnitsToMoveToKeep, this)();
            }
            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::processSpottedEnemyTiles, this)();
        }

    }
}
}
