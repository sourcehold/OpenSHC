#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x00466E20
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_EngineerAndMonkPortraits(
            int param_1, ...)
        {
            DWORD DVar2;
            bool bVar3;
            bool bVar4;
            char* wav_filename;
            if ((DAT_EnoughGoldForRequestedUnit::instance == FALSE)
                || (DAT_GameState::instance.mapAndTime.armySizeLimit
                    <= DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .count_2
                        + DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .armySize)) {}
            int iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                (OpenSHC::Map::Units::UnitType)param_1,
                (undefined4)((
                    int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .engineersGuild.id)),
                (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID), 1);
            if (iVar1 != 0) {
                DAT_GameSynchronyState::instance.DAT_GameCommandParam1
                    = DAT_BuildingsState::instance.menuSelectedBuildingID;
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECRUIT_UNIT);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_BUTTON_CLICK_01);
                if ((param_1 == INT_00df3368::instance)
                    && (DVar2 = timeGetTime(), DVar2 - DWORD_00df3364::instance < 0x1f41)) {}
                if (param_1 == 0x1d) {
                    /*
                       "Okay, sir"
                     */
                    wav_filename = "ladder_s1.wav";
                } else {
                    /*
                      "Your grace"
                     */
                    wav_filename = "engineer_s2.wav";
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(wav_filename);
                INT_00df3368::instance = param_1;
                DWORD_00df3364::instance = timeGetTime();
            }
            if (param_1 == 0x1d) {
                iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[0xf];
                bVar4 = (iVar1 < 4);
                bVar3 = iVar1 + -4 < 0;
            } else if (param_1 == 0x1e) {
                iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[0xf];
                bVar4 = (iVar1 < 0x1e);
                bVar3 = iVar1 + -0x1e < 0;
            } else {
                if (param_1 != 0x25)
                    goto LAB_00466f49;
                iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .currentResources[0xf];
                bVar4 = (iVar1 < 10);
                bVar3 = iVar1 + -10 < 0;
            }
            if (bVar4 != bVar3) {
                /*
                  "You do not have enough gold to train this unit"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "units_warning3.wav");
            }
        LAB_00466f49:
            /*
              "Recruits needed sire"
             */
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("other_warning5.wav");
        }

    }
}
}
