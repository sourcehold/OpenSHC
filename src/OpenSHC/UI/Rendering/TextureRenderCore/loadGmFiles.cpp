#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_LoadingBarProgress.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00455C60
        void TextureRenderCore::loadGmFiles(char* fileNameArray)
        {
            // Up to 240 names of 1000 bytes; the loading bar gets one step per file plus one
            // A found flag, not n + 1 after a plain loop (n + 1: quick_diff 0.9538 -> 0.9385)
            int loadingBarSteps = 0;
            BOOLEnum found = FALSE;
            for (char* fileName = fileNameArray; loadingBarSteps < 240; fileName += 1000) {
                ++loadingBarSteps;
                // "null" ends the list
                if (!strcmp(fileName, s_null_005a506c)) {
                    found = TRUE;
                    break;
                }
            }
            if (!found) {
                ++loadingBarSteps;
            }
            DAT_LoadingBarProgress::instance = loadingBarSteps;
            this->gmNumberOfProcessedPictures = 1;
            this->gmFileID = 1;
            this->gmSizeOfProcessedPictures_0x44 = 0;
            // The count steps first (++i in the for header: quick_diff 0.9538 -> 0.9385); the names are walked, as
            // the original steps a register and then the parameter's slot (indexing: quick_diff 0.9538 -> 0.7313)
            for (int i = 0; i < 240;) {
                ++i;
                // "null" ends the list
                if (!strcmp(fileNameArray, s_null_005a506c)) {
                    break;
                }
                GMFirstPictureIndex::instance[this->gmFileID] = this->gmNumberOfProcessedPictures;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGMFile, this)(
                    (GmID)this->gmFileID, fileNameArray);
                fileNameArray += 1000;
                this->gmNumberOfProcessedPictures
                    += this->gmFileHeaderColorpaletteArray[this->gmFileID].numberOfPicturesInFile;
                ++this->gmFileID;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadCampaignMapGfxUnk, this)();
            // The font's .gm1 holds five font sets of the same size
            DAT_TextManagerObject::instance.sizeOfOneFontSet_0x3c
                = this->gmFileHeaderColorpaletteArray[OpenSHC::IO::Graphics::GID_FONT_STRONGHOLD_AA]
                      .numberOfPicturesInFile
                / 5;
        }

    }
}
}
