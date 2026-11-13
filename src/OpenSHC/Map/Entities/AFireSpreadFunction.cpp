#include "../Entities.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004054E0
    void Entities::AFireSpreadFunction(int playerID, int x, int y, int height, int fireStrength, int fireIntensity)
    {
        int const random = SEC_RNG::instance.currentNumber2;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        x += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[random & 0x3f][0];
        y += DAT_EntityDefinedData::instance.XYOffsetsInAllDirections[random & 0x3f][1];
        uint const tileX = x / 8;
        uint const tileY = y / 8;
        if (tileX > 399 || tileY > 399
            || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[tileY * 400 + tileX] == 0) {
            return;
        }
        int const tile = DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile + tileX;
        int const fireID
            = MACRO_CALL_MEMBER(Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile);
        if (fireID != 0) {
            DAT_EntityState::instance.entityArray[fireID].someTracker = 0;
            if (fireStrength > DAT_EntityState::instance.entityArray[fireID].fireParameter_0xb6) {
                DAT_EntityState::instance.entityArray[fireID].fireParameter_0xb6 = fireStrength;
            }
            DAT_EntityState::instance.entityArray[fireID].unknownAnimationFrameRelated = 0;
            return;
        }
        if (DAT_TileMapState::instance.LogicLayer[tile]
            & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE | LogicHelpers::L_ROCKY
                | LogicHelpers::L_WALL_OR_GATEHOUSE | LogicHelpers::L_RIVER | LogicHelpers::L_FORD
                | LogicHelpers::L_CRENEL_VARIATIONUnk | LogicHelpers::L_FARM_FIELD_HOP
                | LogicHelpers::L_FARM_FIELD_DAIRY | LogicHelpers::L_KEEP_NON_MANOR_HOUSE)) {
            return;
        }
        short const buildingID = DAT_TileMapState::instance.BuildingLayer[tile];
        if (buildingID != 0
            && !MACRO_CALL_MEMBER(Buildings::BuildingsState_Func::lightUpBuilding, DAT_BuildingsState::ptr)(
                buildingID, playerID, fireIntensity)) {
            return;
        }
        if ((DAT_TileMapState::instance.LogicLayer[tile] & LogicHelpers::L_TREE)
            && !MACRO_CALL_MEMBER(LandscapeState_Func::lightUpTree, DAT_LandscapeState::ptr)(tile, playerID)) {
            return;
        }
        uint const newFireID = MACRO_CALL_MEMBER(Entities::EntityState_Func::spawnProjectileEntity,
            DAT_EntityState::ptr)(0, playerID, 0, x, y, height, 0, 0, 0, Entities::ET_FIRE, 0);
        if (newFireID != 0) {
            DAT_EntityState::instance.entityArray[newFireID].fireParameter_0xb6 = fireStrength;
            DAT_EntityState::instance.entityArray[newFireID].fireIntensity = fireIntensity;
        }
        if (fireStrength >= 3 && (DAT_TileMapState::instance.RandomLayer[tile] & 3) == 0) {
            MACRO_CALL_MEMBER(Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                0, playerID, 0, x, y, height, 0, 0, 0, Entities::EntityTypeInt__ET_EXPLOSION, 0);
        }
    }

}
}
