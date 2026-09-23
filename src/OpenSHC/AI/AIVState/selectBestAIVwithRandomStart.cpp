#include "../AIVState.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    // starts at a random castle and picks the first one that fits perfectly, otherwise the best fitting one
    // FUNCTION: STRONGHOLDCRUSADER 0x004F13F0
    void AIVState::selectBestAIVwithRandomStart(int aivID)
    {
        uint castleID = (byte)SEC_RNG::instance.currentNumber2 & 7;
        int bestFit = 0;
        int bestCastleID = -1;
        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->isHandled), 0, this->isHandled);
        for (int tries = 0; tries < 8; ++tries) {
            ++castleID;
            if ((int)castleID > 7) {
                castleID = 0;
            }
            int const aiType = this->aivs[aivID].aiType;
            if (!this->aivFilePresent[aiType - 2][castleID]) {
                continue;
            }
            if (!MACRO_CALL_MEMBER(IO::FilePackager_Func::unpackAIVFile, FilePackagerObj::ptr)(
                    DAT_AIVDefinedData::instance.AIVSectionAddressArray,
                    DAT_AIVDefinedData::instance.AIVFileNames[aiType - 2][castleID])) {
                continue;
            }
            MACRO_CALL_MEMBER(AIVState_Func::rotateAIV, this)(this->aivs[aivID].keepOrientation);
            int const fit = MACRO_CALL_MEMBER(AIVState_Func::computeAIVPlacementFit, this)(aivID);
            if (fit <= 0) {
                continue;
            }
            if (fit == 999999) {
                // the first perfectly fitting castle is taken
                this->aivs[aivID].castleID = castleID;
                this->aivs[aivID].aivSubType = 2;
                return;
            }
            if (fit > bestFit) {
                bestFit = fit;
                bestCastleID = castleID;
            }
        }
        if (bestCastleID >= 0) {
            this->aivs[aivID].aivSubType = 1;
            this->aivs[aivID].castleID = bestCastleID;
        }
    }

}
}
