#include "OpenSHC/Map/LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1BE0
    undefined4 LandscapeState::getValueFrom0UpTo3ForTreeTypeAndTreeStage(undefined4 treeType, int treeStage)
    {
        if (treeStage <= 1) {
            return 1;
        }
        switch (treeType) {
        case 1:
            return 3;
        case 2:
            return 3;
        case 3:
            return 2;
        case 4:
            return 2;
        case 5:
            return 1;
        case 6:
            return 1;
        case 7:
            return 1;
        case 8:
            return 1;
        case 9:
            return 1;
        case 15:
            return 2;
        default:
            return 0;
        }
    }

}
}
