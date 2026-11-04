#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x00462FF0
        void AlphaAndButtonSurface::prepareButtonAndAlphaSurface()
        {
            // The surface has to hold the largest image of any button state, and at least 350x350.
            int maxWidth = 0;
            int maxHeight = 0;
            for (int button = 0; button < 650; ++button) {
                int const stateCount
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[button].numOfAdditionalIconStates_0x8 + 1;
                for (int state = 0; state < stateCount; ++state) {
                    GmIDInt const gmID = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[button].gmId_0x0;
                    if (gmID == 0) {
                        continue;
                    }
                    int const pictureInGm = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[button].pictureInGm_0x4;
                    if (pictureInGm == 0) {
                        continue;
                    }
                    int const imageIndex = GMFirstPictureIndex::instance[gmID] + pictureInGm + state - 1;
                    int const width = DAT_GMImageHeaders::instance.imh[imageIndex].width;
                    if (width > maxWidth) {
                        maxWidth = width;
                    }
                    int const height = DAT_GMImageHeaders::instance.imh[imageIndex].height;
                    if (height > maxHeight) {
                        maxHeight = height;
                    }
                }
            }
            if (maxWidth < 350) {
                maxWidth = 350;
            }
            if (maxHeight < 350) {
                maxHeight = 350;
            }
            this->dim2_intMinimal350_2 = maxHeight;
            this->dim1_intMinimal350_1 = maxWidth;
            this->surfacePtr = (ushort*)MACRO_CALL(OpenSHC::OS_Func::_malloc)(maxHeight * maxWidth * sizeof(ushort));
        }

    }
}
}
