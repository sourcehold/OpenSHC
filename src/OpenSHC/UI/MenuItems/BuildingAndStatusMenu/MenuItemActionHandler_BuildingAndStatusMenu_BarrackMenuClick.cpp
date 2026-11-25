#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/EuroRecruitableState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df3374.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WavEuropeanUnitRecruitment.hpp"
#include "OpenSHC/Globals/DWORD_00df3370.hpp"
#include "OpenSHC/Globals/DWORD_00df3378.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Map::Units::EuroRecruitableState;

        // FUNCTION: STRONGHOLDCRUSADER 0x004672F0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_BarrackMenuClick(int unitType, ...)
        {
            EuroRecruitableState const permission
                = MACRO_CALL(OpenSHC::UI::Helpers_Func::IsEuroUnitRecruitableUnk)(unitType);
            if (permission == OpenSHC::Map::Units::ERS_CAN_RECRUITUnk) {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit, DAT_UnitsState::ptr)(unitType,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                            .id,
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, 1)
                    != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = unitType;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECRUIT_UNIT);
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetEnoughGoldForRequestedUnitToTrueUnk)();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_BUTTON_CLICK_01);
                    DWORD const now = timeGetTime();
                    // the unit's own voice line, unless the same unit was clicked less than 8 seconds ago; near the
                    // army limit the genie speaks instead, at most every 30 seconds
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .armySize
                                + DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .count_2
                            >= DAT_GameState::instance.mapAndTime.armySizeLimit * 9 / 10
                        && now - DWORD_00df3378::instance > 30000) {
                        if (DAT_GameCore::instance.genieVoiceActive) {
                            // "Genie_27.wav": "Your army is approaching its maximum size"
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                s_Genie_27_wav_005a599c);
                        }
                        unitType = DAT_00df3374::instance;
                        DWORD_00df3370::instance = now;
                        DWORD_00df3378::instance = now;
                    }
                    if (unitType == DAT_00df3374::instance && now - DWORD_00df3370::instance <= 8000) {
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        DAT_WavEuropeanUnitRecruitment::instance[unitType - OpenSHC::Map::Units::UT_E_ARCHER]);
                    DAT_00df3374::instance = unitType;
                    DWORD_00df3370::instance = now;
                    return;
                }
            } else {
                int cost = DAT_TroopDefinedData::instance.BarracksUnitCost[unitType - OpenSHC::Map::Units::UT_E_ARCHER];
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                    && DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0) {
                    cost = 0;
                }
                if (permission == OpenSHC::Map::Units::ERS_UNABLE_BECAUSE_MAX_ARMY) {
                    if (DAT_GameCore::instance.genieVoiceActive) {
                        // "Genie_26.wav": "Your army is at its maximum size"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                            (char*)s_Genie_26_wav_005a598c);
                    }
                    return;
                }
                if (permission == OpenSHC::Map::Units::ERS_UNABLE_MISSING_PEASANTS) {
                    // "other_warning5.wav": "Recruits needed sire"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_other_warning5_wav_005a58c4);
                    return;
                }
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    < cost) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_GOLD);
                    return;
                }
                if (permission == OpenSHC::Map::Units::ERS_CAN_NOT_RECRUIT) {
                    // "other_warning6.wav": "Weapons needed sire"
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_other_warning6_wav_005a5978);
                }
                return;
            }
            // the recruit failed: 1 for the gold, 2 for the weapons, 3 for the peasants
            if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_GOLD);
                return;
            }
            if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 2) {
                // "other_warning6.wav": "Weapons needed sire"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning6_wav_005a5978);
                return;
            }
            if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 3) {
                // "other_warning5.wav": "Recruits needed sire"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning5_wav_005a58c4);
            }
        }

    }
}
}
