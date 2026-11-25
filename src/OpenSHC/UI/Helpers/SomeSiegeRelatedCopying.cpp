#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00b960b8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C540
    void Helpers::SomeSiegeRelatedCopying(int slot)
    {
        int const(&setup)[7][3] = DAT_SiegeInformationArray_2::instance[slot];
        for (int unit = 0; unit < 7; ++unit) {
            for (int value = 0; value < 3; ++value) {
                DAT_SiegeInformationArray::instance[unit][value] = setup[unit][value];
            }
        }
        DAT_SiegeRemainingPoints::instance = INT_ARRAY_00b960b8::instance[slot];
    }

}
}
