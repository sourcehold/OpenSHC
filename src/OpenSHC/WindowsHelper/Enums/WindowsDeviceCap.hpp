/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/WindowsHelper/Enums/WindowsDeviceCap.hpp'
*/

#pragma once

namespace OpenSHC {
namespace WindowsHelper {
    namespace Enums {
        typedef enum WindowsDeviceCap {

            WDC_DRIVERVERSION = 0, // 0x00000000
            WDC_TECHNOLOGY = 2, // 0x00000002
            WDC_HORZSIZE = 4, // 0x00000004
            WDC_VERTSIZE = 6, // 0x00000006
            WDC_HORZRES = 8, // 0x00000008
            WDC_VERTRES = 10, // 0x0000000A
            WDC_BITSPIXEL = 12, // 0x0000000C
            WDC_PLANES = 14, // 0x0000000E
            WDC_NUMBRUSHES = 16, // 0x00000010
            WDC_NUMPENS = 18, // 0x00000012
            WDC_NUMMARKERS = 20, // 0x00000014
            WDC_NUMFONTS = 22, // 0x00000016
            WDC_NUMCOLORS = 24, // 0x00000018
            WDC_PDEVICESIZE = 26, // 0x0000001A
            WDC_CURVECAPS = 28, // 0x0000001C
            WDC_LINECAPS = 30, // 0x0000001E
            WDC_POLYGONALCAPS = 32, // 0x00000020
            WDC_TEXTCAPS = 34, // 0x00000022
            WDC_CLIPCAPS = 36, // 0x00000024
            WDC_RASTERCAPS = 38, // 0x00000026
            WDC_ASPECTX = 40, // 0x00000028
            WDC_ASPECTY = 42, // 0x0000002A
            WDC_ASPECTXY = 44, // 0x0000002C
            WDC_LOGPIXELSX = 88, // 0x00000058
            WDC_LOGPIXELSY = 90, // 0x0000005A
            WDC_SIZEPALETTE = 104, // 0x00000068
            WDC_NUMRESERVED = 106, // 0x0000006A
            WDC_COLORRES = 108, // 0x0000006C
            WDC_PHYSICALWIDTH = 110, // 0x0000006E
            WDC_PHYSICALHEIGHT = 111, // 0x0000006F
            WDC_PHYSICALOFFSETX = 112, // 0x00000070
            WDC_PHYSICALOFFSETY = 113, // 0x00000071
            WDC_SCALINGFACTORX = 114, // 0x00000072
            WDC_SCALINGFACTORY = 115, // 0x00000073
            WDC_VREFRESH = 116, // 0x00000074
            WDC_DESKTOPVERTRES = 117, // 0x00000075
            WDC_DESKTOPHORZRES = 118, // 0x00000076
            WDC_BLTALIGNMENT = 119, // 0x00000077
            WDC_SHADEBLENDCAPS = 120, // 0x00000078
            WDC_COLORMGMTCAPS = 121 // 0x00000079

        } WindowsDeviceCap;

        static_assert_cpp98_obj(sizeof(WindowsDeviceCap) == 4, WindowsDeviceCap);
    } // namespace Enums
} // namespace WindowsHelper
} // namespace OpenSHC
