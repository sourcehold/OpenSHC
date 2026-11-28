#include "../../Map.func.hpp"
#include "../Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Entities::EntityType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004052E0
    uint Entities::IgniteFireAtMiniTile(
        int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity)
    {
        uint const randomJitter = (uint)SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        int const microX = miniTileX + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomJitter & 0x3f][0];
        int const microY = miniTileY + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[randomJitter & 0x3f][1];
        uint const x = microX / 8;
        uint const y = microY / 8;
        if (x > 399 || y > 399 || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
            return 0;
        }
        int const tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        if (!(DAT_TileMapState::instance.LogicLayer[tile] & 0x10300131U)) {
            short const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
            if (buildingID) {
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case Map::Buildings::BT_GATEHOUSELARGE:
                case Map::Buildings::BT_GATEHOUSESMALL:
                case Map::Buildings::BT_TOWER1:
                case Map::Buildings::BT_TOWER2:
                case Map::Buildings::BT_TOWER3:
                case Map::Buildings::BT_TOWER4:
                case Map::Buildings::BT_TOWER5:
                    return 0;
                }
            }
            int const fireID
                = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile);
            if (fireID) {
                DAT_EntityState::instance.entityArray[fireID].someTracker = 0;
                if (two > DAT_EntityState::instance.entityArray[fireID].fireParameter_0xb6) {
                    DAT_EntityState::instance.entityArray[fireID].fireParameter_0xb6 = (short)two;
                }
                DAT_EntityState::instance.entityArray[fireID].unknownAnimationFrameRelated = 0;
                return 0;
            }
            if (buildingID) {
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::lightUpBuilding, DAT_BuildingsState::ptr)(
                    DAT_TileMapState::instance.BuildingLayer[tile], playerID, fireIntensity);
            }
            if (DAT_TileMapState::instance.LogicLayer[tile] & 0x1000U) {
                MACRO_CALL_MEMBER(Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(tile, playerID);
            }
            uint const entityID
                = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                    0, playerID, 0, microX, microY, tileHeightMin8, 0, 0, 0, Map::Entities::ET_FIRE, 0);
            if (two > 2 && !(DAT_TileMapState::instance.RandomLayer[tile] & 3)) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                    0, playerID, 0, microX, microY, tileHeightMin8, 0, 0, 0, (EntityType)26, 0);
            }
            if (entityID) {
                DAT_EntityState::instance.entityArray[entityID].fireParameter_0xb6 = (short)two;
                DAT_EntityState::instance.entityArray[entityID].fireIntensity = (short)fireIntensity;
            }
            return entityID;
        }
        return 0;
    }

}
}
