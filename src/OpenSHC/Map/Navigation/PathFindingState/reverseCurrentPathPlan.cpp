#include "../PathFindingState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A5E0
        void PathFindingState::reverseCurrentPathPlan()
        {
            byte bVar1;
            byte bVar2;
            uint _index;
            byte* pbVar3;
            uint _endIndex;
            int _swapCounter;
            /*
              Index from start of path
             */
            _index = 0;
            /*
              === ONLY REVERSE IF PATH HAS MORE THAN 1 ELEMENT ===
             */
            /*
              Index from end of path
             */
            if (1 < (int)this->searchQueue.pathPlanIndex) {
                /*
                  Calculate number of swaps needed (swap pairs from both ends toward center)   Example: 8 elements = 4
                  swaps, 7 elements = 3 swaps
                 */
                _swapCounter = (this->searchQueue.pathPlanIndex - 2 >> 1) + 1;
                _endIndex = this->searchQueue.pathPlanIndex;
                do {
                    /*
                      === SWAP LOOP: Exchange elements from both ends ===   === EXTRACT DIRECTION AT START (uVar3) ===
                     */
                    _endIndex = _endIndex - 1;
                    if ((_index & 1) == 0) {
                        /*
                          Even index: direction is in LOW nibble (bits 0-3)
                         */
                        bVar2 = this->searchQueue.ptrPathPlan[(int)_index / 2] & 0xf;
                    } else {
                        /*
                          Odd index: direction is in HIGH nibble (bits 4-7)
                         */
                        bVar2 = (char)this->searchQueue.ptrPathPlan[(int)_index / 2] >> 4;
                    }
                    /*
                      === EXTRACT DIRECTION AT END (_prevIndex) ===
                     */
                    if ((_endIndex & 1) == 0) {
                        /*
                          Even index: direction is in LOW nibble
                         */
                        bVar1 = this->searchQueue.ptrPathPlan[(int)_endIndex / 2] & 0xf;
                    } else {
                        /*
                          Odd index: direction is in HIGH nibble
                         */
                        bVar1 = (char)this->searchQueue.ptrPathPlan[(int)_endIndex / 2] >> 4;
                    }
                    /*
                      === WRITE END DIRECTION TO START POSITION ===
                     */
                    pbVar3 = this->searchQueue.ptrPathPlan + (int)_index / 2;
                    if ((_index & 1) == 0) {
                        /*
                          Even index: clear LOW nibble, keep HIGH nibble
                         */
                        *pbVar3 = *pbVar3 & 0xf0;
                    } else {
                        /*
                          Odd index: clear HIGH nibble, keep LOW nibble
                         */
                        *pbVar3 = *pbVar3 & 0xf;
                        /*
                          Shift value to HIGH nibble position
                         */
                        bVar1 = bVar1 << 4;
                    }
                    /*
                      Write the direction value
                     */
                    this->searchQueue.ptrPathPlan[(int)_index / 2]
                        = this->searchQueue.ptrPathPlan[(int)_index / 2] + bVar1;
                    /*
                      === WRITE START DIRECTION TO END POSITION ===
                     */
                    pbVar3 = this->searchQueue.ptrPathPlan + (int)_endIndex / 2;
                    if ((_endIndex & 1) == 0) {
                        /*
                          Even index: clear LOW nibble
                         */
                        *pbVar3 = *pbVar3 & 0xf0;
                    } else {
                        /*
                          Odd index: clear HIGH nibble
                         */
                        *pbVar3 = *pbVar3 & 0xf;
                        /*
                          Shift value to HIGH nibble position
                         */
                        bVar2 = bVar2 << 4;
                    }
                    /*
                      Write the direction value
                     */
                    this->searchQueue.ptrPathPlan[(int)_endIndex / 2]
                        = this->searchQueue.ptrPathPlan[(int)_endIndex / 2] + bVar2;
                    /*
                      === MOVE INDICES TOWARD CENTER ===   Move end index forward
                     */
                    /*
                      Move start index forward
                     */
                    _index = _index + 1;
                    /*
                      Decrement swap counter
                     */
                    _swapCounter = _swapCounter + -1;
                } while (_swapCounter != 0);
            }
            return;
        }

    }
}
}
