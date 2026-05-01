/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Entities/EntityState.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityTypeInt.hpp"
#include "OpenSHC/Map/Entities/ExtraEntityInfo.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::Entities::Entity;
        using OpenSHC::Map::Entities::EntityTypeInt;
        using OpenSHC::Map::Entities::ExtraEntityInfo;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000AC5E8
        class EntityState {
        public:
            undefined4 DAT_TotalEntityCount; // 0x00000000 length: 4
            undefined4 maxEntityCount; // 0x00000004 length: 4
            undefined4 every10Ticks; // 0x00000008 length: 4
            undefined4 field3_0xc; // 0x0000000C length: 4
            undefined4 DAT_FireCount; // 0x00000010 length: 4
            Entity entityArray[3000]; // 0x00000014 length: 696000
            ExtraEntityInfo seagullArray[100]; // 0x000A9ED4 length: 10000
            undefined4 field7_0xac5e4; // 0x000AC5E4 length: 4

        private:
            EntityState(EntityState const&);
            void operator=(EntityState const&);

            EntityState();
            ~EntityState();

        public:
            // Constructor
            EntityState* Constructor_EntityState();

            void clearEntityArrayAndSec1077();

            BOOLEnum meth_0x401150(int playerID, EntityTypeInt entityType);

            void setProjectileEntityValues2(int entityID, EntityTypeInt entityType);

            void setEntityParameters(int entityID, undefined4 entityType, int gmLookupValue);

            void drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2);

            void meth_0x401400(int param_1);

            void meth_0x401430(int param_1);

            void doSomethingWithOtherEntitiesOnTile(uint entityID);

            int getFireEntityIDAtTile(int tile);

            int updateAllFireEntitiesAtTile(int tile);

            void processFireDamageToUnitsAtTile(int tile, int playerID, int fireLowIntensity);

            void meth_0x401620();

            void meth_0x401690();

            int somethingWithSeparateAreas1(int unitID);

            void meth_0x401880(int param_1);

            void meth_0x401910(int param_1);

            void destroyEntitiesOnTile(int tile);

            undefined4 isBrazierNearby(int unitX, int unitY, int unitZ);

            void meth_0x401ae0(int param_1, undefined4 param_2);

            void swapEntityOwnership(int param_1, int param_2);

            void destroyEntitiesPart2(int param_1);

            void meth_0x402ae0(int param_1);

            undefined4 FUN_00402bd0(int param_1);

            int math_atan_1(int entityType, double param_3, int param_4, int heightDifference);

            int computeVelocity(undefined4 param_2, double param_3, int param_4, int param_5);

            uint meth_0x402e20(int x, int y, int height, int targetX, int targetY, int targetHeight, int param_7);

            void meth_0x4036f0(int entityID);

            void meth_0x403790(int ID_1077, int param_2, int param_3, int param_4, int param_5);

            void FUN_00403900(int param_1);

            int meth_0x4039b0(int entityID);

            void deleteEntity(uint entityID);

            void initializeProjectileVelocities(
                int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            void meth_0x403ff0(int param_1);

            int arrowShootingRelated(
                int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight);

            uint spawnProjectileEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX, int microY,
                int totalHeight, int targetX, int targetY, int targetZUnk, EntityTypeInt entityType, int param_11);

            void meth_0x405cf0(int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            void meth_0x405da0(int param_1);

            int createSeagull(int x, int y);

            void processSeaGulls(int seagullID);

            undefined4 processEntityHitBuildingOrUnit(int entityID);

            void meth_0x4081e0(uint entityID, undefined4 param_2, int param_3, int param_4);

            uint spawnEntityEffect2(
                undefined4 microX, undefined4 microY, undefined4 height, undefined4 entityType, int gmLookupValue);

            uint spawnEntityEffect1(
                short x, short y, undefined4 height, undefined4 entityType, int graphicType1, int graphicType2);

            undefined4 moveProjectileEntity(int entityID);

            void FUN_00408770(PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

            void updateEntities();
        };

        static_assert_cpp98_obj(sizeof(EntityState) == 706024, EntityState);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(EntityState, false, Address::SHC_3BB0A8C1_0x02350300) pDAT_EntityState;

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
