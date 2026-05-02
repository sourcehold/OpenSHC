/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ScrollingHandler.hpp'
*/

#pragma once

#include "OpenSHC/UI/ScrollDirectionInt.hpp"
#include "OpenSHC/UI/ScrollSpeedInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ScrollDirectionInt;
    using OpenSHC::UI::ScrollSpeedInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000048
    class ScrollingHandler {
    public:
        BOOLEnum isScrolling_0x0; // 0x00000000 length: 4
        ScrollDirectionInt scrollDirection_0x4; // 0x00000004 length: 4
        BOOLEnum scrollRight; // 0x00000008 length: 4
        BOOLEnum scrollLeft; // 0x0000000C length: 4
        BOOLEnum scrollDown; // 0x00000010 length: 4
        BOOLEnum scrollUp; // 0x00000014 length: 4
        BOOLEnum rightKeyDown_0x18; // 0x00000018 length: 4
        BOOLEnum leftKeyDown_0x1c; // 0x0000001C length: 4
        BOOLEnum downKeyDown_0x20; // 0x00000020 length: 4
        BOOLEnum upKeyDown_0x24; // 0x00000024 length: 4
        undefined4 field10_0x28; // 0x00000028 length: 4
        undefined4 field11_0x2c; // 0x0000002C length: 4
        undefined4 field12_0x30; // 0x00000030 length: 4
        undefined4 field13_0x34; // 0x00000034 length: 4
        ScrollSpeedInt scrollSpeedSetting_0x38; // 0x00000038 length: 4
        int scrollDistanceBase; // 0x0000003C length: 4
        int timeOfLastNotScroll_0x40; // 0x00000040 length: 4
        int timeScrolling_0x44; // 0x00000044 length: 4

    private:
        ScrollingHandler(ScrollingHandler const&);
        void operator=(ScrollingHandler const&);

        ScrollingHandler();
        ~ScrollingHandler();

    public:
        // Constructor
        ScrollingHandler* Constructor_ScrollingHandler();

        void handleScrolling();

        int getScrollDistanceBaseUnk();
    };

    static_assert_cpp98_obj(sizeof(ScrollingHandler) == 72, ScrollingHandler);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(ScrollingHandler, false, Address::SHC_3BB0A8C1_0x0112B070) pDAT_ScrollingHandler;

} // namespace UI
} // namespace OpenSHC
