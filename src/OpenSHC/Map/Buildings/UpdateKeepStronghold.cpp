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

    // FUNCTION: STRONGHOLDCRUSADER 0x00417AA0
    void Buildings::UpdateKeepStronghold()
    {
        int* piVar1;
        int sVar2;
        short sVar3;
        byte bVar4;
        int _goldStep;
        int _buildingID;
        int _currentStartingGold;
        _buildingID = DAT_CurrentBuildingID::instance;
        sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[_buildingID].currentHealth
            = DAT_BuildingsState::instance.buildings[_buildingID].maxHealth;
        DAT_BuildingsState::instance.buildings[_buildingID].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[_buildingID].extraAnimationSprite1 = 0x1b;
        DAT_BuildingsState::instance.buildings[_buildingID].someX
            = DAT_BuildingsState::instance.buildings[_buildingID].x + 5;
        bVar4 = (byte)DAT_GameCore::instance.mapTimeInTicks & 3;
        DAT_BuildingsState::instance.buildings[_buildingID].someY
            = DAT_BuildingsState::instance.buildings[_buildingID].y + 4;
        if (!bVar4 && DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
            && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT) {
            _currentStartingGold = DAT_GameState::instance.playerDataArray[sVar2].startResources[0xf];
            if (0 < _currentStartingGold) {
                _goldStep = 1;
                if (_currentStartingGold < 0x3e9) {
                    if (100 < _currentStartingGold) {
                        _goldStep = 10;
                    }
                } else {
                    _goldStep = 100;
                }
                piVar1 = DAT_GameState::instance.playerDataArray[sVar2].currentResources + 0xf;
                *piVar1 = *piVar1 + _goldStep;
                DAT_BuildingsState::instance.buildings[_buildingID].resourceRelatedCountDown = 100;
                sVar3 = (short)DAT_GameState::instance.playerDataArray[sVar2].currentResources[0xf];
                DAT_GameState::instance.playerDataArray[sVar2].startResources[0xf] = _currentStartingGold - _goldStep;
                DAT_GameState::instance.playerDataArray[sVar2].beforeLastMonthsGold = sVar3;
                DAT_GameState::instance.playerDataArray[sVar2].lastMonthsGold = sVar3;
                DAT_GameCore::instance.countdown = 1;
            }
        }
    }

}
}
