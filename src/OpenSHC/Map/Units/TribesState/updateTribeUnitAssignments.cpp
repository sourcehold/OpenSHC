#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00527330
        void TribesState::updateTribeUnitAssignments()
        {
            uint _unitID;
            this->clans = 0;
            this->field2_0x8 = 1;
            /*
              A `for`, not the original's do-while, because the two `continue`s have to run
              the increment: the label they replace sat in front of it. The first test is
              always true, so the two forms are equivalent. This costs 2.9 points
              (60.0% -> 57.1%) for the entry test the do-while does not have; writing the
              arms out with a `clearTribe` call in each instead measures worse still
              (quick_diff 0.6076 against 0.6250), so the `for` stands. The import's
              `if (0x4e1 < instance) {}` had an empty body, which made this loop run
              forever.
             */
            for (DAT_CurrentTribeID::instance = 1; (int)DAT_CurrentTribeID::instance < 1250;
                DAT_CurrentTribeID::instance = DAT_CurrentTribeID::instance + 1) {
                /*
                  The state, the size and the time are all compared as 16-bit values
                  (`movzx ecx, word ptr`, then `cmp cx, bx` / `cmp cx, 3` / `jle`), so they
                  stay `short` here; the earlier `(ushort)` casts turned the signed `jle` on
                  the size into a test only zero could pass. It costs 1.4 points
                  (58.4% -> 57.0%), which is the price of being right about negative sizes.
                 */
                short const _state = this->tribes[DAT_CurrentTribeID::instance].tribeState;
                int _tribeUnitIndex = 0;
                if (_state) {
                    int _tribeID = DAT_CurrentTribeID::instance;
                    if (_state != 3) {
                        short const _size = this->tribes[DAT_CurrentTribeID::instance].size;
                        /*
                          The unit sweep is the fall-through. The original compares the
                          size against the zero it is holding in bx and jumps 0x7d forward
                          when it is not positive (`cmp cx, bx; jle 0x7d`), so the sweep
                          follows the test and the four-line time check goes in the far
                          block. The `<= 0` sense itself is right and stays - see above.
                         */
                        if (0 < _size) {
                            int const _tribeSize = (int)_size;
                            int local_4 = 0;
                            if (0 < _tribeSize) {
                                do {
                                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSpecificUnitFromTribe,
                                        this)(_tribeID, _tribeUnitIndex);
                                    int _unitLogicalState = DAT_UnitsState::instance.units[_unitID].logicalState;
                                    _tribeUnitIndex = _tribeUnitIndex + 1;
                                    /*
                                      `< 1` stays although the original has
                                      `test edx, edx; jle` where ours gives
                                      `cmp edx, 1; jl`: written `<= 0` the whole chain
                                      below it re-lays out and the function measures
                                      75.0% -> 55.3%. The instruction is one line; the
                                      block order it costs is twenty.
                                     */
                                    if (_unitLogicalState < 1
                                        || (2 < _unitLogicalState
                                            && (_unitLogicalState != Map::Units::ULS_TRANSITIONING))
                                        || DAT_UnitsState::instance.units[_unitID].dying != 0
                                        || DAT_UnitsState::instance.units[_unitID].tribeID != _tribeID) {
                                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe, this)(
                                            _unitID, _tribeID);
                                        _tribeID = DAT_CurrentTribeID::instance;
                                    } else {
                                        local_4 = local_4 + 1;
                                    }
                                } while (_tribeUnitIndex < _tribeSize);
                                if (local_4) {
                                    this->clans = this->clans + 1;
                                    this->field2_0x8 = DAT_CurrentTribeID::instance;
                                    continue;
                                }
                            }
                        } else {
                            short const _tribeTime = this->tribes[DAT_CurrentTribeID::instance].time;
                            if (_tribeTime && (int)DAT_GameCore::instance.mapTimeInTicks <= (int)_tribeTime
                                && _tribeTime)
                                continue;
                        }
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::clearTribe, this)(_tribeID);
                }
            }
        }

    }
}
}
