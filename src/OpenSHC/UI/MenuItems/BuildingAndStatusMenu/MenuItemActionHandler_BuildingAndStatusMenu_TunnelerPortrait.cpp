#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DWORD_00df336c.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466F60
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_TunnelerPortrait(int param_1, ...)
        {
            if ((DAT_EnoughGoldForRequestedUnit::instance != FALSE)
                && (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .count_2
                        + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .armySize
                    < DAT_GameState::instance.mapAndTime.armySizeLimit)) {
                int iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit,
                    DAT_UnitsState::ptr)((OpenSHC::Map::Units::UnitType)param_1,
                    (undefined4)((int)(DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .tunnelersGuild.id)),
                    (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID), 1);
                if (iVar1 == 0) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[0xf]
                        < 0x1e) {
                        /*
                          "You do not have enough gold to train this unit"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "units_warning3.wav");
                    }
                    /*
                      "Recruits needed sire"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "other_warning5.wav");
                } else {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECRUIT_UNIT);
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForTunneler)();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_BUTTON_CLICK_01);
                    DWORD DVar2 = timeGetTime();
                    if (8000 < DVar2 - DWORD_00df336c::instance) {
                        /*
                           "Yeeeess?"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "tunnel_s2.wav");
                        DWORD_00df336c::instance = timeGetTime();
                    }
                }
            }
        }

    }
}
}
