#include "../AIVState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECF70
    void AIVState::setKeepOffsetAndOrientation(int aivID, int keepX, int keepY)
    {
        // the AIV is 100x100 tiles with the keep at 43/43
        this->aivs[aivID].keepXOffset = keepX - 43;
        this->aivs[aivID].keepY = keepY;
        this->aivs[aivID].keepX = keepX;
        this->aivs[aivID].keepYOffset = keepY - 43;
        // orient the castle towards the map center
        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(keepX, keepY, 200, 200);
        this->aivs[aivID].keepOrientation = DAT_DirectionAlgorithmState::instance.orientation & 0xfffe;
        if (this->aivs[aivID].keepOrientation == 6) {
            this->aivs[aivID].keepOrientation = 2;
            return;
        }
        if (this->aivs[aivID].keepOrientation == 2) {
            this->aivs[aivID].keepOrientation = 6;
        }
    }

}
}
