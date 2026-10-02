#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::Resources::ResourceType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AD7C0
    void Actions::ProcessAllyRequestingGoods(int askedPlayerID, int param_2, int amount, int askee)
    {
        int* piVar1;
        char cVar2;
        char* pcVar3;
        int _gold1;
        int _gold2;
        char* pcVar4;
        bool bVar5;
        ResourceType _resourceType;
        _resourceType = (OpenSHC::Game::Resources::ResourceType)(param_2 + OpenSHC::Game::Resources::RT_LOGS);
        if (_resourceType == OpenSHC::Game::Resources::RT_GOLD) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] != -1) {
                bVar5 = askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID;
                DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray1Unk[askee]
                    = (short)param_2 + 1;
                DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray2Unk[askee] = (short)amount;
                if (bVar5) {
                    /*
                      added by script: "is requesting goods from you"
                     */
                    pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x48);
                    pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                    do {
                        cVar2 = *pcVar3;
                        *pcVar4 = cVar2;
                        pcVar3 = pcVar3 + 1;
                        pcVar4 = pcVar4 + 1;
                    } while (cVar2 != '\0');
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                        DAT_GameSynchronyState::ptr)(askee, 0);
                }
            }
        } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[askedPlayerID] == -1) {
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playGoodsSentBikFromPlayerToPlayer, DAT_AICState::ptr)(
                askedPlayerID, askee);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(askee, _resourceType, amount);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(askedPlayerID, _resourceType, amount, 0);
            _gold1 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                askedPlayerID, (int)((int)(_resourceType)), amount);
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved + askee;
            *piVar1 = *piVar1 + _gold1;
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGoodsSent + askedPlayerID;
            _gold2 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                askedPlayerID, (int)((int)(_resourceType)), amount);
            *piVar1 = *piVar1 + _gold2;
        } else {
            bVar5 = askedPlayerID == DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray1Unk[askee] = (short)param_2 + 1;
            DAT_GameState::instance.playerDataArray[askedPlayerID].requestedGoodsArray2Unk[askee] = (short)amount;
            if (bVar5) {
                /*
                  added by script: "is requesting goods from you"
                 */
                pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x48);
                pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar2 = *pcVar3;
                    *pcVar4 = cVar2;
                    pcVar3 = pcVar3 + 1;
                    pcVar4 = pcVar4 + 1;
                } while (cVar2 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(askee, 0);
            }
        }
    }

}
}
