#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D48F0
    void AICState ::aiBuyAndSellGoods(int playerID)

    {

        PlayerData* _pPlayerData;

        int _pMarketID;

        _pMarketID = DAT_GameState::instance.playerDataArray[playerID].marketplace.id;

        DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk = 0;

        if (_pMarketID != 0) {

            DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk = 1;
        }

        if (DAT_GameState::instance.playerDataArray[playerID].hasMarketUnk != 0) {

            _pPlayerData = &DAT_GameState::instance.playerDataArray[playerID];

            _pPlayerData->willBuy = _pPlayerData->willBuy ^ TRUE;

            if (_pPlayerData->willBuy == FALSE) {

                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sellExcessGoods, this)(playerID);

                return;
            }

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::buyRequiredGoods, this)(playerID);

            return;
        }

        return;
    }

}
}
