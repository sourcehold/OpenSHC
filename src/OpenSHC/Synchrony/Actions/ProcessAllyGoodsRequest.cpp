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
    void Actions::ProcessAllyGoodsRequest(int param_1, ResourceType param_2, int param_3, int param_4)
    {
        ResourceType resourceType = param_2;
        if (resourceType == RT_GOLD) {
            if (DAT_GameState::instance.playerDataArray[param_4].currentResources[RT_GOLD] < param_3) {
                param_3 = DAT_GameState::instance.playerDataArray[param_4].currentResources[RT_GOLD];
            }
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[param_1] += param_3;
            DAT_GameState::instance.playerDataArray[param_1].currentResources[RT_GOLD] += param_3;
            DAT_GameState::instance.playerDataArray[param_4].currentResources[RT_GOLD] -= param_3;
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[param_4] += param_3;
        } else {
            if (resourceType == RT_PARTIALPITCH) {
                resourceType = RT_PITCH;
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain, DAT_BuildingsState::ptr)(
                param_1, resourceType, param_3);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                param_4, resourceType, param_3, 0);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[param_1] += MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(param_1, resourceType, param_3);
            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[param_4] += MACRO_CALL_MEMBER(
                Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(param_1, resourceType, param_3);
        }
        if (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            switch (param_2) {
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
            if (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 1));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    param_4, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s___005a7674,
                    param_3,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_GOODS, param_2));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    param_4, param_1);
            }
            if (param_4 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_ALLIES2, 2));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    param_4, 0);
                MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__d__s_005a766c,
                    param_3,
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_GOODS, param_2));
                MACRO_CALL_MEMBER(GameSynchronyState_Func::addChatMessageToDisplayList, DAT_GameSynchronyState::ptr)(
                    param_4, 0);
            }
        }
        if (param_2 == DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray1Unk[param_1]) {
            DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray1Unk[param_1] = 0;
            DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray2Unk[param_1] = 0;
        }
        MACRO_CALL_MEMBER(AI::AICState_Func::playThanksBikFromPlayerToPlayer, DAT_AICState::ptr)(param_1, param_4);
    }

}
}
