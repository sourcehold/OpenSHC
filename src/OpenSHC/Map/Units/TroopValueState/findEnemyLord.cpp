#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A220
        int TroopValueState::findEnemyLord(int param_1)
        {
            int iVar1;
            int* piVar2;
            iVar1 = 0;
            if (this->attackInfo.lord3 < 1) {
                return 0;
            }
            piVar2 = &this->attackInfo.lordValuesArray[0].unitID;
            do {
                if (*piVar2 == 0) {
                    this->y = (int)DAT_ViewportRenderState::instance
                                  .tileTranslationMatrix_YComponent[this->attackInfo.lordValuesArray[iVar1].tile2];
                    this->x = this->attackInfo.lordValuesArray[iVar1].tile2
                        - DAT_ViewportRenderState::instance.translationMatrix[this->y].addXgetTile;
                    this->tile = this->attackInfo.lordValuesArray[iVar1].tile;
                    this->attackInfo.lordValuesArray[iVar1].unitID = param_1;
                    return this->attackInfo.lordValuesArray[iVar1].tile2;
                }
                iVar1 = iVar1 + 1;
                piVar2 = piVar2 + 4;
            } while (iVar1 < this->attackInfo.lord3);
            this->y = (int)DAT_ViewportRenderState::instance
                          .tileTranslationMatrix_YComponent[this->attackInfo.lordValuesArray[0].tile2];
            this->x = this->attackInfo.lordValuesArray[0].tile2
                - DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_ViewportRenderState::instance
                              .tileTranslationMatrix_YComponent[this->attackInfo.lordValuesArray[0].tile2]]
                      .addXgetTile;
            this->tile = this->attackInfo.lordValuesArray[0].tile;
            return this->attackInfo.lordValuesArray[0].tile2;
        }

    }
}
}
