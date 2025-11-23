#pragma once

#ifdef __cplusplus
#ifdef UCPDLL_EXPORTS
#define UCP3_DLL  extern "C"   __declspec(dllexport)
#else
#define UCP3_DLL  extern "C"   __declspec(dllimport)
#endif
#else
#ifdef UCPDLL_EXPORTS
#define UCP3_DLL  extern  __declspec(dllexport)
#else
#define UCP3_DLL  extern  __declspec(dllimport)
#endif
#endif

#include <stdio.h>

/**

	When logging messages, set the log level with this enum

	Use Verbosity_1 for DEBUG-level messages

	NOTE: this enum was copy-pasted from loguru.hpp
*/
typedef enum
{
	// Used to mark an invalid verbosity. Do not log to this level.
	Verbosity_INVALID = -10, // Never do LOG_F(INVALID)

	// You may use Verbosity_OFF on g_stderr_verbosity, but for nothing else!
	Verbosity_OFF = -9, // Never do LOG_F(OFF)

	// Prefer to use ABORT_F or ABORT_S over LOG_F(FATAL) or LOG_S(FATAL).
	Verbosity_FATAL = -3,
	Verbosity_ERROR = -2,
	Verbosity_WARNING = -1,

	// Normal messages. By default written to stderr.
	Verbosity_INFO = 0,

	// Same as Verbosity_INFO in every way.
	Verbosity_0 = 0,

	// Verbosity levels 1-9 are generally not written to stderr, but are written to file.
	// Verbosity 1 is a DEBUG verbosity that is written to the console
	Verbosity_1 = +1,
	// Verbosity 2 and above is meant for DEBUG messages that should not be written to the console
	Verbosity_2 = +2,
	Verbosity_3 = +3,
	Verbosity_4 = +4,
	Verbosity_5 = +5,
	Verbosity_6 = +6,
	Verbosity_7 = +7,
	Verbosity_8 = +8,
	Verbosity_9 = +9,

	// Do not use higher verbosity levels, as that will make grepping log files harder.
	Verbosity_MAX = +9,
} ucp_NamedVerbosity;

/**
	Call this function to log a message to the ucp console, and to log files
*/
UCP3_DLL void ucp_log(ucp_NamedVerbosity logLevel, const char * logMessage);


UCP3_DLL int ucp_logLevel();


/**

	
	If fails, returns NULL and sets the LastErrorMessage;
*/
UCP3_DLL FILE* ucp_getFilePointer(const char* path, const char* mode);
/**
	Stronghold Crusader uses _open
*/
UCP3_DLL int ucp_getFileDescriptor(const char* path, const int mode, const int perm);

UCP3_DLL int ucp_getFileSize(const char* filename);
UCP3_DLL int ucp_getFileContents(const char* filename, void* buffer, const int size);


/**
	extensionName should only be the name of the extension, not the version, example. For extension example-0.0.1 (example version 0.0.1), extensionName "example" should be used.

	path should be the path inside the extension, excluding the extension name, e.g. for example-0.0.1/definition.yml, use "definition.yml"

	Only a single version of an extension can be loaded at once, thus the function is deterministic even while excluding the version information

	If fails, returns NULL and sets the LastErrorMessage;
*/
UCP3_DLL FILE* ucp_getFilePointerForFileInExtension(const char * extensionName, const char* path, const char* mode);
/**
	Stronghold Crusader uses _open
*/
UCP3_DLL int ucp_getFileDescriptorForFileInExtension(const char* extensionName, const char* path, const int mode);

UCP3_DLL int ucp_getFileSizeForFileInExtension(const char* extensionName, const char* path);
UCP3_DLL int ucp_getFileContentsForFileInExtension(const char* extensionName, const char* path, void* buffer, const int size);

/**
	
	Gets the last error message;

*/
UCP3_DLL const char * ucp_lastErrorMessage();

/**
	moduleName should only be the name of the module, not the version, example. For extension example-0.0.1 (example version 0.0.1), moduleName "example" should be used.

	Only a single version of an extension can be loaded at once, thus the function is deterministic even while excluding the version information

	returns a FARPROC
*/
UCP3_DLL void * ucp_getProcAddressFromLibraryInModule(const char* moduleName, const char* library, const char* name);

/**
*
	IMPORTANT note for extension developers: do not run this function in your code!

	This function is reserved for the custom binkw32.dll that ucp ships to end-users.
	This binkw32.dll is responsible for initializing ucp at game runtime.

*/
UCP3_DLL void ucp_initialize();