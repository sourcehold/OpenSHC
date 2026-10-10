#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523520
        undefined4 TribesState::hasAvailableSpawnSlotForWildlifeOrMercs()
        {
            int iVar1;
            bool bVar4;
            if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY)
                && (iVar1 = 0, DAT_GameState::instance.mapAndTime.wildlifeCount < 0xa0)) {
                do {
                    if (iVar1 < 4) {
                        uint uVar3 = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar1][0];
                        uint uVar2 = (uint)DAT_GameState::instance.mapAndTime.rabbitSpawnXY[iVar1][1];
                        if ((uVar3 < 400) && (uVar2 < 400)) {
                            bVar4 = *(char*)(uVar2 * 400 + 0x21aec98 + uVar3) == '\0';
                            goto LAB_00523574;
                        }
                    } else {
                        bVar4 = DAT_GameState::instance.mapAndTime.mercRecruitable[iVar1 + 4] == 0;
                    LAB_00523574:
                        if (!bVar4) {
                            return (undefined4)(1);
                        }
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < 0xc);
            }
            return (undefined4)(0);
        }

    }
}
}
