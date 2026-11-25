#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522950
        int TribesState::createPlayerTribe(int playerID, undefined4 one, int tribeID)
        {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(Tribe), '\0', &this->tribes[tribeID]);
            this->tribes[tribeID].tribeState = 2;
            this->tribes[tribeID].owner = playerID;
            this->tribes[tribeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->tribes[tribeID].tribeType = 0;
            this->tribes[tribeID].field_0x1c = 0;
            this->tribes[tribeID].field_0x1e = 0;
            this->tribes[tribeID].tribeBehaviorType = 0;
            this->tribes[tribeID].field_0x30 = 0;
            this->tribes[tribeID].selectionTargetUnitID = 0;
            this->tribes[tribeID].size = 0;
            return tribeID;
        }

    }
}
}
