/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/EuroRecruitableState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum EuroRecruitableState {

            ERS_CAN_NOT_RECRUIT = 0, // 0x00000000
            ERS_CAN_RECRUITUnk = 1, // 0x00000001
            ERS_NOT_ALLOWED_TO_RECRUIT = 2, // 0x00000002
            ERS_UNABLE_BECAUSE_MAX_ARMY = 3, // 0x00000003
            ERS_UNABLE_MISSING_PEASANTS = 4, // 0x00000004
            ERS_UNABLE_MISSING_GOLD = 5, // 0x00000005
            ERS_UNABLE_MISSING_WEAPONSUnk = 6 // 0x00000006

        } EuroRecruitableState;

        static_assert_cpp98_obj(sizeof(EuroRecruitableState) == 4, EuroRecruitableState);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
