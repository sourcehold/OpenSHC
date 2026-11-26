#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00408770
        void EntityState::handleMapVersionUpgrade(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
                OpenSHC::Map::Version::DeleteSeagull();
            }
            if (receivedMapVersion != packagerMapVersion) {
                if (receivedMapVersion == 100) {
                    OpenSHC::Map::Version::UpgradeSetCurrentEntityID3000();
                }
                if (receivedMapVersion < 145) {
                    OpenSHC::Map::Version::SetFlagEntityColor();
                }
                if (receivedMapVersion < 160) {
                    OpenSHC::Map::Version::UpgradeFirst25Entities();
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
