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
        uint _y;
        int _entityID;
        uint _entityID_2;
        uint _x;
        int _tile;
        int microY;
        uint _randomJitter;
        int microX;
        short _buildingID;
        _randomJitter = (uint)SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        microX = miniTileX + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_randomJitter & 0x3f][0];
        microY = miniTileY + DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[_randomJitter & 0x3f][1];
        _x = microX / 8;
        _y = microY / 8;
        if (((399 < _x) || (399 < _y)) || (*(char*)(_y * 400 + 0x21aec98 + _x) == '\0')) {
            return 0;
        }
        _tile = DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x;
        if (!(DAT_TileMapState::instance.LogicLayer[_tile] & 0x10300131U)) {
            _buildingID = DAT_TileMapState::instance.BuildingLayer[_tile];
            if (_buildingID) {
                switch (DAT_BuildingsState::instance.buildings[_buildingID].buildingType) {
                case Map::Buildings::BT_GATEHOUSELARGE:
                case Map::Buildings::BT_GATEHOUSESMALL:
                case Map::Buildings::BT_TOWER1:
                case Map::Buildings::BT_TOWER2:
                case Map::Buildings::BT_TOWER3:
                case Map::Buildings::BT_TOWER4:
                case Map::Buildings::BT_TOWER5:
                    goto switchD_0040539c_caseD_2d;
                }
            }
            _entityID = MACRO_CALL_MEMBER(
                Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(_tile);
            if (!_entityID) {
                if (_buildingID) {
                    MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::lightUpBuilding, DAT_BuildingsState::ptr)(
                        (int)DAT_TileMapState::instance.BuildingLayer[_tile], playerID, fireIntensity);
                }
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x1000U)) {
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(
                        _tile, playerID);
                }
                _entityID_2 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, (undefined4)((int)(playerID)), 0, microX, microY, tileHeightMin8, 0, 0, 0,
                    Map::Entities::ET_FIRE, 0);
                if ((2 < two) && (!(DAT_TileMapState::instance.RandomLayer[_tile] & 3))) {
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity,
                        DAT_EntityState::ptr)(0, (undefined4)((int)(playerID)), 0, microX, microY, tileHeightMin8, 0, 0,
                        0, (EntityType)((int)(26)), 0);
                }
                if (_entityID_2) {
                    DAT_EntityState::instance.entityArray[_entityID_2].fireParameter_0xb6 = (short)two;
                    DAT_EntityState::instance.entityArray[_entityID_2].fireIntensity = (short)fireIntensity;
                }
                return _entityID_2;
            }
            _buildingID = DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6;
            DAT_EntityState::instance.entityArray[_entityID].someTracker = 0;
            if (_buildingID < two) {
                DAT_EntityState::instance.entityArray[_entityID].fireParameter_0xb6 = (short)two;
            }
            DAT_EntityState::instance.entityArray[_entityID].unknownAnimationFrameRelated = 0;
        }
    switchD_0040539c_caseD_2d:
        return 0;
    }

}
}
