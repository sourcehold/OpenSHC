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
                if (this->tribes[DAT_CurrentTribeID::instance].tribeState == 0) {
                    /*
                      The index is only copied out of the loop counter once the slot is
                      known free (`mov edi, eax` at 0x5228c9), and the tribe's address is
                      taken before the clear (`lea esi, [edx + ebp]`, `lea eax, [esi +
                      0x28]`), then reused for every store below it.
                     */
                    int const _tribeID = DAT_CurrentTribeID::instance;
                    /*
                      A shifted TribesState pointer, not a `Tribe&`. The original computes
                      the base without the `tribes` offset (`lea esi, [edx + ebp]`) and then
                      takes `lea eax, [esi + 0x28]` separately for the clear's argument,
                      reaching the fields as `[esi + 0x2c]` and so on. A reference folds the
                      0x28 into one lea and shifts every field displacement by it.
                     */
                    TribesState* const _tb
                        = (TribesState*)((char*)this + _tribeID * sizeof(Tribe));
                    MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                        sizeof(Tribe), '\0', &_tb->tribes[0]);
                    /*
                      An early return, which is where the original puts its `return 0`:
                      `cmp edi, ebx; jg` falls straight into `xor eax, eax` with the claim
                      following, rather than jumping over the claim to a shared epilogue.
                     */
                    if (_tribeID <= 0) {
                        return 0;
                    }
                    {
                        if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                            && (setAsCurrentTribeID)) {
                            this->DAT_CurrentTribeID = _tribeID;
                        }
                        _tb->tribes[0].owner = playerID;
                        _tb->tribes[0].tribeState = 2;
                        _tb->tribes[0].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
                        DAT_GameCore::instance.uniqueGameObjectTracker
                            = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
                        _tb->tribes[0].tribeType = ((AITribeType)0);
                        _tb->tribes[0].field18_0x1c = 0;
                        _tb->tribes[0].field19_0x1e = 0;
                        _tb->tribes[0].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                        _tb->tribes[0].field29_0x30 = 0;
                        _tb->tribes[0].selectionTargetUnitID = 0;
                        _tb->tribes[0].size = 0;
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
