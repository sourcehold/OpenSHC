#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045AD10
    void Version::InitPopularityAndRecruitableDefaults()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            DAT_GameState::instance.playerDataArray[playerID].someCount44
                = (short)DAT_GameState::instance.playerDataArray[playerID].storedPopularityPercent;
        }
        for (int i = 0; i < 7; ++i) {
            DAT_GameState::instance.mapAndTime.euroRecruitable[i] = 1;
            DAT_GameState::instance.mapAndTime.mercRecruitable[i] = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4 = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c = 1;
    }

}
}
