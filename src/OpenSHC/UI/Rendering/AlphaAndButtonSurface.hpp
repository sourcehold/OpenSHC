/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering/AlphaAndButtonSurface.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTargetInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000010
        class AlphaAndButtonSurface {
        public:
            ushort* surfacePtr; // 0x00000000 length: 4
            dword dim1_intMinimal350_1; // 0x00000004 length: 4
            dword dim2_intMinimal350_2; // 0x00000008 length: 4
            int currentImageWidth; // 0x0000000C length: 4

        private:
            AlphaAndButtonSurface(AlphaAndButtonSurface const&);
            void operator=(AlphaAndButtonSurface const&);

            AlphaAndButtonSurface();
            ~AlphaAndButtonSurface();

        public:
            // Constructor
            AlphaAndButtonSurface* Constructor_AlphaAndButtonSurface();

            void renderNonInteractingButtonBackground(int blendStrength);

            void freeMemory();

            void prepareButtonAndAlphaSurface();

            BOOLEnum isMouseOnButtonImageUnk();

            void FUN_00463270(int buildingIndex);

            BOOLEnum openBuildingStatusMenuForBuildingID(int buildingID);

            BOOLEnum FUN_00463a00(int unitIndex);

            void renderBasicButton(int reverseOrBlendStrength, RenderTargetInt renderSurface);
        };

        static_assert_cpp98_obj(sizeof(AlphaAndButtonSurface) == 16, AlphaAndButtonSurface);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(AlphaAndButtonSurface, false, Address::SHC_3BB0A8C1_0x00F2C7BC)
        pDAT_AlphaAndButtonSurface;

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
