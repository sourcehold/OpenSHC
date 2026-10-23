#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A7A0
        void BuildingsState::destroyBuilding(int buildingID)
        {
            // Marks the building and all other parts that were placed together with it for removal
            this->buildings[buildingID].logicalState = BLS_REMOVE;
            if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                this->buildings[buildingID].noRubble = 1;
            }
            if (this->buildings[buildingID].buildingType == BT_SIGNPOST) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroySignpostData, this)(buildingID);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isFearFactorBuilding, this)(buildingID)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAllFearFactors, DAT_BuildingsState::ptr)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isReligiousBuilding, this)(buildingID)
                != FALSE) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, DAT_GameState::ptr)();
            }
            int placedUID = this->buildings[buildingID].uidWhenPlaced;
            if (placedUID != 0) {
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState != 0 && this->buildings[i].uidWhenPlaced == placedUID) {
                        this->buildings[i].logicalState = BLS_REMOVE;
                        if (DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding == 0) {
                            this->buildings[i].noRubble = 1;
                        }
                    }
                }
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 0;
        }

    }
}
}
