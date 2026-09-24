#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040D400
        void BuildingsState::setupMercenaryPostCampgroundPositions(int playerID)
        {
            // Matching note: The original unrolls the three formation parts, reproduced here. The
            // remaining differences are register allocation and the pointer based inner loop of the original.
            int paradeGround2 = 0;
            int paradeGround3 = 0;
            int paradeGround4 = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameState::instance.playerDataArray[playerID].structure), 0,
                &DAT_GameState::instance.playerDataArray[playerID].structure);
            DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id <= 0) {
                return;
            }

            // Find the three parade grounds of the mercenary post
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && this->buildings[i].owner == playerID
                    && (this->buildings[i].buildingType == BT_PARADEGROUND2
                        || this->buildings[i].buildingType == BT_PARADEGROUND3
                        || this->buildings[i].buildingType == BT_PARADEGROUND4)
                    && DAT_BuildingsState::instance
                            .buildings[(short)DAT_BuildingsState::instance.buildings[i].quarryStockpileID]
                            .buildingType
                        == BT_MERCENARYPOST) {
                    if (this->buildings[i].buildingType == BT_PARADEGROUND2) {
                        paradeGround2 = i;
                    } else if (this->buildings[i].buildingType == BT_PARADEGROUND3) {
                        paradeGround3 = i;
                    } else if (this->buildings[i].buildingType == BT_PARADEGROUND4) {
                        paradeGround4 = i;
                    }
                }
            }
            if (paradeGround2 == 0 || paradeGround3 == 0 || paradeGround4 == 0) {
                return;
            }

            // Every formation uses 24 positions on each of the three parade grounds. The structure holds 6 formations
            // of 72 positions each, accessed as a flat array.
            DAT_GameState::instance.playerDataArray[playerID].structureRelated1 = 72;
            // Note: not initialised in the original, an unknown part type keeps the previous parade ground
            int paradeGround;
            int x;
            int y;
            for (int formation = 0; formation < 6; ++formation) {
                // The three parts of the formation are written out in the original
                if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][0] == 0) {
                    paradeGround = paradeGround2;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][0]
                    == 1) {
                    paradeGround = paradeGround3;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][0]
                    == 2) {
                    paradeGround = paradeGround4;
                }
                x = (short)this->buildings[paradeGround].x;
                y = (short)this->buildings[paradeGround].y;
                for (int k = 0; k < 24; ++k) {
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 0 + k]
                        .x = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .x
                        + x;
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 0 + k]
                        .y = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .y
                        + y;
                }
                if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][1] == 0) {
                    paradeGround = paradeGround2;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][1]
                    == 1) {
                    paradeGround = paradeGround3;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][1]
                    == 2) {
                    paradeGround = paradeGround4;
                }
                x = (short)this->buildings[paradeGround].x;
                y = (short)this->buildings[paradeGround].y;
                for (int k = 0; k < 24; ++k) {
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 24 + k]
                        .x = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .x
                        + x;
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 24 + k]
                        .y = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .y
                        + y;
                }
                if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][2] == 0) {
                    paradeGround = paradeGround2;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][2]
                    == 1) {
                    paradeGround = paradeGround3;
                } else if (DAT_BuildingDefinedData::instance.PlayerDataUnknownStructureRelatedArray_2[formation][2]
                    == 2) {
                    paradeGround = paradeGround4;
                }
                x = (short)this->buildings[paradeGround].x;
                y = (short)this->buildings[paradeGround].y;
                for (int k = 0; k < 24; ++k) {
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 48 + k]
                        .x = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .x
                        + x;
                    DAT_GameState::instance.playerDataArray[playerID]
                        .structure.mercenaryOutpostCampgroundLocations[formation * 72 + 48 + k]
                        .y = DAT_BuildingDefinedData::instance
                                 .PlayerDataUnknownStructureRelatedArray_3[DAT_BuildingDefinedData::instance
                                         .PlayerDataUnknownStructureRelatedArray_1[formation]][k]
                                 .y
                        + y;
                }
            }
        }

    }
}
}
