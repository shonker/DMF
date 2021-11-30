/*++

    Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    DmfTrace.h

Abstract:

    Header file for the debug tracing related function definitions and macros.

Environment:

    Kernel-mode Driver Framework
    User-mode Driver Framework

--*/

#pragma once

#define NO_DMF_USE_DBGPRINT
#if defined(DMF_USE_DBGPRINT)
#define WPP_BIT_0x00000001  1
#if defined(DMF_INCLUDE_TMH)
#undef DMF_INCLUDE_TMH
#endif
#endif

// TODO: DMF Client Driver Writer:
//
// Copy lines 52 through 80 into your Trace.h file.
//

// From DmfTrace.h.
// ----------------
//

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                              \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                             \
    (WPP_LEVEL_ENABLED(flag) &&                                         \
     WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(lvl,flags) \
           WPP_LEVEL_LOGGER(flags)

#define WPP_LEVEL_FLAGS_ENABLED(lvl, flags) \
           (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= lvl)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// USEPREFIX and USESUFFIX strip all trailing whitespace, so we need to surround
// FuncExit messages with brackets 
//
// begin_wpp config
// FUNC Trace{FLAG=MYDRIVER_ALL_INFO}(LEVEL, MSG, ...);
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// FUNC FuncEntry{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS);
// FUNC FuncEntryArguments{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS, MSG, ...);
// FUNC FuncExit{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS, MSG, ...);
// FUNC FuncExitVoid{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS);
// FUNC TraceError{LEVEL=TRACE_LEVEL_ERROR}(FLAGS, MSG, ...);
// FUNC TraceInformation{LEVEL=TRACE_LEVEL_INFORMATION}(FLAGS, MSG, ...);
// FUNC TraceVerbose{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS, MSG, ...);
// FUNC FuncExitNoReturn{LEVEL=TRACE_LEVEL_VERBOSE}(FLAGS);
// USEPREFIX(FuncEntry, "%!STDPREFIX! [%!FUNC!] --> Entry");
// USEPREFIX(FuncEntryArguments, "%!STDPREFIX! [%!FUNC!] --> Entry <");
// USEPREFIX(FuncExit, "%!STDPREFIX! [%!FUNC!] <-- Exit <");
// USESUFFIX(FuncExit, ">");
// USEPREFIX(FuncExitVoid, "%!STDPREFIX! [%!FUNC!] <-- Exit");
// USEPREFIX(TraceError, "%!STDPREFIX! [%!FUNC!] ERROR:");
// USEPREFIX(TraceEvents, "%!STDPREFIX! [%!FUNC!] ");
// USEPREFIX(TraceInformation, "%!STDPREFIX! [%!FUNC!] ");
// USEPREFIX(TraceVerbose, "%!STDPREFIX! [%!FUNC!] ");
// USEPREFIX(FuncExitNoReturn, "%!STDPREFIX! [%!FUNC!] <--");
// end_wpp

// Levels.
//
#define TRACE_LEVEL_NONE        0
#define TRACE_LEVEL_CRITICAL    1
#define TRACE_LEVEL_FATAL       1
#define TRACE_LEVEL_ERROR       2
#define TRACE_LEVEL_WARNING     3
#define TRACE_LEVEL_INFORMATION 4
#define TRACE_LEVEL_VERBOSE     5
#define TRACE_LEVEL_RESERVED6   6
#define TRACE_LEVEL_RESERVED7   7
#define TRACE_LEVEL_RESERVED8   8
#define TRACE_LEVEL_RESERVED9   9

// Flags.
//
#define DMF_TRACE               0x00000001

#if !defined(DMF_WDF_DRIVER) || defined(DMF_USE_DBGPRINT)

#if defined(__cplusplus)
extern "C"
{
#endif // defined(__cplusplus)

VOID
TraceEvents(
    _In_ ULONG DebugPrintLevel,
    _In_ ULONG DebugPrintFlag,
    _Printf_format_string_ _In_ CHAR* DebugMessage,
    ...
    );

VOID
TraceInformation(
    _In_ ULONG DebugPrintFlag,
    _Printf_format_string_ _In_ CHAR* DebugMessage,
    ...
    );

VOID
TraceVerbose(
    _In_ ULONG DebugPrintFlag,
    _Printf_format_string_ _In_ CHAR* DebugMessage,
    ...
    );

VOID
TraceError(
    _In_ ULONG DebugPrintFlag,
    _Printf_format_string_ _In_ CHAR* DebugMessage,
    ...
    );

VOID
FuncEntryArguments(
    _In_ ULONG DebugPrintFlag,
    _Printf_format_string_ _In_ CHAR* DebugMessage,
    ...
    );

#define Trace TraceEvents
#define FuncExit FuncEntryArguments

// TODO:
//
#define FuncEntry(X) TraceVerbose(X, "->")
#define FuncExitNoReturn(X) TraceVerbose(X, "<-")
#define FuncExitVoid FuncExitNoReturn

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif // !defined(DMF_WDF_DRIVER) || defined(DMF_USE_DBGPRINT)

// eof: DmfTrace.h
//
