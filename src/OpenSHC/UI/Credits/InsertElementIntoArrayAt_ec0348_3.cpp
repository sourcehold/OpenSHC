#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAE00
    void Credits::InsertElementIntoArrayAt_ec0348_3(
        int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
    {
        CreditsRelatedStructure* pCVar2;
        if (param_1 == 3) {
            int iVar1 = 0;
            pCVar2 = DAT_ARRAY_00ec0348::instance;
            while (pCVar2->isValid) {
                pCVar2 = pCVar2 + 1;
                iVar1 = iVar1 + 1;
                if (0xec0827 < (int)pCVar2) {
                    return;
                }
            }
            if (iVar1 != -1) {
                DAT_ARRAY_00ec0348::instance[iVar1].isValid = 3;
                DAT_ARRAY_00ec0348::instance[iVar1].blendStrength = 0.0f;
                DAT_ARRAY_00ec0348::instance[iVar1].xSpace = param_2;
                DAT_ARRAY_00ec0348::instance[iVar1].x = param_3;
                DAT_ARRAY_00ec0348::instance[iVar1].y = param_4;
                DAT_ARRAY_00ec0348::instance[iVar1].width = param_5;
                DAT_ARRAY_00ec0348::instance[iVar1].height = param_6;
                DAT_ARRAY_00ec0348::instance[iVar1].fadeMode = param_7;
                DAT_ARRAY_00ec0348::instance[iVar1].field7_0x1c = param_8;
            }
        }
        return;
    }

}
}
