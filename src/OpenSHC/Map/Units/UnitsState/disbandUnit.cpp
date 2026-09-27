#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052EDC0
        int UnitsState::disbandUnit(int unitID)
        {
            if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_E_KNIGHT
                && this->units[unitID].horseOriginStablesBuildingIndexUnk != 0) {
                if (*(int*)&this->units[unitID].horseOriginStableIDUnk
                    == DAT_BuildingsState::instance.buildings[this->units[unitID].horseOriginStablesBuildingIndexUnk]
                        .uid) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::removeTetheredUnitFromBuilding,
                        DAT_BuildingsState::ptr)(this->units[unitID].horseOriginStablesBuildingIndexUnk, unitID);
                }
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                UnitTypeShort _unitType = this->units[unitID].unitType;
                this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                /* note &unitID ! */
                int _refund = unitID;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getPriceForDisbandedUnitType,
                    DAT_BuildingsState::ptr)((UnitType)(short)_unitType, &_refund);
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .startResources[0xf] += _refund;
                return DAT_GameSynchronyState::instance.currentPlayerSlotID * 0x39f4 + 0x115c2a0;
            }
            BOOLEnum _hasCampground = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playerHasACampground,
                DAT_GameState::ptr)(this->units[unitID].owner);
            this->units[unitID].disappearFadeAlphaCountdown = 0;
            if (_hasCampground != FALSE) {
                this->units[unitID].state_2 = 0;
                this->units[unitID].cachedState = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                this->units[unitID].unitTypeToChangeInto = OpenSHC::Map::Units::UT_PEASANT;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                this->units[unitID].engineerManningSiegeStateRef_checkType = 1;
                this->units[unitID].isDisappearingUnk = 1;
                return 1;
            }
            this->units[unitID].updateTickTracker = 0;
            this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            this->units[unitID].killedFlagUnk = 1;
            return 0;
        }

    }
}
}
