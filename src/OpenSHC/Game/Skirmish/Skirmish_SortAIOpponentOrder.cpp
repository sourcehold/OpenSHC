#include "../Skirmish.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/INT_00eb9b60.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed27f0.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2be0.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9290
        void Skirmish_SortAIOpponentOrder(int reverseOrder)
        {
            int buffer[countof(INT_ARRAY_00eb96d8::instance)];
            memset(buffer, 0, sizeof(buffer));
            for (int i = 0; i < (int)INT_00eb9b60::instance; ++i) {
                uint maxValue;
                int best = -1;
                for (int j = 0; j < (int)INT_00eb9b60::instance; ++j) {
                    if (buffer[j] == 0 && (best == -1 || (uint)INT_ARRAY_00ed2be0::instance[j] > maxValue)) {
                        maxValue = INT_ARRAY_00ed2be0::instance[j];
                        best = j;
                    }
                }
                if (best < 0) {
                    best = 0;
                }
                INT_ARRAY_00eb96d8::instance[i] = INT_ARRAY_00ed27f0::instance[best];
                buffer[best] = 1;
            }

            if (DAT_MissionDefinedData::instance.sortColumn == 2 && (int)INT_00eb9b60::instance > 1
                && DAT_00ed3124::instance != 1) {
                for (int pass = 0; pass < 2500; ++pass) {
                    int swaps = 0;
                    for (int i = 1; i < (int)INT_00eb9b60::instance; ++i) {
                        OpenSHC::IO::SkMasterDataEntry* const a
                            = &DAT_SkMasters2DataArray::instance[INT_ARRAY_00eb96d8::instance[i - 1]];
                        OpenSHC::IO::SkMasterDataEntry* const b
                            = &DAT_SkMasters2DataArray::instance[INT_ARRAY_00eb96d8::instance[i]];
                        if (_stricmp(a->mapName, b->mapName) > 0) {
                            int const swap = INT_ARRAY_00eb96d8::instance[i];
                            INT_ARRAY_00eb96d8::instance[i] = INT_ARRAY_00eb96d8::instance[i - 1];
                            INT_ARRAY_00eb96d8::instance[i - 1] = swap;
                            ++swaps;
                        }
                    }
                    if (swaps == 0) {
                        break;
                    }
                }
            }

            if (reverseOrder != 0) {
                return;
            }
            memcpy(buffer, INT_ARRAY_00eb96d8::instance, sizeof(buffer));
            for (int i = 0; i < (int)INT_00eb9b60::instance; ++i) {
                INT_ARRAY_00eb96d8::instance[i] = buffer[INT_00eb9b60::instance - 1 - i];
            }
        }

    }
}
}
