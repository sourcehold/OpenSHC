#include "OpenSHC/Global.func.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0046F570
byte Global::TestOSVersion()
{
    byte isSupported = 0;
    OSVERSIONINFOEXA versionInfo;
    memset(&versionInfo, 0, sizeof(versionInfo));
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
    GetVersionExA((OSVERSIONINFOA*)&versionInfo);
    if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && versionInfo.dwMajorVersion > 4) {
        if (versionInfo.dwMajorVersion == 6) {
            if (versionInfo.dwMinorVersion >= 2) {
                isSupported = 1;
            }
        } else if (versionInfo.dwMajorVersion > 6) {
            isSupported = 1;
        }
    }
    return isSupported;
}

}
