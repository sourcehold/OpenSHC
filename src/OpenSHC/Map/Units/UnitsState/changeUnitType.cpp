#include "../UnitsState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E6C0
        int UnitsState::changeUnitType(int unitID)
        {
            this->units[unitID].state.generic = this->units[unitID].state_2;
            UnitTypeShort _previousUnitType = this->units[unitID].unitType;
            this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
            this->units[unitID].goToRallyPoint = 1;
            this->units[unitID].unitType_3 = _previousUnitType;
            this->units[unitID].substate = -1;
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                if (this->units[unitID].unitTypeToChangeInto < UT_E_ARCHER) {
                    /* civilians */
                    this->units[unitID].calculatedOwnerPlayerIndex = 0;
                } else if (this->units[unitID].unitTypeToChangeInto <= UT_E_ENGINEER
                    || this->units[unitID].unitTypeToChangeInto >= UT_A_ARCHER) {
                    /* is army member */
                    this->units[unitID].calculatedOwnerPlayerIndex = this->units[unitID].owner;
                } else {
                    this->units[unitID].calculatedOwnerPlayerIndex = 0;
                }
                if (this->units[unitID].calculatedOwnerPlayerIndex == 0 && this->units[unitID].owner > 1) {
                    this->units[unitID].calculatedOwnerPlayerIndex = this->units[unitID].owner;
                }
            } else {
                this->units[unitID].calculatedOwnerPlayerIndex = this->units[unitID].owner;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitValues, this)(
                unitID, (UnitType)(short)this->units[unitID].unitTypeToChangeInto);
            return unitID;
        }

    }
}
}
