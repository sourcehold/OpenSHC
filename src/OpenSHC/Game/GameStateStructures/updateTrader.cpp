#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0045B6B0
    void GameStateStructures::updateTrader()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        this->mapAndTime.traderRelatedCounter1 = this->mapAndTime.traderRelatedCounter1 + 1;
        if (this->mapAndTime.traderRelated2 == 1) {
            this->mapAndTime.traderRelatedCounter1 = 0;
            return;
        }
        if (this->mapAndTime.traderRelated2 == 2) {
            if ((DAT_TroopValueState::instance.attackInfo.aiTroops <= 1)
                && (this->mapAndTime.traderRelatedCounter1 >= this->mapAndTime.traderRelated1)) {
                this->mapAndTime.traderVisitsPlayer = 0;
                this->mapAndTime.traderRelated2 = 1;
                this->mapAndTime.traderRelatedCounter1 = 0;
            }
            return;
        }
        if (this->mapAndTime.traderRelated2 != 0) {
            return;
        }
        if (DAT_TroopValueState::instance.attackInfo.aiTroops > 1) {
            return;
        }
        if (this->mapAndTime.traderRelatedCounter1 < this->mapAndTime.traderRelatedCounter2) {
            return;
        }
        this->mapAndTime.traderRelatedCounter1 = 0;
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::findNextPlayerWithMarketplace, this)(
                this->mapAndTime.traderVisitsPlayer)
            == 0) {
            return;
        }
        int visitingPlayerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        this->mapAndTime.traderVisitsPlayer = visitingPlayerID;
        if (visitingPlayerID == 0) {
            return;
        }
        this->mapAndTime.traderRelated2 = 1;
        int traderUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, 0,
            this->mapAndTime.signpostsMapEdge[0][0].x * 8, this->mapAndTime.signpostsMapEdge[0][0].y * 8, 8,
            OpenSHC::Map::Units::UT_TRADER);
        if (traderUnitID == 0) {
            return;
        }
        int horseUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, 0,
            this->mapAndTime.signpostsMapEdge[0][0].x * 8, this->mapAndTime.signpostsMapEdge[0][0].y * 8, 8,
            OpenSHC::Map::Units::UT_TRADERHORSE);
        if (horseUnitID == 0) {
            return;
        }
        DAT_UnitsState::instance.units[horseUnitID].traderHorsesTrader = (short)traderUnitID;
        DAT_UnitsState::instance.units[horseUnitID].workplaceBuildingUID
            = DAT_UnitsState::instance.units[traderUnitID].uid;
    }
}
}
