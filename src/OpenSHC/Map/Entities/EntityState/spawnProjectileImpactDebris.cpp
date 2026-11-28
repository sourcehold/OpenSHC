#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using Map::Entities::EntityType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00405DA0
        void EntityState::spawnProjectileImpactDebris(int param_1)
        {
            byte bVar1;
            uint microY;
            uint microX;
            uint uVar2;
            int iVar3;
            uint uVar4;
            int iVar5;
            int iVar6;
            bool bVar7;
            bool bVar8;
            bool bVar9;
            microY = (uint)this->entityArray[param_1].microY;
            microX = (uint)this->entityArray[param_1].microX;
            uVar2 = microX & 7;
            iVar6 = 0;
            iVar3 = 0;
            uVar4 = microY & 7;
            bVar1 = MACRO_CALL_MEMBER(
                Map::TileMapState_Func::setBitFlagBasedOnWallTowerGatehouseOrKeep, DAT_TileMapState::ptr)(
                (int)(microX + ((int)microX >> 0x1f & 7U)) >> 3, (int)((int)((microY + (microY >> 0x1f & 7U)) >> 3)));
            switch (this->entityArray[param_1].orientation) {
            case 0x3c:
            case 0x40:
            case 0x44:
            case 0x48:
            switchD_00405e0c_caseD_3c:
                iVar3 = (int)this->entityArray[param_1].y_2;
                break;
            case 0x3d:
                uVar4 = 7 - uVar4;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 10) {
                    case 0:
                    case 8:
                    switchD_00405e31_caseD_0:
                        uVar4 = 100;
                        break;
                    case 2:
                    switchD_00405e31_caseD_2:
                        uVar2 = 100;
                        break;
                    case 10:
                        goto switchD_00405e0c_caseD_3c;
                    }
                switchD_00405e31_caseD_4:
                    bVar9 = (uVar2 < uVar4);
                    bVar8 = (int)(uVar2 - uVar4) < 0;
                    bVar7 = uVar2 == uVar4;
                }
                goto LAB_00405e3f;
            case 0x3e:
                uVar4 = 7 - uVar4;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 10) {
                    case 0:
                    case 8:
                        goto switchD_00405e31_caseD_0;
                    case 2:
                        goto switchD_00405e31_caseD_2;
                    default:
                        goto switchD_00405e31_caseD_4;
                    case 10:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x3f:
                uVar4 = 7 - uVar4;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 10) {
                    case 0:
                    case 2:
                        goto switchD_00405e31_caseD_2;
                    default:
                        goto switchD_00405e31_caseD_4;
                    case 8:
                        goto switchD_00405e31_caseD_0;
                    case 10:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x41:
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0x82) {
                    case 0:
                    case 2:
                    switchD_00405ebf_caseD_0:
                        uVar4 = 100;
                    default:
                    switchD_00405ebf_caseD_4:
                        bVar9 = (uVar2 < uVar4);
                        bVar8 = (int)(uVar2 - uVar4) < 0;
                        bVar7 = uVar2 == uVar4;
                        break;
                    case 0x80:
                    switchD_00405ebf_caseD_80:
                        bVar9 = (100 < uVar4);
                        bVar8 = (int)(100 - uVar4) < 0;
                        bVar7 = uVar4 == 100;
                        break;
                    case 0x82:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x42:
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0x82) {
                    case 0:
                    case 2:
                        goto switchD_00405ebf_caseD_0;
                    default:
                        goto switchD_00405ebf_caseD_4;
                    case 0x80:
                        goto switchD_00405ebf_caseD_80;
                    case 0x82:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x43:
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0x82) {
                    case 0:
                    case 0x80:
                    switchD_00405f23_caseD_0:
                        uVar2 = 100;
                    default:
                    switchD_00405f23_caseD_4:
                        bVar9 = (uVar2 < uVar4);
                        bVar8 = (int)(uVar2 - uVar4) < 0;
                        bVar7 = uVar2 == uVar4;
                        break;
                    case 2:
                    switchD_00405f23_caseD_2:
                        bVar9 = (uVar2 < 100);
                        bVar8 = (int)(uVar2 - 100) < 0;
                        bVar7 = uVar2 == 100;
                        break;
                    case 0x82:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x45:
                uVar2 = 7 - uVar2;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0xa0) {
                    case 0:
                    case 0x80:
                        goto switchD_00405ebf_caseD_0;
                    case 0x20:
                        goto switchD_00405ebf_caseD_80;
                    default:
                        goto switchD_00405ebf_caseD_4;
                    case 0xa0:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x46:
                uVar2 = 7 - uVar2;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0xa0) {
                    case 0:
                    case 0x80:
                        goto switchD_00405ebf_caseD_0;
                    case 0x20:
                        goto switchD_00405ebf_caseD_80;
                    default:
                        goto switchD_00405ebf_caseD_4;
                    case 0xa0:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x47:
                uVar2 = 7 - uVar2;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0xa0) {
                    case 0:
                    case 0x20:
                        goto switchD_00405f23_caseD_0;
                    default:
                        goto switchD_00405f23_caseD_4;
                    case 0x80:
                        goto switchD_00405f23_caseD_2;
                    case 0xa0:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x49:
                iVar3 = -uVar2 + 7;
                iVar6 = 7 - uVar4;
                bVar9 = (iVar3 < iVar6);
                bVar8 = iVar3 - iVar6 < 0;
                bVar7 = false;
                if (iVar3 == iVar6) {
                    switch (bVar1 & 0x28) {
                    case 0:
                    case 0x20:
                        iVar3 = 100;
                    default:
                        bVar9 = (iVar3 < iVar6);
                        bVar8 = iVar3 - iVar6 < 0;
                        bVar7 = iVar3 == iVar6;
                        break;
                    case 8:
                        bVar9 = (iVar3 < 100);
                        bVar8 = (int)(-uVar2 + -0x5d) < 0;
                        bVar7 = iVar3 == 100;
                        break;
                    case 0x28:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
            LAB_00405e3f:
                if (!bVar7 && bVar9 == bVar8) {
                    iVar3 = (int)this->entityArray[param_1].y_2;
                    iVar6 = this->entityArray[param_1].microX * 2 - (int)this->entityArray[param_1].x_2;
                    goto switchD_00405e0c_caseD_10;
                }
                iVar3 = this->entityArray[param_1].microY * 2 - (int)this->entityArray[param_1].y_2;
                break;
            case 0x4a:
                uVar2 = 7 - uVar2;
                uVar4 = 7 - uVar4;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0x28) {
                    case 0:
                    case 8:
                        goto switchD_00405e31_caseD_0;
                    default:
                        goto switchD_00405e31_caseD_4;
                    case 0x20:
                        goto switchD_00405e31_caseD_2;
                    case 0x28:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            case 0x4b:
                uVar2 = 7 - uVar2;
                uVar4 = 7 - uVar4;
                bVar9 = (uVar2 < uVar4);
                bVar8 = (int)(uVar2 - uVar4) < 0;
                bVar7 = false;
                if (uVar2 == uVar4) {
                    switch (bVar1 & 0x28) {
                    case 0:
                    case 8:
                        goto switchD_00405e31_caseD_0;
                    default:
                        goto switchD_00405e31_caseD_4;
                    case 0x20:
                        goto switchD_00405e31_caseD_2;
                    case 0x28:
                        goto switchD_00405e0c_caseD_3c;
                    }
                }
                goto LAB_00405e3f;
            default:
                goto switchD_00405e0c_caseD_10;
            }
            iVar6 = (int)this->entityArray[param_1].x_2;
        switchD_00405e0c_caseD_10:
            iVar5 = 0;
            uVar4 = this->entityArray[param_1].rng_1 & 0x80000007;
            if ((int)uVar4 < 0) {
                uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
            }
            if (uVar4 != 0xfffffffb && -1 < (int)(uVar4 + 5)) {
                do {
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, this)(0, 0, 0,
                        (int)((int)(microX)), (int)((int)(microY)), (int)((int)(this->entityArray[param_1].height)),
                        iVar6, iVar3, 8, ((EntityType)0x1b), 0);
                    iVar5 = iVar5 + 1;
                    uVar4 = this->entityArray[param_1].rng_1 & 0x80000007;
                    if ((int)uVar4 < 0) {
                        uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                    }
                } while (iVar5 < (int)(uVar4 + 5));
            }
            iVar3 = (int)this->entityArray[param_1].height;
            MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::spawnProjectileEntity, this)(0, 0, 0,
                (int)((int)(microX)), (int)((int)(microY)), iVar3, (int)((int)(microX + 1)), (int)((int)(microY + 1)),
                iVar3, ((EntityType)0x1e), 0);
        }

    }
}
}
