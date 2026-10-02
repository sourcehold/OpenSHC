#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Audio::SFX::SoundEffectID;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeInt;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004ADDD0
    void Actions::ProcessAllyGoodsRequest(int param_1, ResourceType param_2, int param_3, int param_4)
    {
        int* piVar1;
        int* piVar2;
        char cVar3;
        int iVar4;
        char* pcVar5;
        char* pcVar6;
        ResourceTypeInt _resourceType;
        SoundEffectID sfxOffsetInArray;
        if (param_2 == OpenSHC::Game::Resources::RT_GOLD) {
            iVar4 = DAT_GameState::instance.playerDataArray[param_4].currentResources[0xf];
            piVar1 = DAT_GameState::instance.playerDataArray[param_4].currentResources + 0xf;
            if (iVar4 < param_3) {
                param_3 = iVar4;
            }
            piVar2 = DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved + param_1;
            *piVar2 = *piVar2 + param_3;
            piVar2 = DAT_GameState::instance.playerDataArray[param_1].currentResources + 0xf;
            *piVar2 = *piVar2 + param_3;
            *piVar1 = *piVar1 - param_3;
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGoodsSent + param_4;
            *piVar1 = *piVar1 + param_3;
        } else {
            _resourceType = param_2;
            if (param_2 == OpenSHC::Game::Resources::RT_PARTIALPITCH) {
                _resourceType = OpenSHC::Game::Resources::RT_PITCH;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(param_1, (ResourceType)((int)(_resourceType)), param_3);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                DAT_BuildingsState::ptr)(param_4, (ResourceType)((int)(_resourceType)), param_3, 0);
            iVar4 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                param_1, (int)((int)(_resourceType)), param_3);
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved + param_1;
            *piVar1 = *piVar1 + iVar4;
            iVar4 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellPrice, DAT_GameState::ptr)(
                param_1, (int)((int)(_resourceType)), param_3);
            piVar1 = DAT_GameSynchronyState::instance.finalResults.finalGoodsSent + param_4;
            *piVar1 = *piVar1 + iVar4;
        }
        if (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            switch (param_2) {
            case OpenSHC::Game::Resources::RT_IRON:
            case OpenSHC::Game::Resources::RT_GOLD:
                sfxOffsetInArray = OpenSHC::Audio::SFX::SEID_IRON_DEPOSIT;
                break;
                default:
                    sfxOffsetInArray = OpenSHC::Audio::SFX::SEID_FLOUR_DEPOSIT;
                break;
            case OpenSHC::Game::Resources::RT_BOW:
            case OpenSHC::Game::Resources::RT_CROSSBOW:
            case OpenSHC::Game::Resources::RT_SPEAR:
            case OpenSHC::Game::Resources::RT_PIKE:
            case OpenSHC::Game::Resources::RT_MACE:
            case OpenSHC::Game::Resources::RT_SWORD:
            case OpenSHC::Game::Resources::RT_LEATHERARMOR:
            case OpenSHC::Game::Resources::RT_IRONARMOR:
                sfxOffsetInArray = OpenSHC::Audio::SFX::SEID_SWORD_DEPOSIT;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                sfxOffsetInArray);
        }
        if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            if (param_1 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                /*
                  added by script: "Goods received from ally"
                 */
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 1);
                pcVar6 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar3 = *pcVar5;
                    *pcVar6 = cVar3;
                    pcVar5 = pcVar5 + 1;
                    pcVar6 = pcVar6 + 1;
                } while (cVar3 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(param_4, 0);
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, (int)((int)(param_2)));
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    DAT_GameSynchronyState::instance.receivedChatMessage, "%d %s - ", param_3, pcVar5);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(param_4, param_1);
            }
            if (param_4 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                /*
                  added by script: "Goods sent to ally"
                 */
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES2, 2);
                pcVar6 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar3 = *pcVar5;
                    *pcVar6 = cVar3;
                    pcVar5 = pcVar5 + 1;
                    pcVar6 = pcVar6 + 1;
                } while (cVar3 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(param_4, 0);
                pcVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GOODS, (int)((int)(param_2)));
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                    DAT_GameSynchronyState::instance.receivedChatMessage, "%d %s", param_3, pcVar5);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(param_4, 0);
            }
        }
        if (param_2 == (int)DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray1Unk[param_1]) {
            DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray1Unk[param_1] = 0;
            DAT_GameState::instance.playerDataArray[param_4].requestedGoodsArray2Unk[param_1] = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::playThanksBikFromPlayerToPlayer, DAT_AICState::ptr)(
            param_1, param_4);
    }

}
}
