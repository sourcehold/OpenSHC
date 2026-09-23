#include "../AIVState.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_AIVDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace AI {

    // hashes all AIV files and lists the AIs that have at least one AIV
    // FUNCTION: STRONGHOLDCRUSADER 0x004ECAD0
    void AIVState::setAvailableAIV()
    {
        for (int i = 0; i < 20; ++i) {
            this->aivFileAvailabilityPerAIArray[i] = 0;
        }
        this->numberOfAIsWithAIV = 0;
        for (int aiIndex = 0; aiIndex < 16; ++aiIndex) {
            int availableAIVs = 0;
            for (int castleID = 0; castleID < 8; ++castleID) {
                int const hash = MACRO_CALL_MEMBER(IO::ResourceManager_Func::getSimpleFirst1024ByteSumOfFile,
                    DAT_ResourceManager::ptr)(DAT_AIVDefinedData::instance.AIVFileNames[aiIndex][castleID]);
                this->aivFileHash[aiIndex][castleID] = hash;
                if (hash != -1) {
                    ++availableAIVs;
                }
            }
            if (availableAIVs != 0) {
                this->aivFileAvailabilityPerAIArray[aiIndex] = availableAIVs;
                DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[this->numberOfAIsWithAIV] = aiIndex + 1;
                ++this->numberOfAIsWithAIV;
            }
        }
        DAT_GameCore::instance.numOfAIsWithCastleUnk = this->numberOfAIsWithAIV;
    }

}
}
