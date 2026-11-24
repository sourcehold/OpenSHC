/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/Helpers/ScanState.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "WinDef.h"
#include "winnt.h"

namespace OpenSHC {
namespace IO {
    namespace Helpers {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x00000016
        typedef struct ScanState {

            BOOLEnum missionMaps; // 0x00000000 length: 4
            BOOLEnum originalMaps; // 0x00000004 length: 4
            HANDLE handle; // 0x00000008 length: 4
            WORD fatDate; // 0x0000000C length: 2
            undefined1 padding_0xe[2]; // 0x0000000E length: 2
            WORD fatTime; // 0x00000010 length: 2
            BOOLEnum originalMapsScanned; // 0x00000012 length: 4

        } ScanState;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(ScanState) == 22, ScanState);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
