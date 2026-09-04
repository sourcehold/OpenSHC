#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522C20
        void TribesState::setUnitStance(int tribeID, UnitStanceEnum unitStance)
        {
            this->tribes[tribeID].unitStance = unitStance;
            DAT_GameCore::instance.countdown = 1;
        }

    }
}
}
