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
                Address::SHC_3BB0A8C1_0x00401150, &EntityState::meth_0x401150)
            meth_0x401150;

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
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401400, &EntityState::meth_0x401400)
            meth_0x401400;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401430, &EntityState::meth_0x401430)
            meth_0x401430;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(uint), false, Address::SHC_3BB0A8C1_0x00401460,
                &EntityState::doSomethingWithOtherEntitiesOnTile)
            doSomethingWithOtherEntitiesOnTile;

            MACRO_FUNCTION_RESOLVER(
                int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401540, &EntityState::getFireEntityIDAtTile)
            getFireEntityIDAtTile;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401570,
                &EntityState::updateAllFireEntitiesAtTile)
            updateAllFireEntitiesAtTile;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004015D0,
                &EntityState::processFireDamageToUnitsAtTile)
            processFireDamageToUnitsAtTile;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x00401620, &EntityState::meth_0x401620)
            meth_0x401620;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x00401690, &EntityState::meth_0x401690)
            meth_0x401690;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004016E0,
                &EntityState::somethingWithSeparateAreas1)
            somethingWithSeparateAreas1;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401880, &EntityState::meth_0x401880)
            meth_0x401880;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401910, &EntityState::meth_0x401910)
            meth_0x401910;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004019D0,
                &EntityState::destroyEntitiesOnTile)
            destroyEntitiesOnTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (EntityState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00401A50,
                &EntityState::isBrazierNearby)
            isBrazierNearby;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00401AE0,
                &EntityState::meth_0x401ae0)
            meth_0x401ae0;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00401B20,
                &EntityState::swapEntityOwnership)
            swapEntityOwnership;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00401B60, &EntityState::destroyEntitiesPart2)
            destroyEntitiesPart2;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00402AE0, &EntityState::meth_0x402ae0)
            meth_0x402ae0;

            MACRO_FUNCTION_RESOLVER(
                undefined4 (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00402BD0, &EntityState::FUN_00402bd0)
            FUN_00402bd0;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int, double, int, int), false,
                Address::SHC_3BB0A8C1_0x00402C50, &EntityState::math_atan_1)
            math_atan_1;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(undefined4, double, int, int), false,
                Address::SHC_3BB0A8C1_0x00402DA0, &EntityState::computeVelocity)
            computeVelocity;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00402E20, &EntityState::meth_0x402e20)
            meth_0x402e20;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004036F0, &EntityState::meth_0x4036f0)
            meth_0x4036f0;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00403790, &EntityState::meth_0x403790)
            meth_0x403790;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00403900, &EntityState::FUN_00403900)
            FUN_00403900;

            MACRO_FUNCTION_RESOLVER(
                int (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004039B0, &EntityState::meth_0x4039b0)
            meth_0x4039b0;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(uint), false, Address::SHC_3BB0A8C1_0x004039F0, &EntityState::deleteEntity)
            deleteEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00403A20, &EntityState::initializeProjectileVelocities)
            initializeProjectileVelocities;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00403FF0, &EntityState::meth_0x403ff0)
            meth_0x403ff0;

            MACRO_FUNCTION_RESOLVER(int (EntityState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00404A10, &EntityState::arrowShootingRelated)
            arrowShootingRelated;

            MACRO_FUNCTION_RESOLVER(
                uint (EntityState::*)(int, undefined4, uint, int, int, int, int, int, int, EntityTypeInt, int), false,
                Address::SHC_3BB0A8C1_0x00404AE0, &EntityState::spawnProjectileEntity)
            spawnProjectileEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(int, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00405CF0, &EntityState::meth_0x405cf0)
            meth_0x405cf0;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x00405DA0, &EntityState::meth_0x405da0)
            meth_0x405da0;

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
                Address::SHC_3BB0A8C1_0x004081E0, &EntityState::meth_0x4081e0)
            meth_0x4081e0;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(undefined4, undefined4, undefined4, undefined4, int), false,
                Address::SHC_3BB0A8C1_0x004082A0, &EntityState::spawnEntityEffect2)
            spawnEntityEffect2;

            MACRO_FUNCTION_RESOLVER(uint (EntityState::*)(short, short, undefined4, undefined4, int, int), false,
                Address::SHC_3BB0A8C1_0x004083A0, &EntityState::spawnEntityEffect1)
            spawnEntityEffect1;

            MACRO_FUNCTION_RESOLVER(undefined4 (EntityState::*)(int), false, Address::SHC_3BB0A8C1_0x004084A0,
                &EntityState::moveProjectileEntity)
            moveProjectileEntity;

            MACRO_FUNCTION_RESOLVER(void (EntityState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
                Address::SHC_3BB0A8C1_0x00408770, &EntityState::FUN_00408770)
            FUN_00408770;

            MACRO_FUNCTION_RESOLVER(
                void (EntityState::*)(), false, Address::SHC_3BB0A8C1_0x004087C0, &EntityState::updateEntities)
            updateEntities;

        } // namespace EntityState_Func
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
