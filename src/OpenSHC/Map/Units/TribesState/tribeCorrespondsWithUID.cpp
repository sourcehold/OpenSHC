#include "../TribesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522360
        BOOLEnum TribesState::tribeCorrespondsWithUID(int tribeID, uint tribeUID)
        {
            if (tribeUID == 0) {
                return FALSE;
            }
            return this->tribes[tribeID].uid == tribeUID;
        }

    }
}
}
