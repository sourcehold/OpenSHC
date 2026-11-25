/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Text/NumberOfDigitsThreshold.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Text {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct NumberOfDigitsThreshold {

            int maxNumber; // 0x00000000 length: 4
            int numberOfDigits; // 0x00000004 length: 4

        } NumberOfDigitsThreshold;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(NumberOfDigitsThreshold) == 8, NumberOfDigitsThreshold);
    } // namespace Text
} // namespace UI
} // namespace OpenSHC
