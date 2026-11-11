#include "../AICState.func.hpp"

#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D48F0
    void AICState::aiBuyAndSellGoods(int playerID)
    {
        int marketID = DAT_GameState::instance.playerDataArray[playerID]
                           .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                           .id;
        DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk = 0;
        if (marketID != 0)
            DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk = 1;
        if (DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk == 0)
            return;

        DAT_GameState::instance.playerDataArray[playerID].willBuy ^= TRUE;
        if (!DAT_GameState::instance.playerDataArray[playerID].willBuy) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellExcessGoods, this)(playerID);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::buyRequiredGoods, this)(playerID);
    }

}
}
