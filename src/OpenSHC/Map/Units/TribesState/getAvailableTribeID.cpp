#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522720
        int TribesState::getAvailableTribeID(int playerID)
        {
            /*
              Early returns rather than the decompiler's nested `if (0 < _tribeID)` arms:
              the original places each `xor eax, eax` inline behind its own guard.
             */
            int _tribeID;
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                _tribeID = 1249;
                /*
                  Stored once before the loop (0x52272e) and then only after each
                  decrement; the decompiler's repeat of the store after the loop is not in
                  the instruction stream.

                  Both of these loops stay as `while`. The original recomputes the address
                  every iteration and does not strength-reduce them (0x00522733 and
                  0x00522790):

                    L:mov edx, eax; imul edx, edx, 0x334; add edx, ecx
                      cmp word ptr [edx + 0x40], 0 ... jg L

                  where ours hoists `lea edx, [ecx + 0xfa0de]` and walks it with
                  `sub edx, 0x334`. Rewriting both as a top test with an explicit jump
                  back - the change that took the twin createTribeForPlayer from 75.2% to
                  86.2% - fixes the rotation but not the reduction: MSVC still hoists the
                  address, and the result is flat at 62.3%.

                  The difference between the two functions is that createTribeForPlayer's
                  original strength-reduces as well (`sub eax, 0x19a0`), so matching its
                  loop shape was enough there. Here the reduction is the whole gap and it
                  is not reachable from the source.
                 */
                DAT_CurrentTribeID::instance = _tribeID;
                while (this->tribes[_tribeID].tribeState != 0 || this->tribes[_tribeID].time != 0) {
                    _tribeID = _tribeID + -1;
                    DAT_CurrentTribeID::instance = _tribeID;
                    if (_tribeID <= 0) {
                        return 0;
                    }
                }
                if (_tribeID <= 0) {
                    return 0;
                }
                this->tribes[_tribeID].time = 1;
                return _tribeID;
            }
            _tribeID = 1250 - playerID;
            DAT_CurrentTribeID::instance = _tribeID;
            if (_tribeID <= 0) {
                return 0;
            }
            /*
              is tribe slot in use?
             */
            while (this->tribes[_tribeID].tribeState != 0 || this->tribes[_tribeID].time != 0) {
                _tribeID = _tribeID + -8;
                DAT_CurrentTribeID::instance = _tribeID;
                if (_tribeID <= 0) {
                    return 0;
                }
            }
            if (_tribeID <= 0) {
                return 0;
            }
            /*
              claim it. The 400 is added to the full tick count and only then truncated
              (`mov edx, [..]`, `add edx, 0x190`, `mov word ptr [..], dx`), not to a value
              already cut down to a short.
             */
            this->tribes[_tribeID].time = (short)(DAT_GameCore::instance.mapTimeInTicks + 400);
            return _tribeID;
        }

    }
}
}
