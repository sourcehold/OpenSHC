#include "../TribesState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522F70
        void TribesState::spawnUnitsForAITribe(AITribeType tribeType, int tileX, int tileY, int spawnOwnerUnk,
            UnitType unitType, int unitCount, int ownerPlayerIndex)
        {
            if ((tileX <= 0 && tileY <= 0) || unitCount <= 0) {
                return;
            }
            int microYPosition = tileY * 8;
            int microXPosition = tileX * 8;
            int _remainingUnits = unitCount;
            while (_remainingUnits) {
                int const unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    spawnOwnerUnk, spawnOwnerUnk, microXPosition, microYPosition, 8, unitType);
                if (unitID) {
                    DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = ownerPlayerIndex;
                    UnitTypeShort _spawnedUnitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (_spawnedUnitType == Map::Units::UT_E_ARCHER || _spawnedUnitType == Map::Units::UT_E_XBOW
                        || _spawnedUnitType == Map::Units::UT_A_ARCHER || _spawnedUnitType == Map::Units::UT_A_SLINGER
                        || _spawnedUnitType == Map::Units::UT_A_HARCHER
                        || _spawnedUnitType == Map::Units::UT_A_FIRETHROWER) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(unitID, 17);
                    } else {
                        MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(unitID, 20);
                    }
                }
                --_remainingUnits;
            }
        }

    }
}
}
