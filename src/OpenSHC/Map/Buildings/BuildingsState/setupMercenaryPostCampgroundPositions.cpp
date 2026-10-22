#include "../BuildingsState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D400
        void BuildingsState::setupMercenaryPostCampgroundPositions(int playerID)
        {
            int paradeGround1 = 0;
            int paradeGround2 = 0;
            int paradeGround3 = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameState::instance.playerDataArray[playerID].structure), 0,
                &DAT_GameState::instance.playerDataArray[playerID].structure);
            DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id <= 0) {
                return;
            }
            int buildingID;
            for (buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == 0
                    || this->buildings[buildingID].logicalState == BLS_REMOVE
                    || this->buildings[buildingID].owner != playerID) {
                    continue;
                }
                if (this->buildings[buildingID].buildingType != BT_PARADEGROUND2
                    && this->buildings[buildingID].buildingType != BT_PARADEGROUND3
                    && this->buildings[buildingID].buildingType != BT_PARADEGROUND4) {
                    continue;
                }
                // quarryStockpileID holds the linked building here.
                if (DAT_BuildingsState::instance.buildings[this->buildings[buildingID].quarryStockpileID].buildingType
                    != BT_MERCENARYPOST) {
                    continue;
                }
                if (this->buildings[buildingID].buildingType == BT_PARADEGROUND2) {
                    paradeGround1 = buildingID;
                } else if (this->buildings[buildingID].buildingType == BT_PARADEGROUND3) {
                    paradeGround2 = buildingID;
                } else if (this->buildings[buildingID].buildingType == BT_PARADEGROUND4) {
                    paradeGround3 = buildingID;
                }
            }
            if (paradeGround1 == 0 || paradeGround2 == 0 || paradeGround3 == 0) {
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 72;
            // The header splits this 6 x 72 location table into separately named fields.
            for (int formation = 0; formation < 6; ++formation) {
                int const shape = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_1[formation];
                // The loop index above is reused, so an unknown selector keeps the previous building.
                int const selector0
                    = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][0];
                if (selector0 == 0) {
                    buildingID = paradeGround1;
                } else if (selector0 == 1) {
                    buildingID = paradeGround2;
                } else if (selector0 == 2) {
                    buildingID = paradeGround3;
                }
                int const x0 = this->buildings[buildingID].x;
                int const y0 = this->buildings[buildingID].y;
                for (int i = 0; i < 24; ++i) {
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + i]
                        .x
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].x + x0;
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + i]
                        .y
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].y + y0;
                }
                int const selector1
                    = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][1];
                if (selector1 == 0) {
                    buildingID = paradeGround1;
                } else if (selector1 == 1) {
                    buildingID = paradeGround2;
                } else if (selector1 == 2) {
                    buildingID = paradeGround3;
                }
                int const x1 = this->buildings[buildingID].x;
                int const y1 = this->buildings[buildingID].y;
                for (int i = 0; i < 24; ++i) {
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + 24 + i]
                        .x
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].x + x1;
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + 24 + i]
                        .y
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].y + y1;
                }
                int const selector2
                    = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][2];
                if (selector2 == 0) {
                    buildingID = paradeGround1;
                } else if (selector2 == 1) {
                    buildingID = paradeGround2;
                } else if (selector2 == 2) {
                    buildingID = paradeGround3;
                }
                int const x2 = this->buildings[buildingID].x;
                int const y2 = this->buildings[buildingID].y;
                for (int i = 0; i < 24; ++i) {
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + 48 + i]
                        .x
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].x + x2;
                    (&DAT_GameState::instance.playerDataArray[playerID]
                            .structure.mercenaryOutpostCampgroundLocations[0])[formation * 72 + 48 + i]
                        .y
                        = DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_3[shape][i].y + y2;
                }
            }
        }

    }
}
}
