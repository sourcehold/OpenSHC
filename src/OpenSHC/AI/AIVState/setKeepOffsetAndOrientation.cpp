#include "../AIVState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004ECF70
    void AIVState::setKeepOffsetAndOrientation(int aivID, int keepX, int keepY)
    {
        // the AIV is 100x100 tiles with the keep at 43/43
        this->aivs[aivID].keepX = keepX;
        this->aivs[aivID].keepY = keepY;
        this->aivs[aivID].keepXOffset = keepX - 43;
        this->aivs[aivID].keepYOffset = keepY - 43;
        // orient the castle towards the map center
        MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
            DAT_DirectionAlgorithmState::ptr)(keepX, keepY, 200, 200);
        // the orientation is one of the 8 compass directions; clearing the low bit snaps a diagonal onto the
        // preceding cardinal direction, so only 0, 2, 4 and 6 remain
        this->aivs[aivID].keepOrientation = DAT_DirectionAlgorithmState::instance.orientation & 0xfffe;
        // east and west are swapped relative to the direction algorithm's numbering
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
