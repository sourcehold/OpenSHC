#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Game::GameMode;
        using Map::Entities::EntityType;
        using Map::Units::States::UnitState;
        using Map::Units::States::UnitStateShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x004016E0
        int EntityState::findNearestDiseaseCloudForHealer(int unitID)
        {
            short healerUnitID;
            UnitStateShort unitState;
            int canNavigate;
            int nearestEntityIndex = 0;
            int minDistance = 10000;

            auto unitArea = static_cast<short>(DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile]);

            for (int i = 1; i < this->maxEntityCount; ++i) {
                Entity& entity = this->entityArray[i];

                if (entity.logicalState == 2 
                    && entity.entityType == Map::Entities::ET_COW_POISON_CLOUD
                    && entity.unknownAnimationFrameRelated < 1001
                    && !entity.unknownDistanceRelatedValue) {
                    
                    healerUnitID = entity.unitID_healer;
                    if (healerUnitID != 0) {
                        if (entity.unitUID == DAT_UnitsState::instance.units[healerUnitID].uid) {
                            unitState = DAT_UnitsState::instance.units[healerUnitID].state.generic;
                            if (unitState == Map::Units::States::US_AIM_WEAPONUnk || unitState == Map::Units::States::US_FIRE_WEAPONUnk) {
                                continue;
                            }
                        }
                        entity.unitID_healer = 0;
                    }

                    auto entityArea = static_cast<short>(DAT_TileMapState::instance.PathConnectionLayer[entity.tile]);
                    
                    if ((entityArea == unitArea || 
                        (canNavigate = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea, 
                                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[unitID].owner, 
                                        static_cast<DWORD>(unitArea), static_cast<DWORD>(entityArea), 0), 
                        canNavigate != 0)) 
                        && (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY 
                            || (int workplaceID = DAT_UnitsState::instance.units[unitID].workplaceBuildingID_1, 
                                workplaceID == 0 || (MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, 
                                        DAT_DirectionAlgorithmState::ptr)(
                                        static_cast<int>(DAT_BuildingsState::instance.buildings[workplaceID].x),
                                        static_cast<int>(DAT_BuildingsState::instance.buildings[workplaceID].y),
                                        static_cast<int>(entity.xPosition),
                                        static_cast<int>(entity.yPosition)), 
                                    DAT_DirectionAlgorithmState::instance.distanceHigh < 31)))) {
                        
                        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult, 
                                DAT_DirectionAlgorithmState::ptr)(
                                static_cast<int>(DAT_UnitsState::instance.units[unitID].x),
                                static_cast<int>(DAT_UnitsState::instance.units[unitID].y),
                                static_cast<int>(entity.xPosition),
                                static_cast<int>(entity.yPosition));
                        
                        if (DAT_DirectionAlgorithmState::instance.distanceHigh < minDistance) {
                            minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                            nearestEntityIndex = i;
                        }
                    }
                }
            }
            return nearestEntityIndex;
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC