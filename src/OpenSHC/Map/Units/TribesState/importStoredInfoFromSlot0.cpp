#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522DD0
        void TribesState::importStoredInfoFromSlot0(undefined4 param_1, int tribeID)
        {
            if (this->tribeCopiedToSlot0) {
                this->tribes[tribeID].field166_0x2be = this->tribes[0].field166_0x2be;
                this->tribes[tribeID].someUnitID = this->tribes[0].someUnitID;
                this->tribes[tribeID].someUnitUID = this->tribes[0].someUnitUID;
                this->tribes[tribeID].someTile = this->tribes[0].someTile;
                this->tribes[tribeID].someTile2 = this->tribes[0].someTile2;
                this->tribes[tribeID].currentRallyPointIndex = this->tribes[0].currentRallyPointIndex;
                this->tribes[tribeID].rallyPointCount = this->tribes[0].rallyPointCount;
                this->tribes[tribeID].isRallyingUnk = this->tribes[0].isRallyingUnk;
                this->tribes[tribeID].unitStance = this->tribes[0].unitStance;
                /*
                  The original unrolls the inner loop over the nine rally points and keeps
                  the outer one over the two coordinates, stepping its cursor by one short.
                  The import wrote the nine stores out as ten, one past the array.
                 */
                for (int _coordinate = 0; _coordinate < 2; _coordinate = _coordinate + 1) {
                    for (int _point = 0; _point < 9; _point = _point + 1) {
                        this->tribes[tribeID].rallyPointArray[_point][_coordinate]
                            = this->tribes[0].rallyPointArray[_point][_coordinate];
                    }
                }
            }
            this->tribes[tribeID].unitStance = this->tribes[0].unitStance;
        }

    }
}
}
