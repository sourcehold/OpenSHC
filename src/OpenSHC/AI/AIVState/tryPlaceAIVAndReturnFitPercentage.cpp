#include "../AIVState.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F14F0
    int AIVState::tryPlaceAIVAndReturnFitPercentage(int aivID, int castleID)
    {
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->isHandled), 0, this->isHandled);
        if (!MACRO_CALL_MEMBER(IO::FilePackager_Func::unpackAIVFile, FilePackagerObj::ptr)(
                DAT_AIVDefinedData::instance.AIVSectionAddressArray,
                DAT_AIVDefinedData::instance.AIVFileNames[this->aivs[aivID].aiType - 2][castleID])) {
            return -3;
        }
        MACRO_CALL_MEMBER(AIVState_Func::rotateAIV, this)(this->aivs[aivID].keepOrientation);
        int const fit = MACRO_CALL_MEMBER(AIVState_Func::computeAIVPlacementFit, this)(aivID);
        if (fit <= 0) {
            return -2;
        }
        this->aivs[aivID].castleID = castleID;
        if (fit == 999999) {
            // perfect fit
            this->aivs[aivID].aivSubType = 2;
            return 100;
        }
        this->aivs[aivID].aivSubType = 1;
        // the counters are declared unsigned but used as signed values
        if ((int)this->buildingCounter == 0) {
            return 100;
        }
        return ((int)this->buildingCounter - (int)this->invalidTileCounter) * 100 / (int)this->buildingCounter;
    }

}
}
