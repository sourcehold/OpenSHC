#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500F40
    void WallAndPitchState::updateDestructionConfirmationCountdown()
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
            this->countdown = 0;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            this->countdown = 0;
            return;
        }
        if (this->countdown == 0) {
            return;
        }
        this->countdown -= 1;
        switch (this->state) {
        case 0:
            if (DAT_BuildingsState::instance.buildings[this->id].uid != this->uid) {
                this->countdown = 0;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            if (DAT_BuildingsState::instance.buildings[this->id].currentHealth
                != DAT_BuildingsState::instance.buildings[this->id].maxHealth) {
                this->countdown = 0;
            }
            for (int i = 0; i != 25; i++) {
                if (DAT_BuildingsState::instance.buildings[this->id].resources[i] != 0) {
                    this->countdown = 0;
                }
            }
            break;
        case 2:
            if (DAT_UnitsState::instance.units[this->id].uid != this->uid) {
                this->countdown = 0;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            if (DAT_UnitsState::instance.units[this->id]
                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                != 0) {
                this->countdown = 0;
            }
            if (DAT_UnitsState::instance.units[this->id].health != DAT_UnitsState::instance.units[this->id].maxHealth) {
                this->countdown = 0;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            break;
        case 3:
            if (this->index == 0) {
                this->countdown = 0;
            }
            for (int i = 0; i < this->index; i++) {
                int _tile = this->wallPlacementInfoArray[i].tile_OR_pitchID;
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x100) == 0) {
                    this->countdown = 0;
                }
                if (DAT_TileMapState::instance.DamageLayer[_tile] != 0) {
                    this->countdown = 0;
                }
            }
            break;
        case 4:
            for (int i = 0; i < this->index; i++) {
                if (this->wallPlacementInfoArray[i].tile_OR_pitchID == 0
                    || (DAT_TileMapState::instance.LogicLayer[DAT_TileMapState::instance
                                .pitchDitches[this->wallPlacementInfoArray[i].tile_OR_pitchID]
                                .tile]
                           & 8)
                        == 0) {
                    this->countdown = 0;
                }
            }
        }
        if (this->countdown == 0) {
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }
    }

}
}
