/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/WindowInformation.hpp'
*/

#pragma once

#include "WinDef.h"
#include "winnt.h"

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)

    // SIZE: 0x00000040
    class WindowInformation {
    public:
        undefined1 padding_0x0[48]; // 0x00000000 length: 48
        RECT RECT_SomeGameWindowRectUnk; // 0x00000030 length: 16

    private:
        WindowInformation(WindowInformation const&);
        void operator=(WindowInformation const&);

    public:
        WindowInformation();
        ~WindowInformation();

        void storeWindowRectangleInfoUnk(LONG param_1, LONG param_2, LONG param_3, LONG param_4);
    };

    static_assert_cpp98_obj(sizeof(WindowInformation) == 64, WindowInformation);

#pragma pack(pop)

} // namespace Rendering
} // namespace OpenSHC
