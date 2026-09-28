#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500CB0
    void WallAndPitchState::startEntityDestructionConfirmation(int entityID)
    {
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
            this->id = entityID;
            this->state = 1;
            this->countdown = 400;
            this->uid = DAT_EntityState::instance.entityArray[entityID].uid;
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }
        return;
    }

}
}
