#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DOUBLE_00b941c0.hpp"

#include "float.h"
#include "math.h"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402C50
        int EntityState::math_atan_1(int entityType, double param_3, int param_4, int heightDifference)
        {
            double dVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            double fVar5;
            double fVar6;
            fVar5 = (double)param_3 * (double)param_3;
            fVar6 = (double)(param_4 * 4);
            dVar1 = (double)(fVar5 / (fVar6 * (double)9.812));
            fVar5 = sqrt(((fVar5 * fVar5) / ((double)96.275344 * fVar6 * fVar6)
                             - ((fVar5 + fVar5) * (double)(heightDifference / 2)) / (fVar6 * fVar6 * (double)9.812))
                - (double)1.0);
            fVar6 = (double)dVar1 - fVar5;
            if (((double)DOUBLE_00b941c0::instance == fVar6) || (iVar2 = _isnan((double)fVar6), iVar2)) {
                iVar2 = 1000;
            } else {
                fVar6 = atan((double)fVar6);
                iVar2 = (long)((fVar6 * (double)180.0) / (double)3.1415926535 + (double)0.4999000132083893);
            }
            dVar1 = (double)fVar5 + dVar1;
            if ((DOUBLE_00b941c0::instance == dVar1) || (iVar3 = _isnan(dVar1), iVar3)) {
                iVar3 = 1000;
            } else {
                fVar5 = atan((double)dVar1);
                iVar3 = (long)((fVar5 * (double)180.0) / (double)3.1415926535 + (double)0.4999000132083893);
            }
            iVar4 = iVar2;
            if (iVar3 <= iVar2) {
                iVar4 = iVar3;
            }
            if (iVar4 < -0x5a) {
                iVar4 = iVar2;
                if (iVar2 <= iVar3) {
                    iVar4 = iVar3;
                }
                if (iVar4 < -0x5a) {
                    return 0x2d;
                }
            }
            if (0x5a < iVar4) {
                return 0x2d;
            }
            return iVar4;
        }

    }
}
}
