#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00403A20
        void EntityState::initializeProjectileVelocities(
            int entityID, int x, int y, int height, int targetX, int targetY, int targetZ)
        {
            float fVar1;
            short sVar2;
            ushort uVar3;
            EntityTypeShort EVar4;
            short sVar5;
            uint uVar6;
            int iVar7;
            undefined4 uVar8;
            short sVar9;
            short sVar10;
            int iVar11;
            double fVar12;
            double fVar13;
            sVar5 = (short)targetY;
            if (targetY < y) {
                this->entityArray[entityID].pathDeltaY = (short)y - sVar5;
            } else {
                this->entityArray[entityID].pathDeltaY = sVar5 - (short)y;
            }
            sVar10 = (short)targetX;
            if (targetX < x) {
                sVar9 = (short)x - sVar10;
            } else {
                sVar9 = sVar10 - (short)x;
            }
            sVar2 = this->entityArray[entityID].targetZ;
            this->entityArray[entityID].pathDeltaX = sVar9;
            sVar9 = this->entityArray[entityID].height;
            if (sVar9 < sVar2) {
                this->entityArray[entityID].pathDeltaZ = sVar2 - sVar9;
            } else {
                this->entityArray[entityID].pathDeltaZ = sVar9 - sVar2;
            }
            sVar9 = this->entityArray[entityID].pathDeltaX;
            this->entityArray[entityID].pathTargetX = sVar10;
            this->entityArray[entityID].pathTargetY = sVar5;
            this->entityArray[entityID].someMicroX = (ushort)(x <= targetX) * 2 + -1;
            this->entityArray[entityID].someMicroY = (ushort)(y <= targetY) * 2 + -1;
            if (!sVar9) {
                if (this->entityArray[entityID].pathDeltaY == 0) {
                    this->entityArray[entityID].pathAxisCase = 0;
                } else {
                    this->entityArray[entityID].pathAxisCase = 1;
                }
            } else {
                sVar5 = this->entityArray[entityID].pathDeltaY;
                if (!sVar5) {
                    this->entityArray[entityID].pathAxisCase = 2;
                } else if (sVar9 < sVar5) {
                    this->entityArray[entityID].pathAxisCase = 3;
                } else {
                    this->entityArray[entityID].pathAxisCase = 4;
                }
            }
            sVar5 = this->entityArray[entityID].pathAxisCase;
            if (sVar5 == 3) {
                sVar10 = sVar9 * 2;
                sVar9 = this->entityArray[entityID].pathDeltaY;
                this->entityArray[entityID].pathErrorStepStraight = sVar10;
                sVar5 = this->entityArray[entityID].pathDeltaY;
                this->entityArray[entityID].pathErrorStepDiagonal = sVar10 + sVar9 * -2;
            LAB_00403b64:
                this->entityArray[entityID].pathError = sVar10 - sVar5;
            } else if (sVar5 == 4) {
                sVar10 = this->entityArray[entityID].pathDeltaY * 2;
                this->entityArray[entityID].pathErrorStepStraight = sVar10;
                sVar5 = this->entityArray[entityID].pathDeltaX;
                this->entityArray[entityID].pathErrorStepDiagonal = sVar10 + sVar9 * -2;
                goto LAB_00403b64;
            }
            iVar7 = DAT_EntityDefinedData::instance
                        .EntityArrayCurveTypeForProjectileType[(short)this->entityArray[entityID].entityType];
            if (!iVar7) {
                uVar6 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                sVar5 = (short)uVar6;
                this->entityArray[entityID].field62_0x94 = sVar5;
                this->entityArray[entityID].totalFlightDistance = sVar5;
                this->entityArray[entityID].clearanceStepsRemaining = (short)this->lineOfSightClearanceSteps;
                sVar10 = this->entityArray[entityID].velocityUnk;
            } else {
                if (iVar7 == 1) {
                    uVar6 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance,
                        this)(x, y, height, targetX, targetY, targetZ, 1);
                    iVar7 = this->entityArray[entityID].heightDifference;
                    sVar5 = (short)uVar6;
                    this->entityArray[entityID].field62_0x94 = sVar5;
                    this->entityArray[entityID].totalFlightDistance = sVar5;
                    this->entityArray[entityID].clearanceStepsRemaining = (short)this->lineOfSightClearanceSteps;
                    iVar7 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeVelocity, this)(
                        (int)(short)this->entityArray[entityID].entityType,
                        (double)((int)((int)this->entityArray[entityID].startingAngle)), (int)((int)(sVar5)), iVar7);
                    this->entityArray[entityID].velocityUnk = (short)iVar7;
                    goto LAB_00403f37;
                }
                if (iVar7 == 2) {
                    uVar6 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance,
                        this)(x, y, height, targetX, targetY, targetZ, 1);
                    sVar5 = this->entityArray[entityID].height;
                    sVar10 = this->entityArray[entityID].targetZ;
                    sVar9 = (short)uVar6;
                    this->entityArray[entityID].field62_0x94 = sVar9;
                    this->entityArray[entityID].totalFlightDistance = sVar9;
                    this->entityArray[entityID].clearanceStepsRemaining = (short)this->lineOfSightClearanceSteps;
                    if (sVar10 < sVar5) {
                        this->entityArray[entityID].startingAngle = 3;
                    }
                    iVar7 = this->entityArray[entityID].heightDifference;
                    iVar11 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeVelocity, this)(
                        (int)(short)this->entityArray[entityID].entityType,
                        (double)((int)((int)this->entityArray[entityID].startingAngle)), (int)((int)(sVar9)), iVar7);
                    this->entityArray[entityID].velocityUnk = (short)iVar11;
                    if ((short)iVar11 < 1) {
                        EVar4 = this->entityArray[entityID].entityType;
                        this->entityArray[entityID].startingAngle = 0xf;
                        iVar7 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeVelocity, this)(
                            (int)(short)EVar4, 15.0, (int)((int)(sVar9)), iVar7);
                        this->entityArray[entityID].velocityUnk = (short)iVar7;
                    }
                    goto LAB_00403f37;
                }
                if (iVar7 == 3) {
                    uVar3 = (ushort)this->entityArray[entityID].rng_1;
                    this->entityArray[entityID].startingAngle = (uVar3 & 0xf) + 8;
                    this->entityArray[entityID].velocityUnk = (uVar3 & 7) + 0x15;
                    goto LAB_00403f37;
                }
                if (iVar7 == 4) {
                    uVar6 = this->entityArray[entityID].rng_1;
                    sVar5 = (short)((int)uVar6 % 0x14) + 0x10;
                    this->entityArray[entityID].startingAngle = sVar5;
                    if ((char)uVar6 < '\0') {
                        this->entityArray[entityID].startingAngle = -sVar5;
                    }
                    sVar5 = (short)(((int)uVar6 >> 8) % 0x14) + 0x10;
                    this->entityArray[entityID].velocityUnk = sVar5;
                    if (!(uVar6 & 0x8000)) {
                        return;
                    }
                    this->entityArray[entityID].velocityUnk = -sVar5;
                    return;
                }
                if (iVar7 == 5) {
                    iVar11 = this->entityArray[entityID].rng_1;
                    iVar7 = this->entityArray[entityID].rng_1;
                    this->entityArray[entityID].velocityUnk = 0;
                    this->entityArray[entityID].startingAngle = (byte)iVar11 & 7;
                    this->entityArray[entityID].graphicRotationUnk = (ushort)((uint)iVar7 >> 8) & 0x3f;
                    return;
                }
                if (iVar7 != 6) {
                    if (iVar7 == 7) {
                        return;
                    }
                    if (iVar7 == 10) {
                        return;
                    }
                    if (iVar7 == 8) {
                        sVar5 = this->entityArray[entityID].unitID_OR_seaGullID;
                        if (!sVar5) {
                            this->entityArray[entityID].startingAngle
                                = (short)(this->entityArray[entityID].rng_1 % 0x3c) + 8;
                            this->entityArray[entityID].velocityUnk
                                = ((byte)this->entityArray[entityID].rng_1 & 7) + 0x23;
                        } else {
                            if (sVar5 == 4) {
                                this->entityArray[entityID].startingAngle
                                    = (short)(this->entityArray[entityID].rng_1 % 0x1e) + 0xf;
                                sVar5 = ((byte)this->entityArray[entityID].rng_1 & 7) + 0xf;
                            } else {
                                iVar7 = this->entityArray[entityID].rng_1;
                                if (sVar5 == 5) {
                                    this->entityArray[entityID].startingAngle = (short)(iVar7 % 0x1e) + 0x2d;
                                    this->entityArray[entityID].velocityUnk
                                        = ((byte)this->entityArray[entityID].rng_1 & 7) + 0x23;
                                    goto LAB_00403f37;
                                }
                                this->entityArray[entityID].startingAngle = (short)(iVar7 % 0x23) + 0x14;
                                sVar5 = ((byte)this->entityArray[entityID].rng_1 & 7) + 0x19;
                            }
                            fVar1 = this->entityArray[entityID]._elapsedTimeOrGravityAccumulator;
                            this->entityArray[entityID].velocityUnk = sVar5;
                            this->entityArray[entityID]._elapsedTimeOrGravityAccumulator = fVar1 * 0.75;
                        }
                    } else if (iVar7 == 9) {
                        this->entityArray[entityID].startingAngle = 0;
                    }
                    goto LAB_00403f37;
                }
                uVar6 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::computeLineOfSightDistance, this)(
                    x, y, height, targetX, targetY, targetZ, 1);
                sVar5 = (short)uVar6;
                this->entityArray[entityID].field62_0x94 = sVar5;
                this->entityArray[entityID].totalFlightDistance = sVar5;
                this->entityArray[entityID].clearanceStepsRemaining = (short)this->lineOfSightClearanceSteps;
                if (0x96 < sVar5) {
                    this->entityArray[entityID].velocityUnk = 0x7d;
                }
                sVar10 = this->entityArray[entityID].velocityUnk;
            }
            iVar7 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::math_atan_1, this)(
                (int)(short)this->entityArray[entityID].entityType, (double)((int)((int)sVar10)), (int)((int)(sVar5)),
                this->entityArray[entityID].heightDifference);
            this->entityArray[entityID].startingAngle = (short)iVar7;
        LAB_00403f37:
            EVar4 = this->entityArray[entityID].entityType;
            if ((((EVar4 == Map::Entities::ET_ARROW_AND_DEFAULT)
                     || (EVar4 == Map::Entities::ET_CROSSBOWARROW))
                    && (height + 0x36 < targetZ))
                && (this->entityArray[entityID].rng_1 % 10 == 5)) {
                this->entityArray[entityID].hasDoneEffectUnk = 1;
            }
            iVar11 = (int)this->entityArray[entityID].startingAngle;
            this->entityArray[entityID].speedUnk = 0;
            iVar7 = (int)this->entityArray[entityID].velocityUnk;
            this->entityArray[entityID].travelledDistance = 0;
            fVar12 = ((double)iVar11 * (double)3.1415926535) / (double)180.0;
            fVar13 = cos(fVar12);
            this->entityArray[entityID].vCos = (float)(fVar13 * (double)iVar7);
            fVar12 = sin((double)fVar12);
            this->entityArray[entityID].vSin = (float)(fVar12 * (double)iVar7);
            uVar8
                = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(iVar11);
            this->entityArray[entityID].rotationFrameIndex = (short)uVar8;
            return;
        }

    }
}
}
