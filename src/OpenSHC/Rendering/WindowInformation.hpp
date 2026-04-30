/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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

        WindowInformation();
        ~WindowInformation();

    public:
        void storeWindowRectangleInfoUnk(LONG param_1, LONG param_2, LONG param_3, LONG param_4);
    };

    static_assert_cpp98_obj(sizeof(WindowInformation) == 64, WindowInformation);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(WindowInformation, false, Address::SHC_3BB0A8C1_0x01A27980) pDAT_WindowInformation;

} // namespace Rendering
} // namespace OpenSHC
