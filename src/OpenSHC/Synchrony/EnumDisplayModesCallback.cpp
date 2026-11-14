#include "../Synchrony.func.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00467BC0
HRESULT __stdcall Synchrony::EnumDisplayModesCallback(DDSURFACEDESC* displayDesc, LPVOID userParam)
{
    DWORD const width = displayDesc->dwWidth;
    DWORD const height = displayDesc->dwHeight;
    DWORD const bitCount = displayDesc->ddpfPixelFormat.dwRGBBitCount;
    if (bitCount == 15 || bitCount == 16) {
        if (width == 800 && height == 600) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._800x600 = 1;
        } else if (width == 1024 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1024x768 = 1;
        } else if (width == 1024 && height == 600) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1024x600 = 1;
        } else if (width == 1280 && height == 1024) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1280x1024 = 1;
        } else if (width == 1600 && height == 1200) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1600x1200 = 1;
        } else if (width == 1280 && height == 720) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1280x720 = 1;
        } else if (width == 1440 && height == 900) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1440x900 = 1;
        } else if (width == 1920 && height == 1080) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1920x1080 = 1;
        } else if (width == 1920 && height == 1200) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1920x1200 = 1;
        } else if (width == 2560 && height == 1440) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._2560x1440 = 1;
        } else if (width == 2560 && height == 1600) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._2560x1600 = 1;
        } else if (width == 1366 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1366x768 = 1;
        } else if (width == 1360 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1360x768 = 1;
        } else if (width == 1680 && height == 1050) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1680x1050 = 1;
        } else if (width == 1600 && height == 900) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1600x900 = 1;
        }
    }
    return DDENUMRET_OK;
}

}
