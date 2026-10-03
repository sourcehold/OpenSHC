#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Game {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00458EC0
    void GameStateStructures::updateFearFactorProductivity()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= -5) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 150;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= -4) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 140;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= -3) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 130;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= -2) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 120;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= -1) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 110;
            } else if (DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel == 0) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 100;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 1) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 90;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 2) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 80;
            } else if ((int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 3) {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk = 70;
            } else {
                DAT_GameState::instance.playerDataArray[playerID].fearFactorProductivityUnk
                    = (int)DAT_GameState::instance.playerDataArray[playerID].fearFactorLevel <= 4 ? 60 : 50;
            }
        }
    }
}
}
