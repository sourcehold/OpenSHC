#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00df3364.hpp"
#include "OpenSHC/Globals/INT_00df3368.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466E20
            void MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits(int unitType, ...)
            {
                if (!DAT_EnoughGoldForRequestedUnit::instance) {
                    return;
                }
                // armySize first: the other order swaps the two loads.
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .armySize
                        + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .count_2
                    >= DAT_GameState::instance.mapAndTime.armySizeLimit) {
                    return;
                }
                // The last argument (TRUE) only checks that a recruit is free; it converts nobody.
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                        (Map::Units::UnitType)unitType,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .buildingEntryInfos[Game::Player::Enums::BEIE_ENGINEERSGUILD]
                            .id,
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, TRUE)) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                        = DAT_BuildingsState::instance.menuSelectedBuildingID;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = unitType;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_RECRUIT_UNIT);
                    MACRO_CALL(Helpers_Func::CheckIfEnoughGoldForLadderman)();
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        Audio::SFX::SEID_BUTTON_CLICK_01);
                    // The unit answers when it differs from the last one clicked, or 8 seconds after that.
                    if (unitType != INT_00df3368::instance || timeGetTime() - DWORD_00df3364::instance > 8000) {
                        // One call per voice: choosing the file first loads it into a register instead.
                        if (unitType == Map::Units::UT_E_LADDER) {
                            // "ladder_s1.wav": "Okay, sir"
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_ladder_s1_wav_005a4bb4);
                        } else {
                            // "engineer_s2.wav": "Your grace"
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_engineer_s2_wav_005a4a94);
                        }
                        INT_00df3368::instance = unitType;
                        DWORD_00df3364::instance = timeGetTime();
                    }
                    return;
                }
                // Laddermen cost 4 gold, engineers 30, monks 10.
                // One arm per unit: a single condition would go on to test the other units.
                if (unitType == Map::Units::UT_E_LADDER) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[Game::Resources::RT_GOLD]
                        < 4) {
                        // "units_warning3.wav": "You do not have enough gold to train this unit"
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_units_warning3_wav_005a58d8);
                        return;
                    }
                } else if (unitType == Map::Units::UT_E_ENGINEER) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[Game::Resources::RT_GOLD]
                        < 30) {
                        // "units_warning3.wav": "You do not have enough gold to train this unit"
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_units_warning3_wav_005a58d8);
                        return;
                    }
                } else if (unitType == Map::Units::UT_E_MONK) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[Game::Resources::RT_GOLD]
                        < 10) {
                        // "units_warning3.wav": "You do not have enough gold to train this unit"
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_units_warning3_wav_005a58d8);
                        return;
                    }
                }
                // "other_warning5.wav": "Recruits needed sire"
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning5_wav_005a58c4);
            }

        }
    }
}
}
