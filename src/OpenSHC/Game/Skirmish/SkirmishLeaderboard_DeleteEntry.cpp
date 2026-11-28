#include "../../Game.func.hpp"
#include "../Skirmish.func.hpp"

#include "OpenSHC/IO.func.hpp"

#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"

namespace OpenSHC {
namespace Game {

    /*
      This removes the skirmish leaderboard entry at a given index by shifting all subsequent entries   down by one,
      decrementing the count, and saving to disk. It's the delete operation for the   SkMasters2 high score / results
      table — likely called when the player deletes a saved skirmish   result from the UI.      decompilerscript:
      committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D5370
    void Skirmish::SkirmishLeaderboard_DeleteEntry(int index)
    {
        SkMasterDataEntry* pSVar1;
        int iVar2;
        SkMasterDataEntry* pSVar3;
        SkMasterDataEntry* pSVar4;
        if ((-1 < index) && (index < DAT_SkMasters2Data_Count::instance)) {
            if (index < DAT_SkMasters2Data_Count::instance + -1) {
                pSVar1 = DAT_SkMasters2DataArray::instance + index;
                do {
                    pSVar3 = pSVar1 + 1;
                    pSVar4 = pSVar1;
                    for (iVar2 = 0x2fc; iVar2 != 0; iVar2 = iVar2 + -1) {
                        pSVar4->score = pSVar3->score;
                        pSVar3 = (SkMasterDataEntry*)pSVar3->mapName;
                        pSVar4 = (SkMasterDataEntry*)pSVar4->mapName;
                    }
                    index = index + 1;
                    pSVar1 = pSVar1 + 1;
                } while (index < DAT_SkMasters2Data_Count::instance + -1);
            }
            DAT_SkMasters2Data_Count::instance = DAT_SkMasters2Data_Count::instance + -1;
            MACRO_CALL(IO_Func::WriteSkMasters2)();
        }
    }

}
}
