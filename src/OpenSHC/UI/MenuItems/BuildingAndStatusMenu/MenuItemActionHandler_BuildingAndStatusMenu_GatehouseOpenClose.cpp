#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;

        // FUNCTION: STRONGHOLDCRUSADER 0x00465480
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_GatehouseOpenClose(int param_1, ...)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                = DAT_BuildingsState::instance.menuSelectedBuildingID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = param_1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].uid;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_OPEN_OR_CLOSE_GATE);
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .openOrCloseGateClick = param_1;
            if (param_1 == 10) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)140);
            }
            if (param_1 == 11) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)142);
            }
        }

    }
}
}
