#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537D60
        undefined4 UnitsState::tryAttackUnitID(int unitID_1, int unitID_2)
        {
            if (unitID_2 < 1) {
                return 0;
            }
            if (this->units[unitID_1].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return 0;
            }
            if (this->units[unitID_1].dying != 0) {
                return 0;
            }
            if (this->units[unitID_2].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                return 0;
            }
            if (this->units[unitID_2].dying != 0) {
                return 0;
            }
            if (this->units[unitID_1].state.generic == (UnitState)0xcf) {
                return 0;
            }
            if (this->units[unitID_1].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                return 0;
            }
            this->units[unitID_1].movementType_OR_targetUnitID = (short)unitID_2;
            this->units[unitID_1].targetedUnitID__OR__engineerMannedSiegeEngineRef = (short)unitID_2;
            this->units[unitID_1].targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID
                = this->units[unitID_2].uid;
            this->units[unitID_2].huntedBy = this->units[unitID_2].huntedBy + 1;
            this->units[unitID_1].state.generic = (UnitState)0xcf;
            this->units[unitID_1].destinationNeeded = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
            return 1;
        }

    }
}
}
