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

        // FUNCTION: STRONGHOLDCRUSADER 0x005227E0
        int TribesState::createTribeForPlayer(int playerID)
        {
            short* psVar1;
            int _selectionID;
            _selectionID = 1250 - playerID;
            if (0 < _selectionID) {
                /*
                  find an empty tribe
                 */
                psVar1 = (short*)((int)this + _selectionID * 0x334 + 0x40);
                while (*psVar1 != 0) {
                    _selectionID = _selectionID + -8;
                    psVar1 = psVar1 + -0xcd0;
                    if (_selectionID <= 0) {
                        return 0;
                    }
                }
                /*
                  wipe the tribe
                 */
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    820, '\0', (void*)((int)(this->tribes + _selectionID)));
                if (0 < _selectionID) {
                    this->tribes[_selectionID].owner = playerID;
                    this->tribes[_selectionID].tribeState = 2;
                    this->tribes[_selectionID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                    DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
                    this->tribes[_selectionID].tribeType = ((AITribeType)0);
                    this->tribes[_selectionID].field19_0x1c = 0;
                    this->tribes[_selectionID].field20_0x1e = 0;
                    this->tribes[_selectionID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                    this->tribes[_selectionID].field30_0x30 = 0;
                    this->tribes[_selectionID].selectionTargetUnitID = 0;
                    this->tribes[_selectionID].size = 0;
                    return _selectionID;
                }
            }
            return 0;
        }

    }
}
}
