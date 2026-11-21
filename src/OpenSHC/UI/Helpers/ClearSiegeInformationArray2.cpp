#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00b960b8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C190
    void Helpers::ClearSiegeInformationArray2()
    {
        INT_ARRAY_00b960b8::instance[0] = 0;
        INT_ARRAY_00b960b8::instance[1] = 0;
        INT_ARRAY_00b960b8::instance[2] = 0;
        INT_ARRAY_00b960b8::instance[3] = 0;
        // The original clears only the first 11 of each setup's 21 values.
        for (int setup = 0; setup < 4; ++setup) {
            int* const values = DAT_SiegeInformationArray_2::instance[setup][0];
            for (int value = 0; value < 11; ++value) {
                values[value] = 0;
            }
        }
    }

}
}
