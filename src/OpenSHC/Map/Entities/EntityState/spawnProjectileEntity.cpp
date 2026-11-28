#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00404AE0
        uint EntityState::spawnProjectileEntity(int unitID, undefined4 playerID1, uint ownerColorUnk, int microX,
            int microY, int totalHeight, int targetX, int targetY, int targetZUnk, EntityType entityType, int param_11)
        {
            bool bVar1;
            dword dVar2;
            short* psVar3;
            EntityTypeShort* pEVar4;
            uint uVar5;
            uint uVar6;
            short sVar7;
            uint entityID;
            bVar1 = false;
            if (((0x2b < (int)entityType) && ((int)entityType < 0x5b)) || (0x5e < (int)entityType)) {
                return 0;
            }
            if (entityType == ~Map::Entities::ET_UNKNOWN) {
                entityID = 0;
                entityType = ((EntityType)8);
            } else if (entityType - ((EntityType)0x28) < 8) {
                entityID = 1;
                psVar3 = &this->entityArray[1].logicalState;
                do {
                    if (*psVar3 == 0)
                        break;
                    if (0x17 < (int)entityID) {
                        return 0;
                    }
                    entityID = entityID + 1;
                    psVar3 = psVar3 + 0x74;
                } while ((int)entityID < 0x19);
            } else {
                entityID = this->every10Ticks;
                if (this->every10Ticks < 3000) {
                    psVar3 = &this->entityArray[this->every10Ticks].logicalState;
                    do {
                        if (*psVar3 == 0)
                            break;
                        if (0xbb6 < (int)entityID) {
                            switch (entityType) {
                            case Map::Entities::ET_ARROW_AND_DEFAULT:
                            case Map::Entities::ET_CATAPULT:
                            case Map::Entities::ET_TREBUCHET:
                            case Map::Entities::ET_MANGONEL:
                            case Map::Entities::ET_CROSSBOWARROW:
                            case ((EntityType)8):
                            case Map::Entities::ET_COW_POISON_CLOUD:
                            case Map::Entities::ET_COW_FLYING:
                            case ((EntityType)0x18):
                            case ((EntityType)0x19):
                            case Map::Entities::EntityTypeInt__ET_EXPLOSION:
                            case Map::Entities::ET_SLINGER:
                            case Map::Entities::ET_FIRETHROWER:
                            case Map::Entities::ET_FIRETHROWER | Map::Entities::ET_ARROW_AND_DEFAULT:
                            case Map::Entities::ET_FIRETHROWER_UNTARGETED:
                            case Map::Entities::ET_FIREBALLISTA:
                            case ((EntityType)0x5b):
                            case ((EntityType)0x5c):
                            case ((EntityType)0x5d):
                            case ((EntityType)0x5e):
                                this->maxEntityCount = 3000;
                                entityID = 0x19;
                                pEVar4 = &this->entityArray[0x19].entityType;
                                break;
                            default:
                                goto switchD_00404bac_caseD_5;
                            }
                            goto LAB_00404bc5;
                        }
                        entityID = entityID + 1;
                        psVar3 = psVar3 + 0x74;
                    } while ((int)entityID < 3000);
                }
                this->every10Ticks = entityID;
                if (this->maxEntityCount <= (int)entityID) {
                    this->maxEntityCount = entityID + 1;
                }
            }
        LAB_00404c16:
            this->entityArray[entityID].rng_2 = 0;
            if (entityType == ((EntityType)0x5b)) {
                bVar1 = true;
                this->entityArray[entityID].rng_2 = 1;
                entityType = Map::Entities::ET_ARROW_AND_DEFAULT;
            } else if (entityType == Map::Entities::ET_FIREBALLISTA) {
                bVar1 = true;
                this->entityArray[entityID].field90_0xd0 = 1;
                entityType = Map::Entities::ET_BALLISTA;
            } else {
                if ((entityType == Map::Entities::ET_FIRETHROWER)
                    || (entityType == Map::Entities::ET_FIRETHROWER_UNTARGETED)) {
                    bVar1 = true;
                }
                if (entityType == ((EntityType)0x5c)) {
                    bVar1 = true;
                    this->entityArray[entityID].rng_2 = 1;
                    entityType = ((EntityType)0x18);
                } else if (entityType == ((EntityType)0x5d)) {
                    bVar1 = true;
                    this->entityArray[entityID].rng_2 = 2;
                    entityType = Map::Entities::ET_ARROW_AND_DEFAULT;
                } else if (entityType == ((EntityType)0x5e)) {
                    bVar1 = true;
                    this->entityArray[entityID].rng_2 = 2;
                    entityType = ((EntityType)0x18);
                } else if (entityType == ((EntityType)0x1b)) {
                    targetX = targetX + -0xa0 + ((int)SEC_RNG::instance.currentNumber2 % 0x50) * 4;
                    targetY = targetY + -0xa0 + (((int)SEC_RNG::instance.currentNumber2 >> 8) % 0x50) * 4;
                } else if (entityType == ((EntityType)0x20)) {
                    targetX = targetX + -0x18 + (int)SEC_RNG::instance.currentNumber2 % 0x30;
                    targetY = targetY + -0x18 + ((int)SEC_RNG::instance.currentNumber2 >> 8) % 0x30;
                }
            }
            switch (entityType) {
            case Map::Entities::ET_ARROW_AND_DEFAULT:
            case Map::Entities::ET_CATAPULT:
            case Map::Entities::ET_TREBUCHET:
            case Map::Entities::ET_MANGONEL:
            case Map::Entities::ET_CROSSBOWARROW:
            case Map::Entities::ET_BALLISTA:
            case Map::Entities::ET_COW_FLYING:
            case ((EntityType)0x18):
            case ((EntityType)0x19):
            case ((EntityType)0x1b):
            case ((EntityType)0x20):
            case Map::Entities::ET_SLINGER:
            case Map::Entities::ET_FIRETHROWER:
            case Map::Entities::ET_FIRETHROWER | Map::Entities::ET_ARROW_AND_DEFAULT:
            case Map::Entities::ET_FIRETHROWER_UNTARGETED:
            case Map::Entities::ET_FIREBALLISTA:
            case ((EntityType)0x5b):
            case ((EntityType)0x5c):
            case ((EntityType)0x5d):
            case ((EntityType)0x5e):
                uVar5 = microX / 8;
                uVar6 = microY / 8;
                if (((399 < uVar5) || (399 < uVar6)) || (*(char*)(uVar6 * 400 + 0x21aec98 + uVar5) == '\0')) {
                    return 0;
                }
                uVar5 = targetX / 8;
                uVar6 = targetY / 8;
                if (399 < uVar5) {
                    return 0;
                }
                if (399 < uVar6) {
                    return 0;
                }
                if (*(char*)(uVar6 * 400 + 0x21aec98 + uVar5) == '\0') {
                    return 0;
                }
            }
            if ((int)entityID < 0x19) {
                this->entityArray[entityID].uid = 0;
            } else {
                this->entityArray[entityID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            }
            dVar2 = DAT_GameCore::instance.mapTimeInTicks;
            this->entityArray[entityID].unitID_OR_seaGullID = (short)unitID;
            this->entityArray[entityID].targetX = (short)targetX;
            this->entityArray[entityID].targetY = (short)targetY;
            this->entityArray[entityID].targetZ = (short)targetZUnk;
            this->entityArray[entityID].heightDifference = targetZUnk - totalHeight;
            this->entityArray[entityID].field21_0x34 = dVar2;
            this->entityArray[entityID].unitID = (short)param_11;
            this->entityArray[entityID].owner = (short)playerID1;
            this->entityArray[entityID].microX = (short)microX;
            this->entityArray[entityID].x_2 = (short)microX;
            this->entityArray[entityID].logicalState = 1;
            this->entityArray[entityID].microY = (short)microY;
            this->entityArray[entityID].y_2 = (short)microY;
            sVar7 = (short)totalHeight;
            this->entityArray[entityID].height = sVar7;
            this->entityArray[entityID].startingHeight_2 = sVar7;
            this->entityArray[entityID].height_2 = sVar7;
            this->entityArray[entityID].startingHeight = sVar7;
            this->entityArray[entityID].unkMinusOne = 0;
            /*
              sets DAT_TempBuildingOrientation
             */
            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(microX, microY, targetX, targetY);
            this->entityArray[entityID].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            this->entityArray[entityID].colorUnk = 0;
            if ((((entityType == Map::Entities::ET_FLAG_1)
                     || (entityType == Map::Entities::ET_FLAG_4))
                    || (entityType == Map::Entities::ET_FLAG_2))
                || (entityType == Map::Entities::ET_FLAG_3)) {
                this->entityArray[entityID].colorUnk = ownerColorUnk;
            }
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::setProjectileEntityValues2, this)(
                entityID, entityType);
            if (this->entityArray[entityID].rng_2 != 0) {
                this->entityArray[entityID].gmID = 0x91;
            }
            this->entityArray[entityID].field7_0x12 = 0;
            this->entityArray[entityID].unknownAnimationFrameRelated = 0;
            if (entityType == Map::Entities::ET_DUST_CLOUD) {
                if (param_11 == 1) {
                    this->entityArray[entityID].unknownAnimationFrameRelated = 200;
                }
            LAB_00404efa:
                this->entityArray[entityID].rng_1 = (int)SEC_RNG::instance.currentNumber2;
                if (25 < (int)entityID) {
                    MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                }
                if (entityType == Map::Entities::ET_SEAGULLUnk) {
                    this->entityArray[entityID].rng_2 = SEC_RNG::instance.currentNumber2 % 100 + 120;
                    goto LAB_00404f8c;
                }
                if (entityType == ((EntityType)0x1f)) {
                    if (unitID) {
                        this->entityArray[entityID].unkOne_1 = 2;
                    }
                    goto LAB_00404f8c;
                }
                if (entityType != Map::Entities::ET_HEADS_ON_SPIKES)
                    goto LAB_00404f8c;
                this->entityArray[entityID].rng_2 = SEC_RNG::instance.currentNumber2 % 500 + 300;
            } else {
                if (entityType != ((EntityType)8))
                    goto LAB_00404efa;
                ownerColorUnk = DAT_UnitsState::instance.units[unitID].fixedRng;
            }
            this->entityArray[entityID].rng_1 = ownerColorUnk;
        LAB_00404f8c:
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::initializeProjectileVelocities, this)(
                entityID, microX, microY, totalHeight, targetX, targetY, targetZUnk);
            if (this->entityArray[entityID].entityType == ((EntityType)0x18)) {
                this->entityArray[entityID].entityType = Map::Entities::ET_ARROW_AND_DEFAULT;
            }
            if (this->entityArray[entityID].entityType == ((EntityType)0x19)) {
                this->entityArray[entityID].entityType = Map::Entities::ET_CROSSBOWARROW;
            }
            if (this->entityArray[entityID].entityType
                == (Map::Entities::ET_FIRETHROWER | Map::Entities::ET_ARROW_AND_DEFAULT)) {
                this->entityArray[entityID].entityType = Map::Entities::ET_SLINGER;
            }
            if (this->entityArray[entityID].entityType == Map::Entities::ET_FIRETHROWER_UNTARGETED) {
                this->entityArray[entityID].entityType = Map::Entities::ET_FIRETHROWER;
            }
            if (bVar1) {
                this->entityArray[entityID].gmLookupValue = 1;
            }
            if (entityID) {
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::processEntityHitBuildingOrUnit, this)(
                    entityID);
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::calculateEntityDrawOffset, this)(entityID);
                uVar5 = DAT_CurrentEntityID::instance;
                DAT_CurrentEntityID::instance = entityID;
                ((void (*)())DAT_EntityDefinedData::instance
                        .EntityCallbacks[(short)this->entityArray[entityID].entityType])();
                DAT_CurrentEntityID::instance = uVar5;
            }
            return entityID;
        LAB_00404bc5:
            if (pEVar4[-1] == 0)
                goto LAB_00404c16;
            switch (*pEVar4) {
            case Map::Entities::ET_FIRE:
            case Map::Entities::ET_DUST_CLOUD:
            case ((EntityType)0x1b):
            case ((EntityType)0x1e):
            case ((EntityType)0x1f):
                MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::deleteEntity, this)(entityID);
                goto LAB_00404c16;
            default:
                entityID = entityID + 1;
                pEVar4 = pEVar4 + 0x74;
                if (2999 < (int)entityID) {
                switchD_00404bac_caseD_5:
                    this->every10Ticks = 2999;
                    return 0;
                }
            }
            goto LAB_00404bc5;
        }

    }
}
}
