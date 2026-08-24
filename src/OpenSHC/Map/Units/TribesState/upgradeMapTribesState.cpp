#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/IO/PackagedFileMagicNum.hpp"
#include "OpenSHC/Map/Version.func.hpp"





namespace OpenSHC {
namespace Map {
namespace Units {

using OpenSHC::IO::PackagedFileMagicNum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00526370
void TribesState::upgradeMapTribesState(PackagedFileMagicNum receivedMapVersion,PackagedFileMagicNum packagerMapVersion)

{
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_Unknown1)();
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_Unknown2)();
if ((receivedMapVersion != packagerMapVersion) && ((int)receivedMapVersion < 0x8e)) {
MACRO_CALL(OpenSHC::Map::Version_Func::UpgradeMapTribesStateVersionTo_142)();
}
return;
}


}
}
}