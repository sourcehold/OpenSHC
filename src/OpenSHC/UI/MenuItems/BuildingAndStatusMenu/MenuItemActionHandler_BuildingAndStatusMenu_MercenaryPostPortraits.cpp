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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ClickedMercUnitType.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/TIME_ClickedMercUnitTypeMoment.hpp"
#include "OpenSHC/Globals/TIME_MercPostAudio.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::ResourceLackSFX;
        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004674C0
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_MercenaryPostPortraits(int param_1, ...)
        {
            DWORD DVar1;
            DWORD DVar2;
            bool bVar5;
            int iVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::GetUnitRecruitPermission)(param_1);
            if (iVar3 == 1) {
                iVar3 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    (OpenSHC::Map::Units::UnitType)param_1,
                    (undefined4)((int)(DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .mercenaryPost.id)),
                    (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID), 1);
                if (iVar3 != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = param_1;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_RECRUIT_UNIT);
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::DisableMercPostPortraits)();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_BUTTON_CLICK_01);
                    DWORD _now = timeGetTime();
                    if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .count_2
                                + DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .armySize
                            < (DAT_GameState::instance.mapAndTime.armySizeLimit * 9) / 10)
                        || (_now - TIME_MercPostAudio::instance < 0x7531)) {
                        DVar1 = TIME_ClickedMercUnitTypeMoment::instance;
                        DVar2 = TIME_MercPostAudio::instance;
                        if (param_1 != DAT_ClickedMercUnitType::instance)
                            goto LAB_004675b5;
                    } else {
                        param_1 = DAT_ClickedMercUnitType::instance;
                        DVar1 = _now;
                        DVar2 = _now;
                        if (DAT_GameCore::instance.genieVoiceActive != FALSE) {
                            /*
                              "Your army is approaching its maximum size"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                                "Genie_27.wav");
                            param_1 = DAT_ClickedMercUnitType::instance;
                        }
                    }
                    TIME_MercPostAudio::instance = DVar2;
                    TIME_ClickedMercUnitTypeMoment::instance = DVar1;
                    if (_now - TIME_ClickedMercUnitTypeMoment::instance < 0x1f41) {}
                LAB_004675b5:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        (char const*)((int)DAT_UIButtonDefinedData::instance.ButtonGmDataArray + param_1 * 0x20
                            + 0x3f38));
                    TIME_ClickedMercUnitTypeMoment::instance = _now;
                    DAT_ClickedMercUnitType::instance = param_1;
                }
                if (DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 1) {
                LAB_0046764f:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_GOLD);
                }
                bVar5 = DAT_UnitsState::instance.euroUnitAcquisitionFailReason == 3;
            } else {
                int iVar4 = DAT_TroopDefinedData::instance.field279_0x210[param_1];
                if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
                    && (DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0)) {
                    iVar4 = 0;
                }
                if (iVar3 == 3) {
                    if (DAT_GameCore::instance.genieVoiceActive == FALSE) {}
                    /*
                      "Your army is at its maximum size"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFXFile, DAT_SFXState::ptr)(
                        "Genie_26.wav");
                }
                if (iVar3 == 4)
                    goto LAB_004675eb;
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[0xf]
                    < iVar4)
                    goto LAB_0046764f;
                bVar5 = iVar3 == 0;
            }
            if (!bVar5) {}
        LAB_004675eb:
            /*
              "Recruits needed sire"
             */
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("other_warning5.wav");
        }

    }
}
}
