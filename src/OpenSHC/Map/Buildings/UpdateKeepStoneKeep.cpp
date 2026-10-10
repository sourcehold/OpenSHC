#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x004179B0
    void Buildings::UpdateKeepStoneKeep()
    {
        int* piVar1;
        int sVar2;
        short sVar3;
        int iVar4;
        byte bVar5;
        int iVar6;
        int iVar7;
        iVar6 = DAT_CurrentBuildingID::instance;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[iVar6].currentHealth
            = DAT_BuildingsState::instance.buildings[iVar6].maxHealth;
        DAT_BuildingsState::instance.buildings[iVar6].someX = DAT_BuildingsState::instance.buildings[iVar6].x + 3;
        bVar5 = (byte)DAT_GameCore::instance.mapTimeInTicks & 3;
        DAT_BuildingsState::instance.buildings[iVar6].someY = DAT_BuildingsState::instance.buildings[iVar6].y + 2;
        DAT_BuildingsState::instance.buildings[iVar6].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite1 = 0x18;
        if (!bVar5 && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT) {
            iVar4 = DAT_GameState::instance.playerDataArray[sVar2].startResources[0xf];
            if (0 < iVar4) {
                iVar7 = 1;
                if (iVar4 < 0x3e9) {
                    if (100 < iVar4) {
                        iVar7 = 10;
                    }
                } else {
                    iVar7 = 100;
                }
                piVar1 = DAT_GameState::instance.playerDataArray[sVar2].currentResources + 0xf;
                *piVar1 = *piVar1 + iVar7;
                DAT_BuildingsState::instance.buildings[iVar6].resourceRelatedCountDown = 100;
                sVar3 = (short)DAT_GameState::instance.playerDataArray[sVar2].currentResources[0xf];
                DAT_GameState::instance.playerDataArray[sVar2].startResources[0xf] = iVar4 - iVar7;
                DAT_GameState::instance.playerDataArray[sVar2].beforeLastMonthsGold = sVar3;
                DAT_GameState::instance.playerDataArray[sVar2].lastMonthsGold = sVar3;
                DAT_GameCore::instance.countdown = 1;
            }
        }
    }

}
}
