
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl RATEGEN_STUB
// ------------------------------
#ifndef RATEGEN_STUB_EXPORT_H
#define RATEGEN_STUB_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (RATEGEN_STUB_HAS_DLL)
#  define RATEGEN_STUB_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && RATEGEN_STUB_HAS_DLL */

#if !defined (RATEGEN_STUB_HAS_DLL)
#  define RATEGEN_STUB_HAS_DLL 1
#endif /* ! RATEGEN_STUB_HAS_DLL */

#if defined (RATEGEN_STUB_HAS_DLL) && (RATEGEN_STUB_HAS_DLL == 1)
#  if defined (RATEGEN_STUB_BUILD_DLL)
#    define RATEGEN_STUB_Export ACE_Proper_Export_Flag
#    define RATEGEN_STUB_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define RATEGEN_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* RATEGEN_STUB_BUILD_DLL */
#    define RATEGEN_STUB_Export ACE_Proper_Import_Flag
#    define RATEGEN_STUB_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define RATEGEN_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* RATEGEN_STUB_BUILD_DLL */
#else /* RATEGEN_STUB_HAS_DLL == 1 */
#  define RATEGEN_STUB_Export
#  define RATEGEN_STUB_SINGLETON_DECLARATION(T)
#  define RATEGEN_STUB_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* RATEGEN_STUB_HAS_DLL == 1 */

// Set RATEGEN_STUB_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (RATEGEN_STUB_NTRACE)
#  if (ACE_NTRACE == 1)
#    define RATEGEN_STUB_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define RATEGEN_STUB_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !RATEGEN_STUB_NTRACE */

#if (RATEGEN_STUB_NTRACE == 1)
#  define RATEGEN_STUB_TRACE(X)
#else /* (RATEGEN_STUB_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define RATEGEN_STUB_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (RATEGEN_STUB_NTRACE == 1) */

#endif /* RATEGEN_STUB_EXPORT_H */

// End of auto generated file.