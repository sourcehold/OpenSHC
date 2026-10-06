#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532700
        void UnitsState::shootProjectile(
            int unitID, EntityType projectileType, int targetX, int targetY, int targetZUnk)
        {
            if (projectileType == OpenSHC::Map::Entities::ET_TREBUCHET) {
                if (DAT_UnitsState::instance.units[unitID].field243_0x3b0 == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 0x82 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_TREBUCHET, 0);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 0x82 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_COW_FLYING, 0);
                }
            } else if (projectileType == OpenSHC::Map::Entities::ET_CATAPULT) {
                int _offsetX = 0;
                int _offsetY = 0;
                switch (this->units[unitID].facingDirection) {
                case 0:
                    _offsetY = -7;
                    break;
                case 1:
                    _offsetX = 4;
                    _offsetY = -4;
                    break;
                case 2:
                    _offsetX = 7;
                    break;
                case 3:
                    _offsetX = 4;
                    _offsetY = 4;
                    break;
                case 4:
                    _offsetY = 7;
                    break;
                case 5:
                    _offsetX = -4;
                    _offsetY = 4;
                    break;
                case 6:
                    _offsetX = -7;
                    break;
                case 7:
                    _offsetX = -4;
                    _offsetY = -4;
                }
                if (DAT_UnitsState::instance.units[unitID].field243_0x3b0 == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition + _offsetX, this->units[unitID].microYPosition + _offsetY,
                        this->units[unitID].buildingHeight + 0x38 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_CATAPULT, 0);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition + _offsetX, this->units[unitID].microYPosition + _offsetY,
                        this->units[unitID].buildingHeight + 0x38 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, OpenSHC::Map::Entities::ET_COW_FLYING, 0);
                }
            } else if (projectileType == OpenSHC::Map::Entities::ET_MANGONEL) {
                int _offsetX = 0;
                int _offsetY = 0;
                switch (this->units[unitID].facingDirection) {
                case 0:
                    _offsetY = -2;
                    break;
                case 1:
                case 4:
                    _offsetY = 0;
                    _offsetX = 0;
                    break;
                case 2:
                case 6:
                    _offsetX = 0;
                    break;
                case 3:
                    _offsetX = -1;
                    _offsetY = 1;
                    break;
                case 5:
                    _offsetX = -2;
                    _offsetY = 2;
                    break;
                case 7:
                    _offsetX = 1;
                    _offsetY = -1;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                    this->units[unitID].microXPosition + _offsetX, this->units[unitID].microYPosition + _offsetY,
                    this->units[unitID].buildingHeight + 64 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, OpenSHC::Map::Entities::ET_MANGONEL, 0);
            } else if (projectileType == OpenSHC::Map::Entities::ET_BALLISTA
                || projectileType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                    this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                    this->units[unitID].buildingHeight + 25 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, projectileType, 0);
            } else if (projectileType != (EntityType)8 && projectileType != ~OpenSHC::Map::Entities::ET_UNKNOWN) {
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 45 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, projectileType, this->units[unitID].shootTargetedUnit);
                } else {
                    /* This limits the range of arrow type projectiles */
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                        this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                        this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                        this->units[unitID].buildingHeight + 30 + this->units[unitID].terrainOrClimbHeight, targetX,
                        targetY, targetZUnk, projectileType, this->units[unitID].shootTargetedUnit);
                }
            } else {
                int _offsetX = 0;
                int _offsetY = 0;
                switch (this->units[unitID].facingDirection) {
                case 0:
                    _offsetY = -4;
                    break;
                case 1:
                    _offsetX = 10;
                    _offsetY = -4;
                    break;
                case 2:
                    _offsetX = 10;
                    break;
                case 3:
                    _offsetX = 10;
                    _offsetY = 4;
                    break;
                case 4:
                    _offsetY = 4;
                    break;
                case 5:
                    _offsetY = 4;
                    _offsetX = -10;
                    break;
                case 6:
                    _offsetX = -10;
                    break;
                case 7:
                    _offsetY = -4;
                    _offsetX = -10;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(unitID,
                    this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                    this->units[unitID].microXPosition + _offsetX, this->units[unitID].microYPosition + _offsetY,
                    this->units[unitID].buildingHeight + 12 + this->units[unitID].terrainOrClimbHeight, targetX,
                    targetY, targetZUnk, projectileType, 0);
            }
            int _tribeID = this->units[unitID].tribeID;
            if (_tribeID != 0) {
                DAT_TribesState::instance.tribes[_tribeID].countdown2 = 500;
            }
        }

    }
}
}
