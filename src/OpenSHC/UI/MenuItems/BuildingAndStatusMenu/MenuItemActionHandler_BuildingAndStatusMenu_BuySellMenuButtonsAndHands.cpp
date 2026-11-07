#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOL_CurrentMenuClickState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            using Game::Resources::ResourceType;

            // FUNCTION: STRONGHOLDCRUSADER 0x00467040
            void MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int param_1, ...)
            {
                // Buttons 2 and 3 step through the goods (partial pitch shows as pitch), 0 buys and 1 sells.
                if (param_1 == 2) {
                    int resource = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getPreviousGoodsFilteringUnallowed,
                        DAT_GameState::ptr)((ResourceType)DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                    if (resource == Game::Resources::RT_PARTIALPITCH) {
                        resource = Game::Resources::RT_PITCH;
                    }
                    MACRO_CALL(
                        BuildingAndStatusMenu_Func::MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods)(
                        resource);
                    return;
                }
                if (param_1 == 3) {
                    int resource = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getNextGoodFilteringUnallowed,
                        DAT_GameState::ptr)((ResourceType)DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                    if (resource == Game::Resources::RT_PARTIALPITCH) {
                        resource = Game::Resources::RT_PITCH;
                    }
                    MACRO_CALL(
                        BuildingAndStatusMenu_Func::MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods)(
                        resource);
                    return;
                }
                BOOL_CurrentMenuClickState::instance = FALSE;
                if (param_1 == 0) {
                    int const price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBatchBuyPrice,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[Game::Resources::RT_GOLD]
                        < price) {
                        MACRO_CALL(Actions_Func::SetStorageMarketFailState)(1,
                            (ResourceType)DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType);
                        // "space_warning8.wav": not enough gold
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_space_warning8_wav_005a5964);
                        return;
                    }
                    int const space = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getResourceSpace,
                        DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (ResourceType)DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                    if (space == -1) {
                        MACRO_CALL(Actions_Func::SetStorageMarketFailState)(3,
                            (ResourceType)DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType);
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 6) {
                            // "space_warning2.wav": no stockpile built
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning2_wav_005a5950);
                        }
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 5) {
                            // "space_warning1.wav": no granary built
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning1_wav_005a593c);
                        }
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 7) {
                            // "space_warning3.wav": no armory built
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning3_wav_005a5928);
                        }
                        return;
                    }
                    if (space < 5) {
                        MACRO_CALL(Actions_Func::SetStorageMarketFailState)(4,
                            (ResourceType)DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType);
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 9) {
                            // "space_warning5.wav": no space in the stockpile
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning5_wav_005a50b0);
                        }
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 8) {
                            // "space_warning4.wav": no space in the granary
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning4_wav_005a5914);
                        }
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .storageMarketFailState
                            == 10) {
                            // "space_warning6.wav": no space in the armory
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_space_warning6_wav_005a5900);
                        }
                        return;
                    }
                } else if (param_1 == 1) {
                    ResourceType const resource
                        = (ResourceType)DAT_GameState::instance
                              .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .marketSelectedResourceType;
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[resource]
                        <= 0) {
                        MACRO_CALL(Actions_Func::SetStorageMarketFailState)(2, resource);
                        // "space_warning7.wav": not enough goods
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_space_warning7_wav_005a58ec);
                        return;
                    }
                }
                if (param_1 == 0 || param_1 == 1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        Audio::SFX::SEID_DRAWBRIDGE_CONTROL);
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .storageMarketFailState = 0;
                }
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .marketSelectedResourceType;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_BUY_OR_SELL);
            }

        }
    }
}
}
