#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_00eb0e40.hpp"
#include "OpenSHC/Globals/DAT_00ed2bd8.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/INT_00eb1230.hpp"
#include "OpenSHC/Globals/INT_00eb9ac0.hpp"
#include "OpenSHC/Globals/INT_00ec083c.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA300
        void ResetCredits()
        {
            for (int i = 0; i < 24; i++) {
                DAT_ARRAY_00ec0348::instance[i].type = 0;
            }
            DAT_UnknownBinkCount::instance = 0;
            INT_00ec083c::instance = 0.0f;
            DAT_UnknownBinkIndex::instance = 0;
            DAT_NumberOfStoredMenuStrings::instance = 0;
            INT_00ed27a4::instance = 0;
            DAT_00eb0e40::instance = 0;
            DWORD_00eb9ac4::instance = 0;
            DAT_00ed2bd8::instance = 0;
            INT_00eb1230::instance = 0;
            INT_00eb9ac0::instance = 0;
        }

    }
}
}
