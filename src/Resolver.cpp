#include "FunctionResolver.h"
#include "StructResolver.h"

#include "ucp3.h"

#include <sstream>

// TODO?: When in doubt regarding the transition to full exe: Add other logging system.

void StructResolver::initialize(
    bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName)
{
    if (initialized) {
#ifdef OPEN_SHC_EXE
        abort(); // crash silently; if we switch to exe, we should already be sure to never trigger this
#endif

#ifdef OPEN_SHC_DLL
        std::ostringstream oss;
        oss << "Abort execution, since address '" << gameAddress << "' was resolved more then once.";
        ucp_log(Verbosity_FATAL, oss.str().c_str());
#endif
        return;
    }
    initialized = true;

#ifdef OPEN_SHC_DLL
    if (ucp_logLevel() < Verbosity_INFO) {
        return;
    }
    std::ostringstream oss;
    if (isImplemented) {
        oss << "Implemented '" << (void*)gameAddress << "' at address '" << funcPtr << "' as a '" << funcName;
    } else {
        oss << "Use '" << (void*)gameAddress << "' as a '" << funcName;
    }
    ucp_log(Verbosity_INFO, oss.str().c_str());
#endif
}

void FunctionResolver::initialize(
    bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName)
{
    if (initialized) {
#ifdef OPEN_SHC_EXE
        abort(); // crash silently; if we switch to exe, we should already be sure to never trigger this
#endif

#ifdef OPEN_SHC_DLL
        std::ostringstream oss;
        oss << "Abort execution, since address '" << gameAddress << "' was resolved more then once.";
        ucp_log(Verbosity_FATAL, oss.str().c_str());
#endif
        return;
    }
    initialized = true;

#ifdef OPEN_SHC_DLL
    if (isImplemented) {
        // TODO: hooking code
    }

    if (ucp_logLevel() < Verbosity_INFO) {
        return;
    }
    std::ostringstream oss;
    if (isImplemented) {
        oss << "Implemented '" << (void*)gameAddress << "' at address '" << funcPtr << "' as '" << funcName;
    } else {
        oss << "Use '" << (void*)gameAddress << "' as '" << funcName;
    }
    ucp_log(Verbosity_INFO, oss.str().c_str());
#endif
}
