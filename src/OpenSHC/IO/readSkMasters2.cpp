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

// FUNCTION: STRONGHOLDCRUSADER 0x004D5010
void IO::readSkMasters2()
{
    DAT_SkMasters2Data_Version::instance = 3.0;
    DAT_SkMasters2Data_Count::instance = 0;

    char path[1000];
    // NOTE: Direct use to support copy elision
    strcpy(path, DAT_ResourceManager::instance.paths_getDocumentsFolderString(true).c_str());
    strcat(path, s_skmasters2_dat_005aad80);

    FILE* file = MACRO_CALL(OpenSHC::OS_Func::_fopen)(path, s_rb_005a4e18);
    if (!file) {
        return;
    }

    float _version;
    MACRO_CALL(OpenSHC::OS_Func::_fread)(&_version, sizeof(_version), 1, file);
    if (_version != 3.0) {
        MACRO_CALL(OpenSHC::OS_Func::_fclose)(file);
        return;
    }

    int _count;
    MACRO_CALL(OpenSHC::OS_Func::_fread)(&_count, sizeof(_count), 1, file);
    if (_count < 1) {
        MACRO_CALL(OpenSHC::OS_Func::_fclose)(file);
        return;
    }

    DAT_SkMasters2Data_Count::instance = _count;
    MACRO_CALL(OpenSHC::OS_Func::_fread)(
        DAT_SkMasters2DataArray::instance, sizeof(DAT_SkMasters2DataArray::instance[0]), _count, file);
    MACRO_CALL(OpenSHC::OS_Func::_fclose)(file);
}

}
