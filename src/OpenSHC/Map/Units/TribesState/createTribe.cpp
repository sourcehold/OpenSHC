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
                        sizeof(Tribe), '\0', &this->tribes[DAT_CurrentTribeID::instance]);
                    /*
                      An early return, which is where the original puts its `return 0`:
                      `cmp edi, ebx; jg` falls straight into `xor eax, eax` with the claim
                      following, rather than jumping over the claim to a shared epilogue.
                     */
                    if (_tribeID <= 0) {
                        return 0;
                    }
                    {
                        Tribe& _tribe = this->tribes[_tribeID];
                        if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            && (setAsCurrentTribeID)) {
                            this->DAT_CurrentTribeID = _tribeID;
                        }
                        _tribe.owner = playerID;
                        _tribe.tribeState = 2;
                        _tribe.uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                        DAT_GameCore::instance.uniqueGameObjectTracker
                            = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
                        _tribe.tribeType = ((AITribeType)0);
                        _tribe.field18_0x1c = 0;
                        _tribe.field19_0x1e = 0;
                        _tribe.tribeBehaviorType = ((SomeTribeBehaviorType)0);
                        _tribe.field29_0x30 = 0;
                        _tribe.selectionTargetUnitID = 0;
                        _tribe.size = 0;
                        return _tribeID;
                    }
                }
                DAT_CurrentTribeID::instance = DAT_CurrentTribeID::instance + 1;
            } while ((int)DAT_CurrentTribeID::instance < 1250);
            return 0;
        }

    }
}
}
