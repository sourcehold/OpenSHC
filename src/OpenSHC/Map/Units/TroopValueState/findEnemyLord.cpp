#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A220
        int TroopValueState::findEnemyLord(int param_1)
        {
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.lord3) {
                do {
                    if (DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID == 0) {
                        this->y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                      [DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2];
                        this->x = DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[this->y].addXgetTile;
                        this->tile = DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile;
                        DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].unitID = param_1;
                        return DAT_TroopValueState::instance.attackInfo.lordValuesArray[i].tile2;
                    }
                    i++;
                } while (i < DAT_TroopValueState::instance.attackInfo.lord3);
                this->y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                              [DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2];
                this->x = DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2
                    - DAT_ViewportRenderState::instance.translationMatrix[this->y].addXgetTile;
                this->tile = DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile;
                return DAT_TroopValueState::instance.attackInfo.lordValuesArray[0].tile2;
            }
            return 0;
        }

    }
}
}
