#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004016E0
        int EntityState::findNearestDiseaseCloudForHealer(int unitID)
        {
            int nearestCloudID = 0;
            int nearestDistance = 10000;
            int unitArea
                = (short)DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            for (int entityID = 1; entityID < (int)this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState != 2
                    || this->entityArray[entityID].entityType != OpenSHC::Map::Entities::ET_COW_POISON_CLOUD
                    || this->entityArray[entityID].unknownAnimationFrameRelated > 1000
                    || this->entityArray[entityID].unknownDistanceRelatedValue != 0) {
                    continue;
                }
                short claimingHealerID = this->entityArray[entityID].unitID_healer;
                if (claimingHealerID != 0) {
                    if (this->entityArray[entityID].unitUID == DAT_UnitsState::instance.units[claimingHealerID].climbDataRelated
                        && (DAT_UnitsState::instance.units[claimingHealerID].state.generic
                                == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk
                            || DAT_UnitsState::instance.units[claimingHealerID].state.generic
                                == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk)) {
                        continue;
                    }
                    this->entityArray[entityID].unitID_healer = 0;
                }
                int cloudArea
                    = (short)DAT_TileMapState::instance.PathConnectionLayer[this->entityArray[entityID].tile];
                if (cloudArea != unitArea
                    && MACRO_CALL_MEMBER(
                           OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].owner, unitArea, cloudArea, 0)
                        == 0) {
                    continue;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int workplaceID = DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1;
                    if (workplaceID != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(DAT_BuildingsState::instance.buildings[workplaceID].x,
                            DAT_BuildingsState::instance.buildings[workplaceID].y,
                            this->entityArray[entityID].xPosition, this->entityArray[entityID].yPosition);
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh > 30) {
                            continue;
                        }
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, this->entityArray[entityID].xPosition,
                    this->entityArray[entityID].yPosition);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh < nearestDistance) {
                    nearestCloudID = entityID;
                    nearestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                }
            }
            return nearestCloudID;
        }

    }
}
}
