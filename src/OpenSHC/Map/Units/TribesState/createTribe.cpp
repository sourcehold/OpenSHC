#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Map::Units::SomeTribeBehaviorType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522890
        int TribesState::createTribe(int playerID, int setAsCurrentTribeID)
        {
            DAT_CurrentTribeID::instance = 1;
            do {
                int _tribeID = DAT_CurrentTribeID::instance;
                if (this->tribes[DAT_CurrentTribeID::instance].tribeState == 0) {
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        820, '\0', (void*)((int)(this->tribes + DAT_CurrentTribeID::instance)));
                    if (_tribeID <= 0) {
                        return 0;
                    }
                    if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) && (setAsCurrentTribeID)) {
                        this->DAT_CurrentTribeID = _tribeID;
                    }
                    this->tribes[_tribeID].owner = playerID;
                    this->tribes[_tribeID].tribeState = 2;
                    this->tribes[_tribeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                    DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
                    this->tribes[_tribeID].tribeType = ((AITribeType)0);
                    this->tribes[_tribeID].field19_0x1c = 0;
                    this->tribes[_tribeID].field20_0x1e = 0;
                    this->tribes[_tribeID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                    this->tribes[_tribeID].field30_0x30 = 0;
                    this->tribes[_tribeID].selectionTargetUnitID = 0;
                    this->tribes[_tribeID].size = 0;
                    return _tribeID;
                }
                DAT_CurrentTribeID::instance = DAT_CurrentTribeID::instance + 1;
            } while (DAT_CurrentTribeID::instance < 0x4e2);
            return 0;
        }

    }
}
}
