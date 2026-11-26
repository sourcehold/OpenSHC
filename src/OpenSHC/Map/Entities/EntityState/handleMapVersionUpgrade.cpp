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
                MACRO_CALL(Map::Version_Func::DeleteSeagull)();
            }
            if (receivedMapVersion != packagerMapVersion) {
                if (receivedMapVersion == 100) {
                    MACRO_CALL(Map::Version_Func::UpgradeSetCurrentEntityID3000)();
                }
                if (receivedMapVersion < 145) {
                    MACRO_CALL(Map::Version_Func::SetFlagEntityColor)();
                }
                if (receivedMapVersion < 160) {
                    MACRO_CALL(Map::Version_Func::UpgradeFirst25Entities)();
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
