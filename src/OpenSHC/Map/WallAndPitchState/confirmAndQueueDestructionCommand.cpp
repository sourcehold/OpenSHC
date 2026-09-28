#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x005118C0
    void WallAndPitchState::confirmAndQueueDestructionCommand()
    {
        if (this->countdown != 0) {
            this->countdown += 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::WallAndPitchState_Func::updateDestructionConfirmationCountdown, this)();
            if (this->countdown != 0) {
                switch (this->state) {
                case 0:
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = this->id;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 100;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                        = DAT_BuildingsState::instance.buildings[this->id].uid;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_DESTROY_BUILDING);
                    break;
                case 1:
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = this->id;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((GameCommandType)75);
                    break;
                case 2:
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 2;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = this->id;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((GameCommandType)75);
                    break;
                case 3:
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = this->counter;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = this->flag;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 3;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = this->index;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((GameCommandType)76);
                    break;
                case 4:
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = this->counter;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = this->flag;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = 4;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = this->index;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)((GameCommandType)76);
                    break;
                }
            }
        }
        this->countdown = 0;
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
    }

}
}
