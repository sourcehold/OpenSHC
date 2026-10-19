#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522DD0
        void TribesState::importStoredInfoFromSlot0(undefined4 param_1, int tribeID)
        {
            short (*_ptrStoredRallyPoints)[2];
            int iVar1;
            short (*_ptrRallyPoints)[2];
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
                _ptrRallyPoints = this->tribes[tribeID].rallyPointArray + 1;
                _ptrStoredRallyPoints = this->tribes[0].rallyPointArray + 1;
                iVar1 = 2;
                do {
                    _ptrRallyPoints[-1][0] = _ptrStoredRallyPoints[-1][0];
                    (*_ptrRallyPoints)[0] = (*_ptrStoredRallyPoints)[0];
                    _ptrRallyPoints[1][0] = _ptrStoredRallyPoints[1][0];
                    _ptrRallyPoints[2][0] = _ptrStoredRallyPoints[2][0];
                    _ptrRallyPoints[3][0] = _ptrStoredRallyPoints[3][0];
                    _ptrRallyPoints[4][0] = _ptrStoredRallyPoints[4][0];
                    _ptrRallyPoints[5][0] = _ptrStoredRallyPoints[5][0];
                    _ptrRallyPoints[6][0] = _ptrStoredRallyPoints[6][0];
                    _ptrRallyPoints[7][0] = _ptrStoredRallyPoints[7][0];
                    _ptrRallyPoints[8][0] = _ptrStoredRallyPoints[8][0];
                    _ptrStoredRallyPoints = (short (*)[2])(*_ptrStoredRallyPoints + 1);
                    _ptrRallyPoints = (short (*)[2])(*_ptrRallyPoints + 1);
                    iVar1 = iVar1 + -1;
                } while (iVar1);
            }
            this->tribes[tribeID].unitStance = this->tribes[0].unitStance;
        }

    }
}
}
