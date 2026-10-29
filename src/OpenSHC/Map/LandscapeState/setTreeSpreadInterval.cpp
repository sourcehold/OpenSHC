#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // Signed compares (jg) of DAT_TotalOrganisms; the last step is treeSpreadInterval = (count <= 1800) (setle).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2CC0
    void LandscapeState::setTreeSpreadInterval()
    {
        int const count = this->DAT_TotalOrganisms;
        if (count <= 10) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 20;
            return;
        }
        if (count <= 100) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 15;
            return;
        }
        if (count <= 200) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 10;
            return;
        }
        if (count <= 300) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 9;
            return;
        }
        if (count <= 400) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 8;
            return;
        }
        if (count <= 600) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 7;
            return;
        }
        if (count <= 800) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 6;
            return;
        }
        if (count <= 1000) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 5;
            return;
        }
        if (count <= 1200) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 4;
            return;
        }
        if (count <= 1400) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 3;
            return;
        }
        if (count <= 1600) {
            DAT_GameState::instance.mapAndTime.treeSpreadInterval = 2;
            return;
        }
        DAT_GameState::instance.mapAndTime.treeSpreadInterval = count <= 1800;
    }

}
}
