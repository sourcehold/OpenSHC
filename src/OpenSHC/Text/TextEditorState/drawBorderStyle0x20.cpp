#include "../TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_00df2964.hpp"
#include "OpenSHC/Globals/DAT_00df296c.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/INT_00df2968.hpp"
#include "OpenSHC/Globals/INT_00df2970.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D6C0
    void TextEditorState::drawBorderStyle0x20(int dialogX, int dialogY, int dialogWidth, int dialogHeight)
    {
        this->dialogX = dialogX;
        this->dialogY = dialogY;
        this->dialogWidth = dialogWidth;
        this->dialogHeight = dialogHeight;

        int const contentX = this->dialogX + DAT_00df2964::instance;
        int const contentY = this->dialogY + DAT_00df296c::instance;
        int const contentHeight = this->dialogHeight - INT_00df2970::instance;
        int const contentWidth = this->dialogWidth - INT_00df2968::instance;
        this->dialogContentX = contentX;
        this->dialogContentY = contentY;
        this->dialogContentWidth = contentWidth;
        this->dialogContentHeight = contentHeight;

        this->helpContentScrollX = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
        this->helpContentScrollY = DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
    }

}
}
