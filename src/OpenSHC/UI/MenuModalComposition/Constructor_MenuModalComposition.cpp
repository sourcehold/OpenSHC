#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004A9E60
    MenuModalComposition* MenuModalComposition::Constructor_MenuModalComposition(int slot)
    {
        this->slot = slot;
        this->activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
        return this;
    }

}
}
