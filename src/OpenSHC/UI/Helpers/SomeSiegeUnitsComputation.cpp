#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray_2.hpp"
#include "OpenSHC/Globals/DAT_SiegeRemainingPoints.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00b960b8.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0042C1E0
    void Helpers::SomeSiegeUnitsComputation(int slot)
    {
        // The value table starts at ARCHER (7 entries of 3), the slot percentages at field_0x548dc.
        int* const unitValues = &DAT_RenderingDefinedData::instance.ARCHER;
        int* const slotPercentages = &DAT_RenderingDefinedData::instance.field_0x548dc;
        int total = INT_ARRAY_00b960b8::instance[1];
        for (int unit = 0; unit < 7; ++unit) {
            for (int value = 0; value < 3; ++value) {
                total += DAT_SiegeInformationArray_2::instance[1][unit][value] * unitValues[unit * 3 + value];
            }
        }
        int budgets[4];
        for (int budget = 0; budget < 4; ++budget) {
            budgets[budget] = slotPercentages[budget] * total / 100;
        }
        INT_ARRAY_00b960b8::instance[0] = DAT_SiegeRemainingPoints::instance;
        INT_ARRAY_00b960b8::instance[1] = DAT_SiegeRemainingPoints::instance;
        INT_ARRAY_00b960b8::instance[2] = DAT_SiegeRemainingPoints::instance;
        INT_ARRAY_00b960b8::instance[3] = DAT_SiegeRemainingPoints::instance;
        for (int setup = 0; setup < 4; ++setup) {
            // The 7 units by 3 values are copied as one run of 21.
            for (int value = 0; value < 21; ++value) {
                DAT_SiegeInformationArray_2::instance[setup][value / 3][value % 3]
                    = DAT_SiegeInformationArray::instance[value / 3][value % 3];
            }
        }
        if (slot != 1) {
            int const percentage = slotPercentages[slot];
            int cost = 0;
            for (int unit = 0; unit < 7; ++unit) {
                DAT_SiegeInformationArray_2::instance[1][unit][0]
                    = DAT_SiegeInformationArray_2::instance[slot][unit][0] * 100 / percentage;
                DAT_SiegeInformationArray_2::instance[1][unit][1]
                    = DAT_SiegeInformationArray_2::instance[slot][unit][1] * 100 / percentage;
                DAT_SiegeInformationArray_2::instance[1][unit][2]
                    = DAT_SiegeInformationArray_2::instance[slot][unit][2] * 100 / percentage;
                cost += DAT_SiegeInformationArray_2::instance[1][unit][0] * unitValues[unit * 3]
                    + DAT_SiegeInformationArray_2::instance[1][unit][1] * unitValues[unit * 3 + 1]
                    + DAT_SiegeInformationArray_2::instance[1][unit][2] * unitValues[unit * 3 + 2];
            }
            INT_ARRAY_00b960b8::instance[1] = total - cost;
            if (INT_ARRAY_00b960b8::instance[1] < 0) {
                INT_ARRAY_00b960b8::instance[1] = 0;
            }
        }
        for (int other = 0; other < 4; ++other) {
            if (other == slot || other == 1) {
                continue;
            }
            int const percentage = slotPercentages[other];
            int cost = 0;
            for (int unit = 0; unit < 7; ++unit) {
                for (int value = 0; value < 3; ++value) {
                    DAT_SiegeInformationArray_2::instance[other][unit][value]
                        = DAT_SiegeInformationArray_2::instance[1][unit][value] * percentage / 100;
                    cost += DAT_SiegeInformationArray_2::instance[other][unit][value] * unitValues[unit * 3 + value];
                }
            }
            INT_ARRAY_00b960b8::instance[other] = budgets[other] - cost;
            if (INT_ARRAY_00b960b8::instance[other] < 0) {
                INT_ARRAY_00b960b8::instance[other] = 0;
            }
        }
    }

}
}
