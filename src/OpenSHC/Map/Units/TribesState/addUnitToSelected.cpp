#include "OpenSHC/Map/Units/TribesState.func.hpp"



#include "OpenSHC/Globals/DAT_UnitSelectionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
namespace Units {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00522520
void TribesState::addUnitToSelected(uint unitID)

{
uint uVar1;

uVar1 = unitID &0x8000000f;
if ((int)uVar1 < 0) {
uVar1 = (uVar1 - 1 | 0xfffffff0) + 1;
}
*(ushort *)
(DAT_UnitsState::instance.selectedUnitsBitFlags + ((int)(unitID + ((int)unitID >> 0x1f &0xfU)) >> 4) * 2)
= *(ushort *)
(DAT_UnitsState::instance.selectedUnitsBitFlags +
((int)(unitID + ((int)unitID >> 0x1f &0xfU)) >> 4) * 2) |
DAT_UnitSelectionDefinedData::instance.BitMaskHelper[uVar1];
return;
}


}
}
}