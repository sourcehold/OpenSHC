#include "../BuildingsState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E040
        void BuildingsState::setupEngineersGuildParagroundPositions(int playerID)
        {
            int paradeGroundID = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations), 0,
                DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations);
            DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id <= 0) {
                return;
            }
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState != 0
                    && this->buildings[buildingID].logicalState != BLS_REMOVE
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == BT_PARADEGROUND) {
                    paradeGroundID = buildingID;
                }
            }
            if (paradeGroundID == 0) {
                return;
            }
            DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 25;
            int const x = this->buildings[paradeGroundID].x;
            int const y = this->buildings[paradeGroundID].y;
            for (int i = 0; i < 25; ++i) {
                DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[i].x
                    = DAT_BuildingDefinedData::instance.EngineersParagroundOffsets[i].x + x;
                DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations[i].y
                    = DAT_BuildingDefinedData::instance.EngineersParagroundOffsets[i].y + y;
            }
        }

    }
}
}
