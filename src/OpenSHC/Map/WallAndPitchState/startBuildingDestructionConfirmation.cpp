#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500C20
    void WallAndPitchState::startBuildingDestructionConfirmation(int buildingID)
    {
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
            && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT)) {
            if ((int)(short)DAT_BuildingsState::instance.buildings[buildingID].buildingType - 0x28U <= 4) {
                this->countdown = 0;
                return;
            }
            this->state = 0;
            this->countdown = 400;
            this->id = buildingID;
            this->uid = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }
        return;
    }

}
}
