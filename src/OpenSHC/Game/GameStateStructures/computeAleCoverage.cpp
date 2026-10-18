#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00458E20
    int GameStateStructures::computeAleCoverage(int playerID)
    {
        if (this->playerDataArray[playerID].workingInnsCount <= 0) {
            return 0;
        }
        if (this->playerDataArray[playerID].currentPopulation <= 0) {
            return 0;
        }
        int aleCoverage = (this->playerDataArray[playerID].workingInnsCount * 3000)
            / this->playerDataArray[playerID].currentPopulation;
        if (aleCoverage < 0) {
            return 0;
        }
        if (aleCoverage > 100) {
            return 100;
        }
        return aleCoverage;
    }

}
}
