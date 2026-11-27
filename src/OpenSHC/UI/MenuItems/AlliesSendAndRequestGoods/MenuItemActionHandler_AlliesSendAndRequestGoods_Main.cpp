#include "../AlliesSendAndRequestGoods.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeMin1.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df4284.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B14C0
        void AlliesSendAndRequestGoods::MenuItemActionHandler_AlliesSendAndRequestGoods_Main(int button, ...)
        {
            int const playerID = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
            if (button == 40) {
                return;
            }
            if (button <= 20) {
                // a good's button: the list skips RTM_PARTIALSTONE and RTM_PITCH, and has iron armour in gold's place
                DAT_RequestedGoodsByWhoArray::instance[0] = button;
                if (button >= 4) {
                    DAT_RequestedGoodsByWhoArray::instance[0] = button + 1;
                }
                if (button >= 5) {
                    DAT_RequestedGoodsByWhoArray::instance[0]++;
                }
                if (DAT_RequestedGoodsByWhoArray::instance[0] == OpenSHC::Game::Resources::RTM_GOLD) {
                    DAT_RequestedGoodsByWhoArray::instance[0] = OpenSHC::Game::Resources::RTM_IRONARMOR;
                }
                return;
            }
            // gold
            if (button == 21) {
                DAT_RequestedGoodsByWhoArray::instance[0] = OpenSHC::Game::Resources::RTM_GOLD;
                return;
            }
            // the amount's buttons
            if (button == 50) {
                DAT_SentOrRequestedGoodsAmount::instance += 10;
                return;
            }
            if (button == 51) {
                DAT_SentOrRequestedGoodsAmount::instance += 25;
                return;
            }
            if (button == 52) {
                DAT_SentOrRequestedGoodsAmount::instance += 100;
                return;
            }
            if (button == 53) {
                DAT_SentOrRequestedGoodsAmount::instance += 5;
                return;
            }
            if (button == 54) {
                DAT_SentOrRequestedGoodsAmount::instance += 500;
                return;
            }
            // cancel: the choice is cleared, and an ally whose request this dialog answers gets command 3
            if (button == 102) {
                DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                DAT_SentOrRequestedGoodsAmount::instance = 0;
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    != OpenSHC::UI::Enums::MMT_ALLIES_SEND_GOODS) {
                    return;
                }
                if (!DAT_00df4284::instance) {
                    return;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 3;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                return;
            }
            // confirm, once a good and an amount are chosen
            if (button == 100) {
                if (DAT_RequestedGoodsByWhoArray::instance[0] <= -1) {
                    return;
                }
                if (DAT_SentOrRequestedGoodsAmount::instance <= 0) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_ALLIES_REQUEST_GOODS) {
                    if (DAT_RequestedGoodsByWhoArray::instance[0] + 1 == OpenSHC::Game::Resources::RT_GOLD) {
                        if (!MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade,
                                DAT_AICState::ptr)(playerID,
                                (OpenSHC::Game::Resources::ResourceType)(DAT_RequestedGoodsByWhoArray::instance[0] + 1),
                                DAT_SentOrRequestedGoodsAmount::instance)) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::playGoodsNotSentBikFromPlayer, DAT_AICState::ptr)(playerID);
                        } else {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_RequestedGoodsByWhoArray::instance[0];
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                                = DAT_SentOrRequestedGoodsAmount::instance;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                        }
                    } else {
                        int const space = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getResourceSpace, DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            (OpenSHC::Game::Resources::ResourceType)(DAT_RequestedGoodsByWhoArray::instance[0] + 1));
                        if (space == -1) {
                            // no building to put it in: the fail state says which one is missing
                            MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(
                                3, (OpenSHC::Game::Resources::ResourceType)DAT_RequestedGoodsByWhoArray::instance[0]);
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 6) {
                                // "No stockpile built"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning2_wav_005a5950);
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 5) {
                                // "No granary built"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning1_wav_005a593c);
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 7) {
                                // "No armory built"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning3_wav_005a5928);
                            }
                        } else if (space < DAT_SentOrRequestedGoodsAmount::instance) {
                            // not enough room in it
                            MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(
                                4, (OpenSHC::Game::Resources::ResourceType)DAT_RequestedGoodsByWhoArray::instance[0]);
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 9) {
                                // "No space in the stockpile"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning5_wav_005a50b0);
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 8) {
                                // "No space in the granary"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning4_wav_005a5914);
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .storageMarketFailState
                                == 10) {
                                // "No space in the armory"
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    s_space_warning6_wav_005a5900);
                            }
                        } else if (
                            !MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade,
                                DAT_AICState::ptr)(playerID,
                                (OpenSHC::Game::Resources::ResourceType)(DAT_RequestedGoodsByWhoArray::instance[0] + 1),
                                DAT_SentOrRequestedGoodsAmount::instance)) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::playGoodsNotSentBikFromPlayer, DAT_AICState::ptr)(playerID);
                        } else {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_RequestedGoodsByWhoArray::instance[0];
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                                = DAT_SentOrRequestedGoodsAmount::instance;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                        }
                    }
                    DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
                // sending: the ally needs room for it and the player has to have it; gold needs no room
                int const resource = DAT_RequestedGoodsByWhoArray::instance[0] + 1;
                int storedAs = resource;
                if (resource == OpenSHC::Game::Resources::RT_PARTIALPITCH) {
                    storedAs = resource - 1;
                }
                int amount = DAT_SentOrRequestedGoodsAmount::instance;
                if (resource == OpenSHC::Game::Resources::RT_GOLD) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                        < amount) {
                        return;
                    }
                } else {
                    int const space = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceSpace,
                        DAT_BuildingsState::ptr)(playerID, (OpenSHC::Game::Resources::ResourceType)storedAs);
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[storedAs]
                        < amount) {
                        return;
                    }
                    if (space < 0) {
                        return;
                    }
                    if (space < amount) {
                        amount = space;
                    }
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 2;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = resource;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = amount;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_ALLIES, FALSE);
        }

    }
}
}
