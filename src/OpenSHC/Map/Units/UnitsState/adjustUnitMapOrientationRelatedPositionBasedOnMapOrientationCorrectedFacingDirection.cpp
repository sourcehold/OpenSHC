#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005340F0
        void UnitsState::adjustUnitMapOrientationRelatedPositionBasedOnMapOrientationCorrectedFacingDirection(
            int unitID)
        {
            this->units[unitID].orientationRelatedPositionX = this->units[unitID].orientationRelatedPositionX
                + (short)DAT_UnitPropertiesDefinedData::instance
                      .UnitOrientationRelatedOffset[this->units[unitID].facingDirectionMapOrientationCorrected][0];
            this->units[unitID].orientationRelatedPositionY = this->units[unitID].orientationRelatedPositionY
                + (short)DAT_UnitPropertiesDefinedData::instance
                      .UnitOrientationRelatedOffset[this->units[unitID].facingDirectionMapOrientationCorrected][1];
        }

    }
}
}
