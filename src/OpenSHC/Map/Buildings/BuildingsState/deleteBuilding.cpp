#include "../BuildingsState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00421890
        void BuildingsState::deleteBuilding(uint buildingID)
        {
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                && DAT_BuildingsState::instance.menuSelectedBuildingID == buildingID) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::subtractResourcesStoredInBuilding, this)(buildingID);
            MACRO_CALL_MEMBER(Units::UnitsState_Func::setTowerSiegeEngineToIdle, DAT_UnitsState::ptr)(buildingID);
            if ((this->buildings[buildingID].buildingType == BT_OUTPOST_EUROPEAN
                    || this->buildings[buildingID].buildingType == BT_OUTPOST_ARABIAN)
                && this->buildings[buildingID].tribeID > 0
                && DAT_TribesState::instance.tribes[this->buildings[buildingID].tribeID].uid
                    == this->buildings[buildingID].tribeUID) {
                MACRO_CALL_MEMBER(AI::AICState_Func::aiRegisterTribeAndAssignTarget, DAT_AICState::ptr)(
                    this->buildings[buildingID].tribeID, this->buildings[buildingID].tribeUID);
            }
            if (this->buildings[buildingID].buildingType == BT_OXTETHER) {
                MACRO_CALL_MEMBER(Units::UnitsState_Func::removeUnitFromItsTribe, DAT_UnitsState::ptr)(
                    this->buildings[buildingID].oxTetherRelatedUnitID,
                    this->buildings[buildingID].oxTetherRelatedUnitUID);
            } else if (this->buildings[buildingID].buildingType == BT_CATHEDRAL) {
                DAT_GameState::instance.mapAndTime.cathedralRelated1 = 1;
            }
            MACRO_CALL_MEMBER(BuildingsState_Func::spawnCrowForBuilding, this)(buildingID);
            MACRO_CALL_MEMBER(TileMapState_Func::clearBuildingFromTerrain, DAT_TileMapState::ptr)(buildingID);
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::updatePrimaryBuildingPlayerDataReferences,
                DAT_GameState::ptr)(buildingID);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->buildings[buildingID]), 0, &this->buildings[buildingID]);
        }

    }
}
}
