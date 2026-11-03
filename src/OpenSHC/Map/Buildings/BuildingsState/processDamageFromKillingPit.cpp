#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00419800
        void BuildingsState::processDamageFromKillingPit(int unitID)
        {
            int const buildingID
                = DAT_TileMapState::instance.BuildingLayer[DAT_UnitsState::instance.units[unitID].tile];
            if (buildingID == 0) {
                return;
            }
            if (DAT_UnitsState::instance.units[unitID].unitType == Units::UT_TRADER
                || DAT_UnitsState::instance.units[unitID].unitType == Units::UT_TRADERHORSE) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_SKIRMISH_AND_MULTIPLAYER
                && this->buildings[buildingID].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_UnitsState::instance.units[unitID].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            if (this->buildings[buildingID].buildingType != BT_KILLINGPIT || this->buildings[buildingID].state != 0
                || DAT_UnitsState::instance.units[unitID].isStalked != 0
                || DAT_GameState::instance.mapAndTime.playerTeams[this->buildings[buildingID].owner]
                    == DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                || DAT_UnitsState::instance.units[unitID].dying != 0) {
                return;
            }
            DAT_UnitsState::instance.units[unitID].health += -18000;
            if (DAT_UnitsState::instance.units[unitID].health <= 0) {
                DAT_UnitsState::instance.units[unitID].health = 0;
                DAT_UnitsState::instance.units[unitID].state.generic = Units::States::US_STONE_DEATH_01;
                DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                DAT_UnitsState::instance.units[unitID].dying = 1;
                DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 1;
            }
            DAT_UnitsState::instance.units[unitID].healthPercentage = MACRO_CALL_MEMBER(
                Navigation::DirectionAlgorithmState_Func::computeHealthPercentage, DAT_DirectionAlgorithmState::ptr)(
                DAT_UnitsState::instance.units[unitID].health, DAT_UnitsState::instance.units[unitID].maxHealth);
            DAT_UnitsState::instance.units[unitID].healthbar
                = DAT_UnitsState::instance.units[unitID].healthPercentage / 10;
            this->buildings[buildingID].state = 1;
        }

    }
}
}
