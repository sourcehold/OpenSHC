#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAE90
    void Credits::InsertElementIntoArrayAt_ec0348_2(
        int param_1, int xSpace, int param_3, int param_4, int x, int y, int param_7, int width, int param_9)
    {
        CreditsRelatedStructure* pCVar1;
        if (param_1 == 2) {
            int _index = 0;
            pCVar1 = DAT_ARRAY_00ec0348::instance;
            while (pCVar1->isValid) {
                pCVar1 = pCVar1 + 1;
                _index = _index + 1;
                if (0xec0827 < (int)pCVar1) {
                    return;
                }
            }
            if (_index != -1) {
                DAT_ARRAY_00ec0348::instance[_index].xSpace = xSpace;
                DAT_ARRAY_00ec0348::instance[_index].blendStrength = 0.0f;
                DAT_ARRAY_00ec0348::instance[_index].field8_0x20 = param_3;
                DAT_ARRAY_00ec0348::instance[_index].x = x;
                DAT_ARRAY_00ec0348::instance[_index].y = y;
                DAT_ARRAY_00ec0348::instance[_index].width = width;
                DAT_ARRAY_00ec0348::instance[_index].field9_0x24 = param_9;
                DAT_ARRAY_00ec0348::instance[_index].field10_0x28 = param_4;
                DAT_ARRAY_00ec0348::instance[_index].isValid = 2;
                DAT_ARRAY_00ec0348::instance[_index].fadeMode = param_7;
                DAT_ARRAY_00ec0348::instance[_index].field7_0x1c = 7;
                if (param_7 == 1) {
                    DAT_ARRAY_00ec0348::instance[_index].blendStrength = 31.0f;
                    return;
                }
                if (param_7 == 2) {
                    DAT_ARRAY_00ec0348::instance[_index].blendStrength = 1.0f;
                }
            }
        }
        return;
    }

}
}
