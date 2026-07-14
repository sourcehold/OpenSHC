/**
  path: 'OpenSHC/Map/Entities/EntityState.func.hpp'
*/

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Entities/EntityState.hpp"
#include "OpenSHC/Map/Entities/EntityTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Entities {
        namespace EntityState_Func {

            using OpenSHC::IO::PackagedFileMagicNumInt;
            using OpenSHC::Map::Entities::EntityTypeInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x004010E0,
                &EntityState::clearEntityArrayAndSec1077)
            clearEntityArrayAndSec1077;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (EntityState::*)(int, EntityTypeInt), false,
                Address::SHC_3BB0A8C1_0x00401150, &EntityState::playerHasEntityOfType)
            playerHasEntityOfType;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, EntityTypeInt), false, Address::SHC_3BB0A8C1_0x004011D0,
                &EntityState::setProjectileEntityValues2)
            setProjectileEntityValues2;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, undefined4, int), false,
                Address::SHC_3BB0A8C1_0x004012F0, &EntityState::setEntityParameters)
            setEntityParameters;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x00401380, &EntityState::drawEntityEffect)
            drawEntityEffect;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401400, &EntityState::beginEntityDeath)
            beginEntityDeath;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401430, &EntityState::tickEntityLifetime)
            tickEntityLifetime;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(uint), false, Address::SHC_3BB0A8C1_0x00401460,
                &EntityState::unlinkEntityFromTileChain)
            unlinkEntityFromTileChain;

            MACRO_FUNCTION_RESOLVER(
                int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401540, &EntityState::getFireEntityIDAtTile)
            getFireEntityIDAtTile;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401570,
                &EntityState::updateAllFireEntitiesAtTile)
            updateAllFireEntitiesAtTile;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004015D0,
                &EntityState::processFireDamageToUnitsAtTile)
            processFireDamageToUnitsAtTile;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x00401620,
                &EntityState::rebuildFireTileOccupancy)
            rebuildFireTileOccupancy;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x00401690,
                &EntityState::markUnitsWithActiveEntity)
            markUnitsWithActiveEntity;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004016E0,
                &EntityState::findNearestReachablePoisonCow)
            findNearestReachablePoisonCow;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401880,
                &EntityState::refreshPoisonCloudsNearUnit)
            refreshPoisonCloudsNearUnit;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401910,
                &EntityState::assignPoisonCloudToEntity)
            assignPoisonCloudToEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004019D0,
                &EntityState::destroyEntitiesOnTile)
            destroyEntitiesOnTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (EntityState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00401A50,
                &EntityState::isBrazierNearby)
            isBrazierNearby;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00401AE0,
                &EntityState::reassignEntityOwnership)
            reassignEntityOwnership;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00401B20,
                &EntityState::swapEntityOwnership)
            swapEntityOwnership;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401B60, &EntityState::destroyEntitiesPart2)
            destroyEntitiesPart2;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00402AE0,
                &EntityState::stepEntityMicroMovement)
            stepEntityMicroMovement;

            MACRO_FUNCTION_RESOLVER(undefined (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x00402BD0,
                &EntityState::heightDeltaToSpriteIndex)
            heightDeltaToSpriteIndex;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int, double, int, int), false,
                Address::SHC_3BB0A8C1_0x00402C50, &EntityState::math_atan_1)
            math_atan_1;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(undefined4, double, int, int), false,
                Address::SHC_3BB0A8C1_0x00402DA0, &EntityState::computeVelocity)
            computeVelocity;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00402E20, &EntityState::traceLineOfSight)
            traceLineOfSight;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004036F0,
                &EntityState::updateEntitySubtilePixelOffset)
            updateEntitySubtilePixelOffset;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00403790, &EntityState::setupSeagullMovement)
            setupSeagullMovement;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00403900,
                &EntityState::removeEntityFromTileList)
            removeEntityFromTileList;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004039B0,
                &EntityState::activateProjectileEntity)
            activateProjectileEntity;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(uint), false, Address::SHC_3BB0A8C1_0x004039F0, &EntityState::deleteEntity)
            deleteEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00403A20, &EntityState::initializeProjectileVelocities)
            initializeProjectileVelocities;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00403FF0,
                &EntityState::bounceProjectileOffWall)
            bounceProjectileOffWall;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00404A10, &EntityState::checkProjectileLineOfSight)
            checkProjectileLineOfSight;

            MACRO_FUNCTION_RESOLVER(
                uint (EntityState::*)(int, undefined4, uint, int, int, int, int, int, int, EntityTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x00404AE0, &EntityState::spawnProjectileEntity)
            spawnProjectileEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00405CF0, &EntityState::launchProjectileAt)
            launchProjectileAt;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00405DA0,
                &EntityState::spawnProjectileImpactFragments)
            spawnProjectileImpactFragments;

            MACRO_FUNCTION_RESOLVER(
                int (EntityState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00406650, &EntityState::createSeagull)
            createSeagull;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00406900, &EntityState::processSeaGulls)
            processSeaGulls;

            MACRO_FUNCTION_RESOLVER(undefined4 (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00407190,
                &EntityState::processEntityHitBuildingOrUnit)
            processEntityHitBuildingOrUnit;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(uint, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x004081E0, &EntityState::updateProjectileHeight)
            updateProjectileHeight;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(undefined4, undefined4, undefined4, undefined4, int), false,
                Address::SHC_3BB0A8C1_0x004082A0, &EntityState::spawnEntityEffect2)
            spawnEntityEffect2;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(short, short, undefined4, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x004083A0, &EntityState::spawnEntityEffect1)
            spawnEntityEffect1;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004084A0,
                &EntityState::moveProjectileEntity)
            moveProjectileEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00408770, &EntityState::migrateEntityDataForMapVersion)
            migrateEntityDataForMapVersion;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x004087C0, &EntityState::updateEntities)
            updateEntities;

        } // namespace EntityState_Func
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
