#include "OpenSHC/Map/Units/TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B680
        void TroopValueState::clearAIInfoLayerOutsideStartZone()
        {
            // fixme: this function doesn't use this-> (would be not 100% matching!)
            int area = DAT_TroopValueState::instance.attackInfo.startCon;
            for (int iVar2 = 0; iVar2 < 80400; iVar2++) {
                if ((DAT_TileMapState::instance.AIInfoLayer[iVar2] != '\0')
                    && ((short)DAT_TileMapState::instance.PathConnectionLayer[iVar2] != area)) {
                    DAT_TileMapState::instance.AIInfoLayer[iVar2] = '\0';
                }
            }
        }

    }
}
}
