#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DAD40
        void InsertElementIntoAnArrayAt_ec0348(
            int state, int xSpace, int field11, int x, int y, int width, int height, int fadeMode, int field7)
        {
            if (state != 1 && state != 4) {
                return;
            }
            int index = -1;
            for (int i = 0; i < 24; i++) {
                if (DAT_ARRAY_00ec0348::instance[i].type == 0) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                return;
            }
            DAT_ARRAY_00ec0348::instance[index].type = state;
            DAT_ARRAY_00ec0348::instance[index].blendStrength = 0.0f;
            DAT_ARRAY_00ec0348::instance[index].xSpace = xSpace;
            DAT_ARRAY_00ec0348::instance[index].field_0x2c = field11;
            DAT_ARRAY_00ec0348::instance[index].x = x;
            DAT_ARRAY_00ec0348::instance[index].y = y;
            DAT_ARRAY_00ec0348::instance[index].width = width;
            DAT_ARRAY_00ec0348::instance[index].height = height;
            DAT_ARRAY_00ec0348::instance[index].fadeMode = fadeMode;
            DAT_ARRAY_00ec0348::instance[index].field_0x1c = field7;
            if (fadeMode == 1) {
                DAT_ARRAY_00ec0348::instance[index].blendStrength = 31.0f;
            } else if (fadeMode == 2) {
                DAT_ARRAY_00ec0348::instance[index].blendStrength = 1.0f;
            }
        }

    }
}
}
