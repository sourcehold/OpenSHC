#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AD7C0
    void Actions::ProcessAllyRequestingGoods(int askedPlayerID, int param_2, int amount, int askee)
    {
        if (param_2 + 1 == Game::Resources::RT_GOLD) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] == -1) {
                return;
            }
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray1Unk[askee]
                = (short)(param_2 + 1);
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray2Unk[askee] = (short)amount;
            if (askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 72));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    askee, 0);
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] != -1) {
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray1Unk[askee]
                = (short)(param_2 + 1);
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray2Unk[askee] = (short)amount;
            if (askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 72));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    askee, 0);
            }
            return;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::playGoodsSentBikFromPlayerToPlayer, DAT_AICState::ptr)(
            askedPlayerID, askee);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain, DAT_BuildingsState::ptr)(
            askee, (ResourceType)(param_2 + 1), amount);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
            askedPlayerID, (ResourceType)(param_2 + 1), amount, 0);
        DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[askee] += MACRO_CALL_MEMBER(
            Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(askedPlayerID, param_2 + 1, amount);
        DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[askedPlayerID] += MACRO_CALL_MEMBER(
            Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(askedPlayerID, param_2 + 1, amount);
    }

}
}
