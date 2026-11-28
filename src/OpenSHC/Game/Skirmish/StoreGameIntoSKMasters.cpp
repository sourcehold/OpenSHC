#include "../../Game.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D52A0
    void Skirmish::StoreGameIntoSKMasters(int score)
    {
        if (!MACRO_CALL(Game::Skirmish_Func::StoreCurrentGameIntoTemporarySKMasterEntry)(score)) {
            return;
        }
        int count = DAT_SkMasters2Data_Count::instance;
        int insertIndex = -1;
        if (count <= 0) {
            insertIndex = 0;
        }
        if (count < 250) {
            insertIndex = count;
        }
        if (insertIndex != 0) {
            for (int i = 0; i < count; i++) {
                if (DAT_SkMasterDataEntry::instance.skMasterScore
                    > DAT_SkMasters2DataArray::instance[i].skMasterScore) {
                    insertIndex = i;
                    break;
                }
            }
            if (insertIndex == -1) {
                return;
            }
        }
        for (; count > insertIndex; count--) {
            if (count <= 249) {
                DAT_SkMasters2DataArray::instance[count] = DAT_SkMasters2DataArray::instance[count - 1];
            }
        }
        DAT_SkMasters2DataArray::instance[insertIndex] = DAT_SkMasterDataEntry::instance;
        if (DAT_SkMasters2Data_Count::instance < 250) {
            DAT_SkMasters2Data_Count::instance = DAT_SkMasters2Data_Count::instance + 1;
        }
        MACRO_CALL(IO_Func::WriteSkMasters2)();
    }

}
}
