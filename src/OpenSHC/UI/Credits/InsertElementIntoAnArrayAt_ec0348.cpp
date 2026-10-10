#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAD40
    void Credits::InsertElementIntoAnArrayAt_ec0348(
        int state, int xSpace, int param_3, int x, int y, int width, int param_7, int param_8, int param_9)
    {
        CreditsRelatedStructure* pCVar2;
        if ((state == 1) || (state == 4)) {
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
                DAT_ARRAY_00ec0348::instance[iVar1].isValid = state;
                DAT_ARRAY_00ec0348::instance[iVar1].blendStrength = 0.0f;
                DAT_ARRAY_00ec0348::instance[iVar1].xSpace = xSpace;
                DAT_ARRAY_00ec0348::instance[iVar1].field11_0x2c = param_3;
                DAT_ARRAY_00ec0348::instance[iVar1].x = x;
                DAT_ARRAY_00ec0348::instance[iVar1].y = y;
                DAT_ARRAY_00ec0348::instance[iVar1].width = width;
                DAT_ARRAY_00ec0348::instance[iVar1].height = param_7;
                DAT_ARRAY_00ec0348::instance[iVar1].fadeMode = param_8;
                DAT_ARRAY_00ec0348::instance[iVar1].field7_0x1c = param_9;
                if (param_8 == 1) {
                    DAT_ARRAY_00ec0348::instance[iVar1].blendStrength = 31.0f;
                    return;
                }
                if (param_8 == 2) {
                    DAT_ARRAY_00ec0348::instance[iVar1].blendStrength = 1.0f;
                }
            }
        }
        return;
    }

}
}
