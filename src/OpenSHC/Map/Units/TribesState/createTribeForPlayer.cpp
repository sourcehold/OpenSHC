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

        /*
          The inner slot-ID guard stays a positive `if` around the claim: inverting it to an
          early return, which took spawnUnitsIntoNewTribe from 89.4% to 98.3%, costs 2.0
          points here (75.2% -> 73.2%).

          The repeated subscript stays too. The original does take the tribe's address once
          before the clear (`lea esi, [edx + ecx]`, `lea eax, [esi + 0x28]` at 0x522823) and
          reach every store through it, and writing that as a `Tribe&` is what took the twin
          createTribe from 30.3% to 67.2% - but here the identical change costs 37.3 points
          (75.2% -> 37.9%). The two functions differ only in how they find the slot, so the
          shape that matches one does not match the other.
         */
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
                psVar1 = &this->tribes[_selectionID].tribeState;
                while (*psVar1 != 0) {
                    _selectionID = _selectionID + -8;
                    psVar1 = psVar1 - 0xcd0;
                    if (_selectionID <= 0) {
                        return 0;
                    }
                }
                /*
                  wipe the tribe
                 */
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Tribe), '\0', &this->tribes[_selectionID]);
                if (0 < _selectionID) {
                    this->tribes[_selectionID].owner = playerID;
                    this->tribes[_selectionID].tribeState = 2;
                    this->tribes[_selectionID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                    DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
                    this->tribes[_selectionID].tribeType = ((AITribeType)0);
                    this->tribes[_selectionID].field18_0x1c = 0;
                    this->tribes[_selectionID].field19_0x1e = 0;
                    this->tribes[_selectionID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                    this->tribes[_selectionID].field29_0x30 = 0;
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
