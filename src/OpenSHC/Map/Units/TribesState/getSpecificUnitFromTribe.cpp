#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_00ee0fb4.hpp"
#include "OpenSHC/Globals/DAT_Tribe_HighestID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522410
        int TribesState::getSpecificUnitFromTribe(int tribeID, int param_2)
        {
            short* psVar3;
            if (param_2 == 0) {
                DAT_Tribe_HighestID::instance = (int)this->tribes[tribeID].highestID;
                DAT_00ee0fb4::instance = 0;
            }
            /*
              Both globals are read before the bound test, which is the order the original
              loads them in.
             */
            int iVar1 = DAT_Tribe_HighestID::instance;
            int iVar2 = DAT_00ee0fb4::instance;
            if (iVar1 < 200) {
                psVar3 = this->tribes[tribeID].unitSelectionBitMasked + iVar1;
                do {
                    /*
                      The word is read once: `movzx edx, word ptr [esi]` for the zero test,
                      then `movsx edx, dx` for the bit tests, rather than a load per bit.
                     */
                    short const _bits = *psVar3;
                    if ((_bits != 0) && (iVar2 < 0x10)) {
                        do {
                            if ((int)_bits & 1 << iVar2) {
                                DAT_00ee0fb4::instance = iVar2 + 1;
                                /*
                                  The wrap arm is the fall-through. The original stores the
                                  incremented bit index, tests it and jumps 0x1d forward
                                  when it has not reached sixteen (`cmp edx, 0x10; mov
                                  [..], edx; jne 0x1d`), so the arm that advances the tribe
                                  id and resets the bit index is what follows the test.
                                 */
                                if (iVar2 + 1 == 0x10) {
                                    DAT_Tribe_HighestID::instance = iVar1 + 1;
                                    DAT_00ee0fb4::instance = 0;
                                    return iVar1 * 0x10 + iVar2;
                                }
                                DAT_Tribe_HighestID::instance = iVar1;
                                return iVar1 * 0x10 + iVar2;
                            }
                            iVar2 = iVar2 + 1;
                        } while (iVar2 < 0x10);
                    }
                    /*
                      MSVC keeps a zero of its own in a register here - `xor edi, edi` up
                      front, which costs it `ebx` and turns the function's immediate tests
                      into register compares (`cmp dx, di` where the original has
                      `test dx, dx`). The original materialises its zero into the counter
                      and stores from there. Writing the store below as
                      `DAT_00ee0fb4::instance = iVar2` to say the same thing measures
                      55.1% -> 55.1%: the dedicated zero register survives it, so this is
                      the register allocator rather than the spelling.
                     */
                    iVar2 = 0;
                    iVar1 = iVar1 + 1;
                    psVar3 = psVar3 + 1;
                    DAT_00ee0fb4::instance = 0;
                } while (iVar1 < 200);
            }
            return 0;
        }

    }
}
}
