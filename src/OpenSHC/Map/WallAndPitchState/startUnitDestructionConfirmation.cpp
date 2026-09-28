#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500CF0
    void WallAndPitchState::startUnitDestructionConfirmation(int unitID)
    {
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
            this->id = unitID;
            this->state = 2;
            this->countdown = 400;
            this->uid = DAT_UnitsState::instance.units[unitID].uid;
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }
    }

}
}
