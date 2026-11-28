#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAE90
    void Credits::InsertElementIntoArrayAt_ec0348_2(
        int param_1, int xSpace, int param_3, int param_4, int x, int y, int param_7, int width, int param_9)
    {
        if (param_1 == 2) {
            int _index = -1;
            for (int i = 0; i < 24; i++) {
                if (DAT_ARRAY_00ec0348::instance[i].type == 0) {
                    _index = i;
                    break;
                }
            }
            if (_index != -1) {
                DAT_ARRAY_00ec0348::instance[_index].xSpace = xSpace;
                DAT_ARRAY_00ec0348::instance[_index].blendStrength = 0.0f;
                DAT_ARRAY_00ec0348::instance[_index].field_0x20 = param_3;
                DAT_ARRAY_00ec0348::instance[_index].x = x;
                DAT_ARRAY_00ec0348::instance[_index].y = y;
                DAT_ARRAY_00ec0348::instance[_index].width = width;
                DAT_ARRAY_00ec0348::instance[_index].field_0x24 = param_9;
                DAT_ARRAY_00ec0348::instance[_index].type = 2;
                DAT_ARRAY_00ec0348::instance[_index].fadeMode = param_7;
                DAT_ARRAY_00ec0348::instance[_index].field_0x28 = param_4;
                DAT_ARRAY_00ec0348::instance[_index].field_0x1c = 7;
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
