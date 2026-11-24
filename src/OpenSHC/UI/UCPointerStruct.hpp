/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/UCPointerStruct.hpp'
*/

#pragma once

#include "OpenSHC/UI/UC.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::UC;

#pragma pack(push, 1)

    // SIZE: 0x00000004
    class UCPointerStruct {
    public:
        UC* ucArrayPointer; // 0x00000000 length: 4

    private:
        UCPointerStruct(UCPointerStruct const&);
        void operator=(UCPointerStruct const&);

    public:
        UCPointerStruct() {};
        ~UCPointerStruct() {};

        void loadMenuElement(int ucId, int* xPosPtr, int* yPosPtr, ushort* iconDeactivatedPtrUnk, int ucPositionIndex);
    };

    static_assert_cpp98_obj(sizeof(UCPointerStruct) == 4, UCPointerStruct);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
