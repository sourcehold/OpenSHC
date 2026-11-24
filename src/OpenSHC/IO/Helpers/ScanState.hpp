#pragma once

#include "Windows.h"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {
    namespace Helpers {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        struct ScanState {
            BOOLEnum _missionMaps;
            BOOLEnum _originalMaps;
            HANDLE _handle;
            __declspec(align(4)) WORD fatDate;
            __declspec(align(4)) WORD fatTime;
            BOOLEnum originalMapsScanned;
        };

    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
