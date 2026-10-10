#include "../AlliesSendAndRequestGoods.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeMin1.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeMin1Int.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using Commands::GameCommandType;
        using Game::Resources::ResourceType;
        using Game::Resources::ResourceTypeInt;
        using Game::Resources::ResourceTypeMin1;
        using Game::Resources::ResourceTypeMin1Int;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B14C0
        void AlliesSendAndRequestGoods::MenuItemActionHandler_AlliesSendAndRequestGoods_Main(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            int _space;
            int playerID = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
            if (param_1 == 0x28) {}
            if (param_1 < 0x15) {
                DAT_RequestedGoodsByWhoArray::instance[0] = param_1;
                if (3 < param_1) {
                    DAT_RequestedGoodsByWhoArray::instance[0] = param_1 + 1;
                }
                if (4 < param_1) {
                    DAT_RequestedGoodsByWhoArray::instance[0] = DAT_RequestedGoodsByWhoArray::instance[0] + 1;
                }
                if (DAT_RequestedGoodsByWhoArray::instance[0] != 14) {}
                DAT_RequestedGoodsByWhoArray::instance[0] = 23;
            }
            if (param_1 == 0x15) {
                DAT_RequestedGoodsByWhoArray::instance[0] = 14;
            }
            if (param_1 == 0x32) {
                DAT_SentOrRequestedGoodsAmount::instance = DAT_SentOrRequestedGoodsAmount::instance + 10;
            }
            if (param_1 == 0x33) {
                DAT_SentOrRequestedGoodsAmount::instance = DAT_SentOrRequestedGoodsAmount::instance + 25;
            }
            if (param_1 == 0x34) {
                DAT_SentOrRequestedGoodsAmount::instance = DAT_SentOrRequestedGoodsAmount::instance + 100;
            }
            if (param_1 == 0x35) {
                DAT_SentOrRequestedGoodsAmount::instance = DAT_SentOrRequestedGoodsAmount::instance + 5;
            }
            if (param_1 != 0x36) {
                if (param_1 == 0x66) {
                    DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                    DAT_SentOrRequestedGoodsAmount::instance = 0;
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID != UI::Enums::MMT_ALLIES_SEND_GOODS) {
                        DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                        DAT_SentOrRequestedGoodsAmount::instance = 0;
                    }
                    if (!DAT_00df4284::instance) {
                        DAT_RequestedGoodsByWhoArray::instance[0] = -1;
                        DAT_SentOrRequestedGoodsAmount::instance = 0;
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 3;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                }
                if (param_1 != 100) {
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_ALLIES, FALSE);
                }
                if (-1 < DAT_RequestedGoodsByWhoArray::instance[0]) {
                    if (DAT_SentOrRequestedGoodsAmount::instance < 1) {}
                    if (DAT_MenuModalComposition1::instance.activeModalDialogID
                        == UI::Enums::MMT_ALLIES_REQUEST_GOODS) {
                        if ((int*)(DAT_RequestedGoodsByWhoArray::instance[0] + 1) == (int*)0xf) {
                            BVar1 = MACRO_CALL_MEMBER(
                                AI::AICState_Func::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade,
                                DAT_AICState::ptr)(
                                playerID, Game::Resources::RT_GOLD, (int)(DAT_SentOrRequestedGoodsAmount::instance));
                        } else {
                            iVar2 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getResourceSpace,
                                DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                (int*)((int)((DAT_RequestedGoodsByWhoArray::instance[0] + 1))));
                            if (iVar2 == -1) {
                                MACRO_CALL(UI::Actions_Func::SetStorageMarketFailState)(
                                    3, (ResourceType)((int)(DAT_RequestedGoodsByWhoArray::instance[0])));
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    == 6) {
                                    /*
                                      "No stockpile built"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "space_warning2.wav");
                                }
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    == 5) {
                                    /*
                                      "No granary built"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "space_warning1.wav");
                                }
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    != 7) {
                                    DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                                }
                                /*
                                  "No armory built"
                                 */
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    "space_warning3.wav");
                                DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                            }
                            if (iVar2 < DAT_SentOrRequestedGoodsAmount::instance) {
                                MACRO_CALL(UI::Actions_Func::SetStorageMarketFailState)(
                                    4, (ResourceType)((int)(DAT_RequestedGoodsByWhoArray::instance[0])));
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    == 9) {
                                    /*
                                      "No space in the stockpile"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "space_warning5.wav");
                                }
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    == 8) {
                                    /*
                                      "No space in the granary"
                                     */
                                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                        "space_warning4.wav");
                                }
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .storageMarketFailState
                                    != 10) {
                                    DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                                }
                                /*
                                  "No space in the armory"
                                 */
                                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                    "space_warning6.wav");
                                DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                            }
                            BVar1 = MACRO_CALL_MEMBER(
                                AI::AICState_Func::isResourceLargerOrEqualThanMinimumGoodsRequiredAfterTrade,
                                DAT_AICState::ptr)(playerID,
                                (ResourceType)((
                                    int)(DAT_RequestedGoodsByWhoArray::instance[0] + Game::Resources::RT_LOGS)),
                                (int)(DAT_SentOrRequestedGoodsAmount::instance));
                        }
                        if (BVar1) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                                = DAT_RequestedGoodsByWhoArray::instance[0];
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam3
                                = DAT_SentOrRequestedGoodsAmount::instance;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                                = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand,
                                DAT_GameSynchronyState::ptr)(Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                            DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                        }
                        MACRO_CALL_MEMBER(AI::AICState_Func::playGoodsNotSentBikFromPlayer, DAT_AICState::ptr)(
                            playerID);
                        DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                    }
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_ALLIES, FALSE);
                    int _sendAmount = DAT_SentOrRequestedGoodsAmount::instance;
                    ResourceTypeMin1Int _resource
                        = DAT_RequestedGoodsByWhoArray::instance[0] + Game::Resources::RTM_WOOD;
                    ResourceTypeInt _resourceType = _resource;
                    if (_resource == Game::Resources::RTM_WHEAT) {
                        _resourceType = DAT_RequestedGoodsByWhoArray::instance[0];
                    }
                    if (_resource == Game::Resources::RTM_FLOUR) {
                        /*
                          gold
                         */
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .currentResources[0xf]
                            < DAT_SentOrRequestedGoodsAmount::instance) {}
                    } else {
                        _space = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getResourceSpace,
                            DAT_BuildingsState::ptr)(playerID, (int*)((int)(_resourceType)));
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .currentResources[_resourceType]
                            < _sendAmount) {}
                        if (_space < 0) {}
                        if (_space < _sendAmount) {
                            _sendAmount = _space;
                        }
                    }
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = playerID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = _resource;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = _sendAmount;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam4
                        = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_SEND_PLAYER_TO_PLAYER_REQUEST);
                    MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                }
            }
            DAT_SentOrRequestedGoodsAmount::instance = DAT_SentOrRequestedGoodsAmount::instance + 500;
        }

    }
}
}
