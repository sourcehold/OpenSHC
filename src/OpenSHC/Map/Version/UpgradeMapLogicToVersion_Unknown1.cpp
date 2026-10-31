#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005011F0
    void Version::UpgradeMapLogicToVersion_Unknown1()
    {
        for (int tile = 0; tile < OpenSHC::Map::MC_MAP_TILES_COUNT; ++tile) {
            if ((DAT_TileMapState::instance.MiscDisplayLayer[tile] & 0x20) != 0) {
                short buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
                int type;
                if (buildingID == 0
                    || (type = DAT_BuildingsState::instance.buildings[buildingID].buildingType)
                        < Buildings::BT_GATEHOUSELARGE
                    || type > Buildings::BT_WOODGATE1) {
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] &= ~0x20;
                }
            }
        }
    }

}
}
