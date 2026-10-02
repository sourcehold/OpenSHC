#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Rendering::ColorMode;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          This function loads for example the menu edges. --TheRedDaemon   decompilerscript: committed: 2025-01-30
          21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004547C0
        int TextureRenderCore::loadGfxAtBufferEnd(char* fileName)
        {
            void* pvVar1;
            size_t _size;
            BOOLEnum _success;
            void* _destination;
            int _backwardsBufferSize;
            /*
              Some address calculations are bugged. I assume normal numbers are mistaken as   addresses, which causes
              issues. -TheRedDaemon
             */
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GFX, (char const*)((int)(fileName)));
            _size = MACRO_CALL_MEMBER(
                OpenSHC::IO::ResourceManager_Func::getCurrentResourceSize, DAT_ResourceManager::ptr)();
            pvVar1 = this->gmAndGfxImageDataBuffer;
            _backwardsBufferSize
                = -_size - this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer;
            _destination = (void*)((int)this->gmAndGfxImageDataBuffer + (int)DAT_GameState::ptr + _backwardsBufferSize
                + 0x3c858);
            _success = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readCurrentResourceIntoDestination,
                DAT_ResourceManager::ptr)(_destination, _size);
            if (_success == FALSE) {
                return -1;
            }
            if (DAT_WindowAndDirectDraw::instance.colorBitMode == OpenSHC::Rendering::RGB_565) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::transformTgxFromRGB555ToRGB565, this)(
                    (ushort*)((int)pvVar1 + (int)DAT_GameState::ptr + _backwardsBufferSize + 0x3c860),
                    DAT_ResourceManager::instance.loadPositionInCurrentResource + -8);
            }
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].offsetInBuffer
                = (0x1167910 - this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer)
                - _size;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850 + -1].backwardsOffsetInBuffer
                = this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer
                + DAT_ResourceManager::instance.loadPositionInCurrentResource;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].backwardsOffsetInBuffer
                = this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850 + -1].backwardsOffsetInBuffer;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].width = *(int*)_destination;
            this->loadedGfxArray[this->backwardsLoadedGfxIndex_0x16C850].height
                = *(int*)((int)pvVar1 + (int)DAT_GameState::ptr + _backwardsBufferSize + 0x3c85c);
            _backwardsBufferSize = this->backwardsLoadedGfxIndex_0x16C850;
            this->backwardsLoadedGfxIndex_0x16C850 = this->backwardsLoadedGfxIndex_0x16C850 + -1;
            return _backwardsBufferSize;
        }

    }
}
}
