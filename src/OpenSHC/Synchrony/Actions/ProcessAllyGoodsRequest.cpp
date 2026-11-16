#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using namespace OpenSHC::Game::Resources;

    // FUNCTION: STRONGHOLDCRUSADER 0x004ADDD0
    void Actions::ProcessAllyGoodsRequest(
        int receiverPlayerID, ResourceType requestedResource, int amount, int senderPlayerID)
    {
        ResourceType resourceType = requestedResource;
        if (resourceType == RT_GOLD) {
            if (DAT_GameState::instance.playerDataArray[senderPlayerID].currentResources[RT_GOLD] < amount) {
                amount = DAT_GameState::instance.playerDataArray[senderPlayerID].currentResources[RT_GOLD];
            }
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[receiverPlayerID] += amount;
            DAT_GameState::instance.playerDataArray[receiverPlayerID].currentResources[RT_GOLD] += amount;
            DAT_GameState::instance.playerDataArray[senderPlayerID].currentResources[RT_GOLD] -= amount;
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[senderPlayerID] += amount;
        } else {
            if (resourceType == RT_PARTIALPITCH) {
                resourceType = RT_PITCH;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain, DAT_BuildingsState::ptr)(
                receiverPlayerID, resourceType, amount);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                senderPlayerID, resourceType, amount, 0);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[receiverPlayerID]
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    receiverPlayerID, resourceType, amount);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[senderPlayerID]
                += MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                    receiverPlayerID, resourceType, amount);
        }
        if (receiverPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            switch (requestedResource) {
            case RT_IRON:
            case RT_GOLD:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    Audio::SFX::SEID_IRON_DEPOSIT);
                break;
            case RT_BOW:
            case RT_CROSSBOW:
            case RT_SPEAR:
            case RT_PIKE:
            case RT_MACE:
            case RT_SWORD:
            case RT_LEATHERARMOR:
            case RT_IRONARMOR:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    Audio::SFX::SEID_SWORD_DEPOSIT);
                break;
            default:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    Audio::SFX::SEID_FLOUR_DEPOSIT);
                break;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER) {
            if (receiverPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 1));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    senderPlayerID, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s___005a7674,
                    amount,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_GOODS, requestedResource));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    senderPlayerID, receiverPlayerID);
            }
            if (senderPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 2));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    senderPlayerID, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s_005a766c,
                    amount,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_GOODS, requestedResource));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    senderPlayerID, 0);
            }
        }
        if (requestedResource
            == DAT_GameState::instance.playerDataArray[senderPlayerID].goodsRequestTypeByPlayer[receiverPlayerID]) {
            DAT_GameState::instance.playerDataArray[senderPlayerID].goodsRequestTypeByPlayer[receiverPlayerID] = 0;
            DAT_GameState::instance.playerDataArray[senderPlayerID].goodsRequestAmountByPlayer[receiverPlayerID] = 0;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::playThanksBikFromPlayerToPlayer, DAT_AICState::ptr)(
            receiverPlayerID, senderPlayerID);
    }

}
}
