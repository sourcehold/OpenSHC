#include "OpenSHC/Map/Units/UnitsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00535550
        BOOLEnum UnitsState::selectionHasEngineers() { return (BOOLEnum)(this->selectionEngineers != 0); }

    }
}
}
