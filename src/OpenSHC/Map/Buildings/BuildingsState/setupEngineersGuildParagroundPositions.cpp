#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040E040
        void BuildingsState::setupEngineersGuildParagroundPositions(int playerID)
        {
            int paradeGround = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations), 0,
                DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocations);
            DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 0;
            if (DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id <= 0) {
                return;
            }

            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState != 0 && this->buildings[i].logicalState != BLS_REMOVE
                    && this->buildings[i].owner == playerID && this->buildings[i].buildingType == BT_PARADEGROUND) {
                    paradeGround = i;
                }
            }
            if (paradeGround == 0) {
                return;
            }

            DAT_GameState::instance.playerDataArray[playerID].engineersParadegroundLocationsTotal = 25;
            int x = (short)this->buildings[paradeGround].x;
            int y = (short)this->buildings[paradeGround].y;
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
