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

          The `if (0 < slot)` around the stores also stays. The original returns zero
          through an epilogue of its own right there - `cmp edi, ebx; jg 0x9` over
          `pop/pop/pop/xor eax,eax/pop/ret 4` - where ours sends that return to the shared
          epilogue and inverts the test to `jle`, so a flat guard looks like the obvious
          fix. It measures 75.2% -> 73.2%. Flattening guard chains is as unpredictable as
          caching the base: it took trySpawnAdditionalWildlifeForTribe to a full match
          (+12.8) and gained +0.6 on predictUnitInterceptPosition, but costs 1.4 on
          isTribePathToDestinationClear and 2.0 here. Measure it; do not assume it.
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
                /*
                  Top-tested, with the back-edge returning to the test, which is what the
                  original has at 0x522801:

                    lea eax, [eax + ecx + 0x40]   ; the cursor, taken once
                  L:cmp word ptr [eax], bx        ; tested through it
                    je  <found>
                    sub edi, 8
                    sub eax, 0x19a0
                    cmp edi, ebx
                    jg  L

                  A `while (*psVar1 != 0)` gets rotated: MSVC peels the first test, and
                  does that one through two-register addressing (`cmp word ptr [eax + ecx
                  + 0x40], bx`) before taking the cursor at all, then bottom-tests the
                  rest. Writing the test at the top with an explicit jump back keeps the
                  cursor as the only way the field is read.
                 */
                psVar1 = &this->tribes[_selectionID].tribeState;
            LAB_00522801:
                if (*psVar1 != 0) {
                    _selectionID = _selectionID + -8;
                    psVar1 = psVar1 - 0xcd0;
                    if (0 < _selectionID) {
                        goto LAB_00522801;
                    }
                    return 0;
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
