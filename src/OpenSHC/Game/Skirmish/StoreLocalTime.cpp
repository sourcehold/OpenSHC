#include "OpenSHC/Game/Skirmish.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C6CD0
        void StoreLocalTime()
        {
            SYSTEMTIME localTime;
            GetLocalTime(&localTime);
            DAT_SkMasterDataEntry::instance.localTimeDay = localTime.wDay;
            DAT_SkMasterDataEntry::instance.localTimeMonth = localTime.wMonth;
            DAT_SkMasterDataEntry::instance.localTimeYear = localTime.wYear;
            DAT_SkMasterDataEntry::instance.gameDurationInMinutes = (int)DAT_GameCore::instance.gameDuration / 60000;
            DAT_SkMasterDataEntry::instance.mapTimeInTicks = DAT_GameCore::instance.mapTimeInTicks;
        }

    }
}
}
