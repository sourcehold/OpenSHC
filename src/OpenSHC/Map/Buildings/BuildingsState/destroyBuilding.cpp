#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A7A0
        void BuildingsState::destroyBuilding(int buildingID)
        {
            this->buildings[buildingID].logicalState = BLS_REMOVE;
            if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                this->buildings[buildingID].noRubble = 1;
            }
            if (this->buildings[buildingID].buildingType == BT_SIGNPOST) {
                MACRO_CALL_MEMBER(BuildingsState_Func::destroySignpostData, this)(buildingID);
            }
            if (MACRO_CALL_MEMBER(BuildingsState_Func::isFearFactorBuilding, this)(buildingID) != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::recomputeAllFearFactors, DAT_BuildingsState::ptr)();
            }
            if (MACRO_CALL_MEMBER(BuildingsState_Func::isReligiousBuilding, this)(buildingID) != FALSE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, DAT_GameState::ptr)();
            }
            int const linkedUID = this->buildings[buildingID].uidWhenPlaced;
            if (linkedUID != 0) {
                for (int otherID = 1; otherID < this->maxBuildingsCount; ++otherID) {
                    if (this->buildings[otherID].logicalState != 0
                        && this->buildings[otherID].uidWhenPlaced == linkedUID) {
                        this->buildings[otherID].logicalState = BLS_REMOVE;
                        if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                            this->buildings[otherID].noRubble = 1;
                        }
                    }
                }
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }

    }
}
}
