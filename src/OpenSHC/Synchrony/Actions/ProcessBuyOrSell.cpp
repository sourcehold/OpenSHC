#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00465E60
    void Actions::ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType)
    {
        int* piVar1;
        int _buyPrice;
        BOOLEnum BVar2;
        int _salesCount;
        int _salesPrice;
        if (!buyOrSell) {
            /*
              buying?
             */
            _buyPrice = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBatchBuyPrice, DAT_GameState::ptr)(
                playerID, (int)(resourceType));
            if ((_buyPrice <= DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf])
                && (BVar2 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, resourceType, 5),
                    BVar2)) {
                piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xf;
                *piVar1 = *piVar1 - _buyPrice;
                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].marketGold;
                *piVar1 = *piVar1 - _buyPrice;
            }
        } else if ((buyOrSell == 1)
            && (-1 < DAT_GameState::instance.playerDataArray[playerID].currentResources[resourceType])) {
            _salesCount = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellResourceAmount, DAT_GameState::ptr)(
                playerID, (int)(resourceType));
            /*
              selling?
             */
            _salesPrice = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalesPrice, DAT_GameState::ptr)(
                playerID, (int)(resourceType));
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGold + playerID;
            *piVar1 = *piVar1 + _salesPrice;
            piVar1 = DAT_GameState::instance.playerDataArray[playerID].currentResources + 0xf;
            *piVar1 = *piVar1 + _salesPrice;
            piVar1 = &DAT_GameState::instance.playerDataArray[playerID].marketGold;
            *piVar1 = *piVar1 + _salesPrice;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                playerID, resourceType, _salesCount, 0);
        }
    }

}
}
