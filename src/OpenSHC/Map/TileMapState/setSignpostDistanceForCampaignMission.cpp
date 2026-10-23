#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500BB0
    void TileMapState::setSignpostDistanceForCampaignMission()
    {
        DAT_GameState::instance.mapAndTime.unk_signpostDistance = 30;
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
            if (DAT_GameCore::instance.missionNumber1to20 <= 2) {
                DAT_GameState::instance.mapAndTime.unk_signpostDistance = 0;
                return;
            }
            if (DAT_GameCore::instance.missionNumber1to20 <= 4) {
                DAT_GameState::instance.mapAndTime.unk_signpostDistance = 15;
                return;
            }
            if (DAT_GameCore::instance.missionNumber1to20 == 6) {
                DAT_GameState::instance.mapAndTime.unk_signpostDistance = 37;
            }
            return;
        }

        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                && (int)DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 >= 2)) {
            DAT_GameState::instance.mapAndTime.unk_signpostDistance = 7;
        }
    }

}
}
