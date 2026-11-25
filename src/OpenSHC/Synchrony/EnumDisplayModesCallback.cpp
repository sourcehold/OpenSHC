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
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._800x600 = TRUE;
        } else if (width == 1024 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1024x768 = TRUE;
        } else if (width == 1024 && height == 600) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1024x600 = TRUE;
        } else if (width == 1280 && height == 1024) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1280x1024 = TRUE;
        } else if (width == 1600 && height == 1200) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1600x1200 = TRUE;
        } else if (width == 1280 && height == 720) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1280x720 = TRUE;
        } else if (width == 1440 && height == 900) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1440x900 = TRUE;
        } else if (width == 1920 && height == 1080) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1920x1080 = TRUE;
        } else if (width == 1920 && height == 1200) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1920x1200 = TRUE;
        } else if (width == 2560 && height == 1440) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._2560x1440 = TRUE;
        } else if (width == 2560 && height == 1600) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._2560x1600 = TRUE;
        } else if (width == 1366 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1366x768 = TRUE;
        } else if (width == 1360 && height == 768) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1360x768 = TRUE;
        } else if (width == 1680 && height == 1050) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1680x1050 = TRUE;
        } else if (width == 1600 && height == 900) {
            DAT_WindowAndDirectDraw::instance.resolutionSupported_0x68.fields._1600x900 = TRUE;
        }
    }
    return DDENUMRET_OK;
}

}
