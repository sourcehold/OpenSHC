#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532700
        void UnitsState::shootProjectile(
            int unitID, EntityType projectileType, int targetX, int targetY, int targetZUnk)
        {
            int _offsetX = 0;
            int _offsetY = 0;
            int _height;
            int _targetedUnitID = 0;
            if (projectileType == OpenSHC::Map::Entities::ET_TREBUCHET) {
                if (this->units[unitID].field243_0x3b0 == 0) {
                    projectileType = OpenSHC::Map::Entities::ET_TREBUCHET;
                } else {
                    projectileType = OpenSHC::Map::Entities::ET_COW_FLYING;
                }
                _height = this->units[unitID].buildingHeight + 0x82 + this->units[unitID].terrainOrClimbHeight;
            } else if (projectileType == OpenSHC::Map::Entities::ET_CATAPULT) {
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
                if (this->units[unitID].field243_0x3b0 == 0) {
                    projectileType = OpenSHC::Map::Entities::ET_CATAPULT;
                } else {
                    projectileType = OpenSHC::Map::Entities::ET_COW_FLYING;
                }
                _height = this->units[unitID].buildingHeight + 0x38 + this->units[unitID].terrainOrClimbHeight;
            } else if (projectileType == OpenSHC::Map::Entities::ET_MANGONEL) {
                switch (this->units[unitID].facingDirection) {
                case 0:
                    _offsetY = -2;
                    break;
                case 1:
                case 4:
                    _offsetX = 0;
                    _offsetY = 0;
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
                projectileType = OpenSHC::Map::Entities::ET_MANGONEL;
                _height = this->units[unitID].buildingHeight + 64 + this->units[unitID].terrainOrClimbHeight;
            } else if (projectileType == OpenSHC::Map::Entities::ET_BALLISTA
                || projectileType == OpenSHC::Map::Entities::ET_FIREBALLISTA) {
                _height = this->units[unitID].buildingHeight + 25 + this->units[unitID].terrainOrClimbHeight;
            } else if (projectileType != (EntityType)8 && projectileType != ~OpenSHC::Map::Entities::ET_UNKNOWN) {
                _targetedUnitID = this->units[unitID].shootTargetedUnit;
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_A_HARCHER) {
                    _height = this->units[unitID].buildingHeight + 45 + this->units[unitID].terrainOrClimbHeight;
                } else {
                    /* This limits the range of arrow type projectiles */
                    _height = this->units[unitID].buildingHeight + 30 + this->units[unitID].terrainOrClimbHeight;
                }
            } else {
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
                _height = this->units[unitID].buildingHeight + 12 + this->units[unitID].terrainOrClimbHeight;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(
                unitID, this->units[unitID].owner, this->units[unitID].calculatedOwnerPlayerIndex,
                this->units[unitID].microXPosition + _offsetX, this->units[unitID].microYPosition + _offsetY, _height,
                targetX, targetY, targetZUnk, projectileType, _targetedUnitID);
            if (this->units[unitID].tribeID != 0) {
                DAT_TribesState::instance.tribes[this->units[unitID].tribeID].countdown2 = 500;
            }
        }

    }
}
}
