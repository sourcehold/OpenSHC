/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/WindowsHelper/Enums/WindowsSystemMetric.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Enums {
        typedef enum WindowsSystemMetric {

            SM_CXSCREEN = 0, // 0x00000000
            SM_CYSCREEN = 1, // 0x00000001
            SM_CXVSCROLL = 2, // 0x00000002
            SM_CYHSCROLL = 3, // 0x00000003
            SM_CYCAPTION = 4, // 0x00000004
            SM_CXBORDER = 5, // 0x00000005
            SM_CYBORDER = 6, // 0x00000006
            SM_CXDLGFRAME = 7, // 0x00000007
            SM_CXFIXEDFRAME = 7, // 0x00000007
            SM_CYDLGFRAME = 8, // 0x00000008
            SM_CYFIXEDFRAME = 8, // 0x00000008
            SM_CYVTHUMB = 9, // 0x00000009
            SM_CXHTHUMB = 10, // 0x0000000A
            SM_CXICON = 11, // 0x0000000B
            SM_CYICON = 12, // 0x0000000C
            SM_CXCURSOR = 13, // 0x0000000D
            SM_CYCURSOR = 14, // 0x0000000E
            SM_CYMENU = 15, // 0x0000000F
            SM_CXFULLSCREEN = 16, // 0x00000010
            SM_CYFULLSCREEN = 17, // 0x00000011
            SM_CYKANJIWINDOW = 18, // 0x00000012
            SM_MOUSEPRESENT = 19, // 0x00000013
            SM_CYVSCROLL = 20, // 0x00000014
            SM_CXHSCROLL = 21, // 0x00000015
            SM_DEBUG = 22, // 0x00000016
            SM_SWAPBUTTON = 23, // 0x00000017
            SM_CXMIN = 28, // 0x0000001C
            SM_CYMIN = 29, // 0x0000001D
            SM_CXSIZE = 30, // 0x0000001E
            SM_CYSIZE = 31, // 0x0000001F
            SM_CXFRAME = 32, // 0x00000020
            SM_CXSIZEFRAME = 32, // 0x00000020
            SM_CYFRAME = 33, // 0x00000021
            SM_CYSIZEFRAME = 33, // 0x00000021
            SM_CXMINTRACK = 34, // 0x00000022
            SM_CYMINTRACK = 35, // 0x00000023
            SM_CXDOUBLECLK = 36, // 0x00000024
            SM_CYDOUBLECLK = 37, // 0x00000025
            SM_CXICONSPACING = 38, // 0x00000026
            SM_CYICONSPACING = 39, // 0x00000027
            SM_MENUDROPALIGNMENT = 40, // 0x00000028
            SM_PENWINDOWS = 41, // 0x00000029
            SM_DBCSENABLED = 42, // 0x0000002A
            SM_CMOUSEBUTTONS = 43, // 0x0000002B
            SM_SECURE = 44, // 0x0000002C
            SM_CXEDGE = 45, // 0x0000002D
            SM_CYEDGE = 46, // 0x0000002E
            SM_CXMINSPACING = 47, // 0x0000002F
            SM_CYMINSPACING = 48, // 0x00000030
            SM_CXSMICON = 49, // 0x00000031
            SM_CYSMICON = 50, // 0x00000032
            SM_CYSMCAPTION = 51, // 0x00000033
            SM_CXSMSIZE = 52, // 0x00000034
            SM_CYSMSIZE = 53, // 0x00000035
            SM_CXMENUSIZE = 54, // 0x00000036
            SM_CYMENUSIZE = 55, // 0x00000037
            SM_ARRANGE = 56, // 0x00000038
            SM_CXMINIMIZED = 57, // 0x00000039
            SM_CYMINIMIZED = 58, // 0x0000003A
            SM_CXMAXTRACK = 59, // 0x0000003B
            SM_CYMAXTRACK = 60, // 0x0000003C
            SM_CXMAXIMIZED = 61, // 0x0000003D
            SM_CYMAXIMIZED = 62, // 0x0000003E
            SM_NETWORK = 63, // 0x0000003F
            SM_CLEANBOOT = 67, // 0x00000043
            SM_CXDRAG = 68, // 0x00000044
            SM_CYDRAG = 69, // 0x00000045
            SM_SHOWSOUNDS = 70, // 0x00000046
            SM_CXMENUCHECK = 71, // 0x00000047
            SM_CYMENUCHECK = 72, // 0x00000048
            SM_SLOWMACHINE = 73, // 0x00000049
            SM_MIDEASTENABLED = 74, // 0x0000004A
            SM_MOUSEWHEELPRESENT = 75, // 0x0000004B
            SM_XVIRTUALSCREEN = 76, // 0x0000004C
            SM_YVIRTUALSCREEN = 77, // 0x0000004D
            SM_CXVIRTUALSCREEN = 78, // 0x0000004E
            SM_CYVIRTUALSCREEN = 79, // 0x0000004F
            SM_CMONITORS = 80, // 0x00000050
            SM_SAMEDISPLAYFORMAT = 81, // 0x00000051
            SM_IMMENABLED = 82, // 0x00000052
            SM_CXFOCUSBORDER = 83, // 0x00000053
            SM_CYFOCUSBORDER = 84, // 0x00000054
            SM_TABLETPC = 86, // 0x00000056
            SM_MEDIACENTER = 87, // 0x00000057
            SM_STARTER = 88, // 0x00000058
            SM_SERVERR2 = 89, // 0x00000059
            SM_MOUSEHORIZONTALWHEELPRESENT = 91, // 0x0000005B
            SM_CXPADDEDBORDER = 92, // 0x0000005C
            SM_DIGITIZER = 94, // 0x0000005E
            SM_MAXIMUMTOUCHES = 95, // 0x0000005F
            SM_REMOTESESSION = 4096, // 0x00001000
            SM_SHUTTINGDOWN = 8192, // 0x00002000
            SM_REMOTECONTROL = 8193, // 0x00002001
            SM_CONVERTIBLESLATEMODE = 8195, // 0x00002003
            SM_SYSTEMDOCKED = 8196 // 0x00002004

        } WindowsSystemMetric;

        static_assert_cpp98_obj(sizeof(WindowsSystemMetric) == 4, WindowsSystemMetric);
    } // namespace Enums
} // namespace WindowsHelper
} // namespace OpenSHC
