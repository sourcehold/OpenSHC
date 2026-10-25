#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522950
        int TribesState::createPlayerTribe(int playerID, undefined4 one, int tribeID)
        {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                820, '\0', (void*)((int)(this->tribes + tribeID)));
            this->tribes[tribeID].tribeState = 2;
            this->tribes[tribeID].owner = playerID;
            this->tribes[tribeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->tribes[tribeID].tribeType = ((AITribeType)0);
            this->tribes[tribeID].field18_0x1c = 0;
            this->tribes[tribeID].field19_0x1e = 0;
            this->tribes[tribeID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
            this->tribes[tribeID].field29_0x30 = 0;
            this->tribes[tribeID].selectionTargetUnitID = 0;
            this->tribes[tribeID].size = 0;
            return tribeID;
        }

    }
}
}
