#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040BC40
        void BuildingsState::setupNextCandidateLocationComputeOffsets2(int size, int nudge, int try_, int offset)
        {
            // Offset of the try_-th tile around a building of the given size
            switch (size) {
            case 1:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field179_0x7e8c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field179_0x7e8c[try_].y;
                break;
            case 2:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field180_0x7ecc[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field180_0x7ecc[try_].y;
                break;
            case 3:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field181_0x7f2c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field181_0x7f2c[try_].y;
                break;
            case 4:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field182_0x7fac[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field182_0x7fac[try_].y;
                break;
            case 5:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field183_0x804c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field183_0x804c[try_].y;
                break;
            case 6:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field184_0x810c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field184_0x810c[try_].y;
                break;
            case 7:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field185_0x81ec[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field185_0x81ec[try_].y;
                break;
            case 8:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field186_0x82ec[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field186_0x82ec[try_].y;
                break;
            case 9:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field187_0x840c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field187_0x840c[try_].y;
                break;
            case 10:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field188_0x854c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field188_0x854c[try_].y;
                break;
            case 11:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field189_0x86ac[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field189_0x86ac[try_].y;
                break;
            case 12:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field190_0x882c[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field190_0x882c[try_].y;
                break;
            case 13:
                this->DAT_TempXOffset = DAT_BuildingDefinedData::instance.field191_0x89cc[try_].x;
                this->DAT_TempYOffset = DAT_BuildingDefinedData::instance.field191_0x89cc[try_].y;
                break;
            }

            // Move the tile away from the side of the building it belongs to
            switch (try_ / size * 2) {
            case 0:
                this->DAT_TempYOffset -= offset;
                break;
            case 4:
                this->DAT_TempYOffset += offset;
                break;
            case 2:
                this->DAT_TempXOffset += offset;
                break;
            case 6:
                this->DAT_TempXOffset -= offset;
                break;
            }
            if (this->DAT_TempXOffset < size && this->DAT_TempYOffset < size) {
                if (this->DAT_TempXOffset <= -1) {
                    this->DAT_TempXOffset = this->DAT_TempXOffset - nudge + 1;
                    return;
                }
                if (this->DAT_TempYOffset <= -1) {
                    this->DAT_TempYOffset = this->DAT_TempYOffset - nudge + 1;
                }
            }
        }

    }
}
}
