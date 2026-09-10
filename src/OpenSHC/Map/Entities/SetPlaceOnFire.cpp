#include "OpenSHC/Map/Entities.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00407160
    void Entities::SetPlaceOnFire(int playerID, int x, int y, int height, int param_5)
    {
        MACRO_CALL(OpenSHC::Map::Entities_Func::AFireSpreadFunction)(playerID, x, y, height, param_5, 0);
    }

}
}
