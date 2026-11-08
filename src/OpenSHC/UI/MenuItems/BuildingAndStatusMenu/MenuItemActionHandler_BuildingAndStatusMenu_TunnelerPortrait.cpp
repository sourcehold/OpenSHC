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

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00df336c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466F60
            void MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait(int unitType, ...)
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
                // The last argument (1) only checks that a recruit is free; it converts nobody.
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                        (Map::Units::UnitType)unitType,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .buildingEntryInfos[Game::Player::Enums::BEIE_TUNNELERSGUILD]
                            .id,
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, 1)
                    != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = unitType;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        Commands::GCT_RECRUIT_UNIT);
                    MACRO_CALL(Helpers_Func::CheckIfEnoughGoldForTunneler)();
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        Audio::SFX::SEID_BUTTON_CLICK_01);
                    // The tunneler answers at most every eight seconds.
                    if (timeGetTime() - DWORD_00df336c::instance > 8000) {
                        // "tunnel_s2.wav": "Yeeeess?"
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_tunnel_s2_wav_005a4ab4);
                        DWORD_00df336c::instance = timeGetTime();
                    }
                    return;
                }
                // A tunneler costs 30 gold (CheckIfEnoughGoldForTunneler uses the same number).
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[Game::Resources::RT_GOLD]
                    < 30) {
                    // "units_warning3.wav": "You do not have enough gold to train this unit"
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        s_units_warning3_wav_005a58d8);
                    return;
                }
                // "other_warning5.wav": "Recruits needed sire"
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning5_wav_005a58c4);
            }

        }
    }
}
}
