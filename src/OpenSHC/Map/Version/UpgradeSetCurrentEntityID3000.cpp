#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004038A0
    void Version::UpgradeSetCurrentEntityID3000() { DAT_CurrentEntityID::instance = 3000; }

}
}
