// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../IO.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Version.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004D5180
void IO::WriteSkMasters2()
{
    if (DAT_SkMasters2Data_Count::instance < 1) {
        return;
    }

    char path[1000];
    // NOTE: Direct use to support copy elision
    strcpy(path, DAT_ResourceManager::instance.paths_getDocumentsFolderString(true).c_str());
    strcat(path, s_skmasters2_dat_005aad80);

    FILE* _File = MACRO_CALL(OpenSHC::OS_Func::_fopen)(path, s_wb_005a5510);
    if (!_File) {
        return;
    }

    MACRO_CALL(OpenSHC::OS_Func::_fwrite)(
        DAT_SkMasters2Data_Version::ptr, sizeof(DAT_SkMasters2Data_Version::instance), 1, _File);
    MACRO_CALL(OpenSHC::OS_Func::_fwrite)(
        DAT_SkMasters2Data_Count::ptr, sizeof(DAT_SkMasters2Data_Count::instance), 1, _File);
    MACRO_CALL(OpenSHC::OS_Func::_fwrite)(DAT_SkMasters2DataArray::instance,
        sizeof(DAT_SkMasters2DataArray::instance[0]), DAT_SkMasters2Data_Count::instance, _File);
    MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
}

}
