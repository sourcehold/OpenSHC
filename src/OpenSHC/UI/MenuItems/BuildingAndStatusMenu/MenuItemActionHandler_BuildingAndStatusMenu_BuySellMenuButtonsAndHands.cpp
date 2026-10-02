#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Actions.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildingAndStatusMenu.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOL_CurrentMenuClickState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00467040
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(
            int param_1, ...)
        {
            int _buyingPrice;
            int _player;
            if (param_1 == 2) {
                _buyingPrice
                    = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getPreviousGoodsFilteringUnallowed,
                        DAT_GameState::ptr)((OpenSHC::Game::Resources::ResourceType)DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                if (_buyingPrice == 8) {
                    _buyingPrice = 7;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::BuildingAndStatusMenu_Func::
                        MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods)(_buyingPrice);
            }
            if (param_1 == 3) {
                _buyingPrice = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getNextGoodFilteringUnallowed,
                    DAT_GameState::ptr)((OpenSHC::Game::Resources::ResourceType)DAT_GameState::instance
                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketSelectedResourceType);
                if (_buyingPrice == 8) {
                    _buyingPrice = 7;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::BuildingAndStatusMenu_Func::
                        MenuItemActionHandler_BuildingAndStatusMenu_SelectBuySellGoods)(_buyingPrice);
            }
            BOOL_CurrentMenuClickState::instance = FALSE;
            if (param_1 == 0) {
                /*
                  Buying
                 */
                _buyingPrice = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBatchBuyPrice,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType));
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf]
                    < _buyingPrice) {
                    MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(1,
                        (ResourceType)((int)(DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType)));
                    /*
                      "Not enough gold"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "space_warning8.wav");
                }
                int _space = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getResourceSpace,
                    DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (int*)((int)(DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType)));
                if (_space == -1) {
                    MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(3,
                        (ResourceType)((int)(DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType)));
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        == 6) {
                        /*
                          "No stockpile built"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "space_warning2.wav");
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        == 5) {
                        /*
                          "No Granary built"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "space_warning1.wav");
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        != 7) {}
                    /*
                      "No Armory built"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "space_warning3.wav");
                }
                if (_space < 5) {
                    MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(4,
                        (ResourceType)((int)(DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType)));
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        == 9) {
                        /*
                          "No space in the stockpile"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "space_warning5.wav");
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        == 8) {
                        /*
                          "No space in the granary"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "space_warning4.wav");
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState
                        != 10) {}
                    /*
                      "No space in the armory"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "space_warning6.wav");
                }
            } else {
                _player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                /*
                  Selling
                 */
                if (param_1 != 1)
                    goto LAB_004672c0;
                ResourceType _resource = (OpenSHC::Game::Resources::ResourceType)DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .marketSelectedResourceType;
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[_resource]
                    < 1) {
                    MACRO_CALL(OpenSHC::UI::Actions_Func::SetStorageMarketFailState)(2, _resource);
                    /*
                      "Not enough goods"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "space_warning7.wav");
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                OpenSHC::Audio::SFX::SEID_DRAWBRIDGE_CONTROL);
            _player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .storageMarketFailState = 0;
        LAB_004672c0:
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                = DAT_GameState::instance.playerDataArray[_player].marketSelectedResourceType;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_BUY_OR_SELL);
        }

    }
}
}
