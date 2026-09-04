#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Commands/MappersEnumInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Commands::MappersEnumInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x005010C0
    void HoveredState::clearHoveredState()
    {
        for (int i = 0; i < 20; i++) {
            this->elements[i].type = OpenSHC::Commands::M_MAPPER_NULL;
        }
    }

}
}
