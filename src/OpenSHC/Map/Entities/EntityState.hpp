/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/EntityState.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/ExtraEntityInfo.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::IO::PackagedFileMagicNum;
        using OpenSHC::Map::Entities::Entity;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Entities::ExtraEntityInfo;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000AC5E8
        class EntityState {
        public:
            undefined4 totalEntityCount; // 0x00000000 length: 4
            undefined4 maxEntityCount; // 0x00000004 length: 4
            undefined4 every10Ticks; // 0x00000008 length: 4
            int lineOfSightClearanceSteps; // 0x0000000C length: 4
            undefined4 fireCount; // 0x00000010 length: 4
            Entity entityArray[3000]; // 0x00000014 length: 696000
            ExtraEntityInfo seagullArray[100]; // 0x000A9ED4 length: 10000
            DWORD classConstructionTime; // 0x000AC5E4 length: 4

        private:
            EntityState(EntityState const&);
            void operator=(EntityState const&);

        public:
            EntityState() {};
            ~EntityState() {};

            // Constructor
            EntityState* Constructor_EntityState();

            void clearEntityArrayAndSec1077();

            BOOLEnum playerHasEntityOfType(int playerID, EntityType entityType);

            void setProjectileEntityValues2(int entityID, EntityType entityType);

            void setEntityParameters(int entityID, undefined4 entityType, int gmLookupValue);

            void drawEntityEffect(int entityID, undefined4 entityType, int graphicType1, int graphicType2);

            void markEntityDestroyed(int param_1);

            void tickEntityDecayCounter(int param_1);

            void doSomethingWithOtherEntitiesOnTile(uint entityID);

            int getFireEntityIDAtTile(int tile);

            int updateAllFireEntitiesAtTile(int tile);

            void processFireDamageToUnitsAtTile(int tile, int playerID, int fireLowIntensity);

            void recountActiveFires();

            void flagUnitsWithActiveEntity();

            int somethingWithSeparateAreas1(int unitID);

            void refreshPoisonCloudNearUnit(int param_1);

            void assignPoisonCloudTargetEntity(int param_1);

            void destroyEntitiesOnTile(int tile);

            undefined4 isBrazierNearby(int unitX, int unitY, int unitZ);

            void reassignEntitiesOwner(int param_1, undefined4 param_2);

            void swapEntityOwnership(int param_1, int param_2);

            void destroyEntitiesPart2(int param_1);

            void updateEntityMicroMovement(int param_1);

            undefined4 angleToRotationFrameIndex(int param_1);

            int math_atan_1(int entityType, double param_3, int param_4, int heightDifference);

            int computeVelocity(undefined4 param_2, double param_3, int param_4, int param_5);

            uint computeLineOfSightDistance(
                int x, int y, int height, int targetX, int targetY, int targetHeight, int param_7);

            void calculateEntityDrawOffset(int entityID);

            void initializeSeagullMovementVector(int ID_1077, int param_2, int param_3, int param_4, int param_5);

            void removeEntityFromTileLinkedList(int param_1);

            int activateProjectileEntity(int entityID);

            void deleteEntity(uint entityID);

            void initializeProjectileVelocities(
                int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            void handleProjectileWallBounce(int param_1);

            int arrowShootingRelated(
                int microX, int microY, int height, int destMicroX, int destMicroY, int destHeight);

            uint spawnProjectileEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX, int microY,
                int totalHeight, int targetX, int targetY, int targetZUnk, EntityType entityType, int param_11);

            void setProjectileTargetPosition(
                int entityID, int x, int y, int height, int targetX, int targetY, int targetZ);

            void spawnProjectileImpactDebris(int param_1);

            int createSeagull(int x, int y);

            void processSeaGulls(int seagullID);

            undefined4 processEntityHitBuildingOrUnit(int entityID);

            void updateProjectileHeightAndCollision(uint entityID, undefined4 param_2, int param_3, int param_4);

            uint spawnEntityEffect2(
                undefined4 microX, undefined4 microY, undefined4 height, undefined4 entityType, int gmLookupValue);

            uint spawnEntityEffect1(
                short x, short y, undefined4 height, undefined4 entityType, int graphicType1, int graphicType2);

            BOOLEnum moveProjectileEntity(int entityID);

            void handleMapVersionUpgrade(
                PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion);

            void updateEntities();
        };

        static_assert_cpp98_obj(sizeof(EntityState) == 706024, EntityState);

#pragma pack(pop)

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
