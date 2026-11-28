#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using DE::SHCDE::eSFX;

        // FUNCTION: STRONGHOLDCRUSADER 0x00403FF0
        void EntityState::handleProjectileWallBounce(int param_1)
        {
            word wVar1;
            byte _bitFlag;
            uint y;
            undefined4 uVar2;
            uint x;
            uint uVar3;
            short sVar4;
            int iVar5;
            uint uVar6;
            short sVar7;
            short sVar8;
            int iVar9;
            bool bVar10;
            bool bVar11;
            bool bVar12;
            double fVar13;
            double fVar14;
            sVar4 = this->entityArray[param_1].microY;
            y = (uint)sVar4;
            sVar8 = this->entityArray[param_1].microX;
            x = (uint)sVar8;
            uVar3 = x & 7;
            iVar5 = 0;
            iVar9 = 0;
            uVar6 = y & 7;
            _bitFlag = MACRO_CALL_MEMBER(Map::TileMapState_Func::setBitFlagBasedOnWallTowerGatehouseOrKeep,
                DAT_TileMapState::ptr)(x / 8, (int)((int)(y / 8)));
            switch (this->entityArray[param_1].orientation) {
            case 0x3c:
            case 0x40:
            case 0x44:
            case 0x48:
            switchD_0040405c_caseD_3c:
                iVar9 = (int)this->entityArray[param_1].y_2;
            LAB_004042e5:
                iVar5 = (int)this->entityArray[param_1].x_2;
                break;
            case 0x3d:
                uVar6 = 7 - uVar6;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 10) {
                    case 0:
                    case 8:
                    switchD_00404081_caseD_0:
                        uVar6 = 100;
                        break;
                    case 2:
                    switchD_00404081_caseD_2:
                        uVar3 = 100;
                        break;
                    case 10:
                        goto switchD_0040405c_caseD_3c;
                    }
                switchD_00404081_caseD_4:
                    bVar12 = (uVar3 < uVar6);
                    bVar11 = (int)(uVar3 - uVar6) < 0;
                    bVar10 = uVar3 == uVar6;
                }
                goto LAB_0040408f;
            case 0x3e:
                uVar6 = 7 - uVar6;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 10) {
                    case 0:
                    case 8:
                        goto switchD_00404081_caseD_0;
                    case 2:
                        goto switchD_00404081_caseD_2;
                    default:
                        goto switchD_00404081_caseD_4;
                    case 10:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x3f:
                uVar6 = 7 - uVar6;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 10) {
                    case 0:
                    case 2:
                        goto switchD_00404081_caseD_2;
                    default:
                        goto switchD_00404081_caseD_4;
                    case 8:
                        goto switchD_00404081_caseD_0;
                    case 10:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x41:
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0x82) {
                    case 0:
                    case 2:
                    switchD_0040410f_caseD_0:
                        uVar6 = 100;
                    default:
                    switchD_0040410f_caseD_4:
                        bVar12 = (uVar3 < uVar6);
                        bVar11 = (int)(uVar3 - uVar6) < 0;
                        bVar10 = uVar3 == uVar6;
                        break;
                    case 0x80:
                    switchD_0040410f_caseD_80:
                        bVar12 = (100 < uVar6);
                        bVar11 = (int)(100 - uVar6) < 0;
                        bVar10 = uVar6 == 100;
                        break;
                    case 0x82:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x42:
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0x82) {
                    case 0:
                    case 2:
                        goto switchD_0040410f_caseD_0;
                    default:
                        goto switchD_0040410f_caseD_4;
                    case 0x80:
                        goto switchD_0040410f_caseD_80;
                    case 0x82:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x43:
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0x82) {
                    case 0:
                    case 0x80:
                    switchD_00404173_caseD_0:
                        uVar3 = 100;
                    default:
                    switchD_00404173_caseD_4:
                        bVar12 = (uVar3 < uVar6);
                        bVar11 = (int)(uVar3 - uVar6) < 0;
                        bVar10 = uVar3 == uVar6;
                        break;
                    case 2:
                    switchD_00404173_caseD_2:
                        bVar12 = (uVar3 < 100);
                        bVar11 = (int)(uVar3 - 100) < 0;
                        bVar10 = uVar3 == 100;
                        break;
                    case 0x82:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x45:
                uVar3 = 7 - uVar3;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0xa0) {
                    case 0:
                    case 0x80:
                        goto switchD_0040410f_caseD_0;
                    case 0x20:
                        goto switchD_0040410f_caseD_80;
                    default:
                        goto switchD_0040410f_caseD_4;
                    case 0xa0:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x46:
                uVar3 = 7 - uVar3;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0xa0) {
                    case 0:
                    case 0x80:
                        goto switchD_0040410f_caseD_0;
                    case 0x20:
                        goto switchD_0040410f_caseD_80;
                    default:
                        goto switchD_0040410f_caseD_4;
                    case 0xa0:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x47:
                uVar3 = 7 - uVar3;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0xa0) {
                    case 0:
                    case 0x20:
                        goto switchD_00404173_caseD_0;
                    default:
                        goto switchD_00404173_caseD_4;
                    case 0x80:
                        goto switchD_00404173_caseD_2;
                    case 0xa0:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x49:
                iVar5 = -uVar3 + 7;
                iVar9 = 7 - uVar6;
                bVar12 = (iVar5 < iVar9);
                bVar11 = iVar5 - iVar9 < 0;
                bVar10 = false;
                if (iVar5 == iVar9) {
                    switch (_bitFlag & 0x28) {
                    case 0:
                    case 0x20:
                        iVar5 = 100;
                    default:
                        bVar12 = (iVar5 < iVar9);
                        bVar11 = iVar5 - iVar9 < 0;
                        bVar10 = iVar5 == iVar9;
                        break;
                    case 8:
                        bVar12 = (iVar5 < 100);
                        bVar11 = (int)(-uVar3 + -0x5d) < 0;
                        bVar10 = iVar5 == 100;
                        break;
                    case 0x28:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
            LAB_0040408f:
                if (bVar10 || bVar12 != bVar11) {
                    iVar9 = this->entityArray[param_1].microY * 2 - (int)this->entityArray[param_1].y_2;
                    goto LAB_004042e5;
                }
                iVar9 = (int)this->entityArray[param_1].y_2;
                iVar5 = this->entityArray[param_1].microX * 2 - (int)this->entityArray[param_1].x_2;
                break;
            case 0x4a:
                uVar3 = 7 - uVar3;
                uVar6 = 7 - uVar6;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0x28) {
                    case 0:
                    case 8:
                        goto switchD_00404081_caseD_0;
                    default:
                        goto switchD_00404081_caseD_4;
                    case 0x20:
                        goto switchD_00404081_caseD_2;
                    case 0x28:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            case 0x4b:
                uVar3 = 7 - uVar3;
                uVar6 = 7 - uVar6;
                bVar12 = (uVar3 < uVar6);
                bVar11 = (int)(uVar3 - uVar6) < 0;
                bVar10 = false;
                if (uVar3 == uVar6) {
                    switch (_bitFlag & 0x28) {
                    case 0:
                    case 8:
                        goto switchD_00404081_caseD_0;
                    default:
                        goto switchD_00404081_caseD_4;
                    case 0x20:
                        goto switchD_00404081_caseD_2;
                    case 0x28:
                        goto switchD_0040405c_caseD_3c;
                    }
                }
                goto LAB_0040408f;
            default:
                break;
            }
            MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::somethingWithProjectileDistance,
                DAT_DirectionAlgorithmState::ptr)(x, (int)((int)(y)), iVar5, iVar9);
            this->entityArray[param_1].orientation = DAT_DirectionAlgorithmState::instance.orientation;
            sVar7 = (short)iVar9;
            if (iVar9 < (int)y) {
                this->entityArray[param_1].pathDeltaY = sVar4 - sVar7;
            } else {
                this->entityArray[param_1].pathDeltaY = sVar7 - sVar4;
            }
            sVar4 = (short)iVar5;
            if (iVar5 < (int)x) {
                this->entityArray[param_1].pathDeltaX = sVar8 - sVar4;
            } else {
                this->entityArray[param_1].pathDeltaX = sVar4 - sVar8;
            }
            sVar8 = this->entityArray[param_1].pathDeltaX;
            this->entityArray[param_1].pathTargetX = sVar4;
            this->entityArray[param_1].someMicroX = (ushort)((int)x <= iVar5) * 2 + -1;
            this->entityArray[param_1].pathTargetY = sVar7;
            this->entityArray[param_1].someMicroY = (ushort)((int)y <= iVar9) * 2 + -1;
            if (!sVar8) {
                if (this->entityArray[param_1].pathDeltaY == 0) {
                    this->entityArray[param_1].pathAxisCase = 0;
                } else {
                    this->entityArray[param_1].pathAxisCase = 1;
                }
            } else {
                sVar4 = this->entityArray[param_1].pathDeltaY;
                if (!sVar4) {
                    this->entityArray[param_1].pathAxisCase = 2;
                } else if (sVar8 < sVar4) {
                    this->entityArray[param_1].pathAxisCase = 3;
                } else {
                    this->entityArray[param_1].pathAxisCase = 4;
                }
            }
            sVar4 = this->entityArray[param_1].pathAxisCase;
            if (sVar4 == 3) {
                sVar4 = this->entityArray[param_1].pathDeltaY;
                sVar8 = sVar8 * 2;
                this->entityArray[param_1].pathErrorStepStraight = sVar8;
                sVar7 = sVar8 + sVar4 * -2;
                this->entityArray[param_1].pathError = sVar8 - sVar4;
            } else {
                if (sVar4 != 4)
                    goto LAB_0040440f;
                sVar4 = this->entityArray[param_1].pathDeltaY * 2;
                this->entityArray[param_1].pathErrorStepStraight = sVar4;
                sVar7 = sVar4 + sVar8 * -2;
                this->entityArray[param_1].pathError = sVar4 - sVar8;
            }
            this->entityArray[param_1].pathErrorStepDiagonal = sVar7;
        LAB_0040440f:
            wVar1 = this->entityArray[param_1].graphicRotationUnk;
            this->entityArray[param_1].startingAngle = wVar1;
            if ((short)wVar1 < -0x50) {
                this->entityArray[param_1].startingAngle = -0x50;
            }
            iVar9 = (int)this->entityArray[param_1].startingAngle;
            this->entityArray[param_1].speedUnk = 0;
            iVar5 = (int)this->entityArray[param_1].velocityUnk;
            fVar13 = ((double)iVar9 * (double)3.1415926535) / (double)180.0;
            sVar4 = this->entityArray[param_1].height;
            sVar8 = (short)(iVar5 / 8);
            this->entityArray[param_1].velocityUnk = sVar8;
            this->entityArray[param_1].startingHeight = sVar4;
            this->entityArray[param_1].travelledDistance = 0;
            fVar14 = cos(fVar13);
            this->entityArray[param_1].vCos = (float)((double)(int)sVar8 * fVar14);
            fVar13 = sin((double)fVar13);
            this->entityArray[param_1].vSin = (float)((double)(int)sVar8 * fVar13);
            uVar2 = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::angleToRotationFrameIndex, this)(iVar9);
            sVar4 = this->entityArray[param_1].xPosition;
            this->entityArray[param_1].rotationFrameIndex = (short)uVar2;
            sVar8 = this->entityArray[param_1].yPosition;
            this->entityArray[param_1].gmLookupValue = 0;
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)sVar4, (int)((int)(sVar8)), DE::SHCDE::FX_ARROW_BOUNCE);
            return;
        }

    }
}
}
