#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmImageType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PictureNumToGmIDArray_UNUSED.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004559B0
        void TextureRenderCore::loadGMFile(GmID gmID, char* gmFileName)
        {
            // keep the window responsive while the files load
            MSG message;
            if (PeekMessageA(&message, NULL, 0, 0, 0) && GetMessageA(&message, NULL, 0, 0)) {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }
            BOOLEnum const flag = this->unknownSfxAndGmRelatedFlag;
            int totalSize = 0;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->gmFileHeaderColorpaletteArray[gmID]), 0, &this->gmFileHeaderColorpaletteArray[gmID]);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                1000, 0, this->gmFileNameArray_UNUSEDUnk_0x13179c[gmID]);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                strlen(gmFileName), gmFileName, this->gmFileNameArray_UNUSEDUnk_0x13179c[gmID]);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_GM, this->gmFileNameArray_UNUSEDUnk_0x13179c[gmID]);

            // the header, the offsets, sizes and headers of its pictures, then their data
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readFirstPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(&this->gmFileHeaderColorpaletteArray[gmID],
                sizeof(this->gmFileHeaderColorpaletteArray[gmID]), (char*)s_gm1_005a5068);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(&DAT_GMImageOffsets::instance[this->gmNumberOfProcessedPictures],
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile * 4, (char*)s_gm1_005a5068);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(&DAT_GMImageSizes::instance[this->gmNumberOfProcessedPictures],
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile * 4, (char*)s_gm1_005a5068);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(&DAT_GMImageHeaders::instance.imh[this->gmNumberOfProcessedPictures],
                this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile * 16, (char*)s_gm1_005a5068);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::readNextPartOfCurrentResourceIntoMemory,
                DAT_ResourceManager::ptr)(this->gmAndGfxImageDataBuffer,
                this->gmFileHeaderColorpaletteArray[gmID].dataSize, (char*)s_gm1_005a5068);
            if (this->gmFileHeaderColorpaletteArray[gmID].ImageType == OpenSHC::IO::Graphics::GIT_Animation) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::transformGmColorTableFromRGB555To565IfRequired,
                    this)(gmID);
            }

            // copy each picture's data behind the ones processed so far; a picture that shares another one's data
            // points at it instead
            int offset = DAT_GMImageOffsets::instance[this->gmNumberOfProcessedPictures];
            for (int picture = this->gmNumberOfProcessedPictures; picture
                < this->gmFileHeaderColorpaletteArray[gmID].numberOfPicturesInFile + this->gmNumberOfProcessedPictures;
                ++picture) {
                DAT_PictureNumToGmIDArray_UNUSED::instance[picture] = gmID;
                if ((flag && DAT_GMImageHeaders::instance.imh[picture].animatedColor != 0)
                    || (DAT_GMImageHeaders::instance.imh[picture].animatedColor & 4) != 0) {
                    if ((DAT_GMImageHeaders::instance.imh[picture].animatedColor & 4) != 0) {
                        DAT_GMImageOffsets::instance[picture] = DAT_GMImageOffsets::instance[picture - 1];
                    } else {
                        DAT_GMImageOffsets::instance[picture] = DAT_GMImageOffsets::instance
                            [DAT_GMImageHeaders::instance.imh[picture].alternativeImageIndexUnk + picture];
                    }
                    DAT_GMImageSizes::instance[picture]
                        = DAT_GMImageSizes::instance[DAT_GMImageHeaders::instance.imh[picture].alternativeImageIndexUnk
                            + picture];
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
                        DAT_GMImageSizes::instance[picture],
                        this->gmAndGfxImageDataBuffer + DAT_GMImageOffsets::instance[picture],
                        this->gmProcessedImageData + this->gmSizeOfProcessedPictures_0x44 + offset);
                    DAT_GMImageOffsets::instance[picture] = this->gmSizeOfProcessedPictures_0x44 + offset;
                    totalSize += DAT_GMImageSizes::instance[picture];
                    offset += DAT_GMImageSizes::instance[picture];
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::adaptGmColorsToRGB565IfRequired,
                        this)(gmID, picture);
                }
            }
            this->gmSizeOfProcessedPictures_0x44 += totalSize;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawLoadingBarUnk, this)(
                gmID, DAT_LoadingBarProgress::instance + 180);
        }

    }
}
}
