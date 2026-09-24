#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B2F0
    void GameCore::setViewOnExitUnk() { this->currentMenuViewType = ((MenuViewType)2); }

}
}
