#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x00465700
    void Commands::QueueChangeTaxes()
    {
        int iVar1;
        BOOLEnum BVar2;
        DWORD DVar3;
        iVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .taxesSliderUI;
        if (iVar1
            != DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .taxesSetting2) {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                BVar2 = MACRO_CALL(OpenSHC::Game_Func::Tutorial_IsActionAllowed)(4, iVar1);
                if (BVar2 == FALSE) {
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .taxesSliderUI
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .taxesSetting2;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(0xd,
                    (BuildingType)((int)(DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSliderUI)));
            }
            iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DVar3 = timeGetTime();
            DAT_GameState::instance.playerDataArray[iVar1].timeTaxesOrRationsChange = DVar3;
            DAT_GameState::instance.playerDataArray[iVar1].taxesSetting2
                = DAT_GameState::instance.playerDataArray[iVar1].taxesSliderUI;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                = DAT_GameState::instance.playerDataArray[iVar1].taxesSliderUI;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_CHANGE_TAXES);
        }
    }

}
}
