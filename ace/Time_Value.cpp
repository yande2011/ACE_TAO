#include "ace/Time_Value.h"

ACE_RCSID (ace,
           Time_Value,
           "$Id$")


#if !defined (__ACE_INLINE__)
#include "ace/Time_Value.inl"
#endif /* __ACE_INLINE__ */

#if !defined(ACE_LACKS_NUMERIC_LIMITS)
// some platforms pollute the namespace by defining max() and min() macros
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#include <limits>
#endif /* ACE_LACKS_NUMERIC_LIMITS */


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Static constant representing `zero-time'.
// Note: this object requires static construction.
const ACE_Time_Value ACE_Time_Value::zero;

// Constant for maximum time representable.  Note that this time
// is not intended for use with select () or other calls that may
// have *their own* implementation-specific maximum time representations.
// Its primary use is in time computations such as those used by the
// dynamic subpriority strategies in the ACE_Dynamic_Message_Queue class.
// Note: this object requires static construction.
// Note: on platforms without std::numeric_limits<>, we assume time_t is
// a long, the historical type used for time.
const ACE_Time_Value ACE_Time_Value::max_time (
#if !defined(ACE_LACKS_NUMERIC_LIMITS)
                                               std::numeric_limits<time_t>::max (),
#else
                                               LONG_MAX,
#endif
                                               ACE_ONE_SECOND_IN_USECS - 1);

ACE_ALLOC_HOOK_DEFINE (ACE_Time_Value)

// Increment microseconds (the only reason this is here is to allow
// the use of ACE_Atomic_Op with ACE_Time_Value).

ACE_Time_Value
ACE_Time_Value::operator ++ (int)
{
  // ACE_OS_TRACE ("ACE_Time_Value::operator ++ (int)");
  ACE_Time_Value tv (*this);
  ++*this;
  return tv;
}

ACE_Time_Value &
ACE_Time_Value::operator ++ (void)
{
  // ACE_OS_TRACE ("ACE_Time_Value::operator ++ (void)");
  this->usec (this->usec () + 1);
  this->normalize ();
  return *this;
}

// Decrement microseconds (the only reason this is here is / to allow
// the use of ACE_Atomic_Op with ACE_Time_Value).

ACE_Time_Value
ACE_Time_Value::operator -- (int)
{
  // ACE_OS_TRACE ("ACE_Time_Value::operator -- (int)");
  ACE_Time_Value tv (*this);
  --*this;
  return tv;
}

ACE_Time_Value &
ACE_Time_Value::operator -- (void)
{
  // ACE_OS_TRACE ("ACE_Time_Value::operator -- (void)");
  this->usec (this->usec () - 1);
  this->normalize ();
  return *this;
}

#if defined (ACE_WIN32)
// Static constant to remove time skew between FILETIME and POSIX
// time.  POSIX and Win32 use different epochs (Jan. 1, 1970 v.s.
// Jan. 1, 1601).  The following constant defines the difference
// in 100ns ticks.
//
// In the beginning (Jan. 1, 1601), there was no time and no computer.
// And Bill said: "Let there be time," and there was time....
# if defined (ACE_LACKS_LONGLONG_T)
const ACE_U_LongLong ACE_Time_Value::FILETIME_to_timval_skew =
ACE_U_LongLong (0xd53e8000, 0x19db1de);
# else
const DWORDLONG ACE_Time_Value::FILETIME_to_timval_skew =
ACE_INT64_LITERAL (0x19db1ded53e8000);
# endif

//  Initializes the ACE_Time_Value object from a Win32 FILETIME

ACE_Time_Value::ACE_Time_Value (const FILETIME &file_time)
{
  // // ACE_OS_TRACE ("ACE_Time_Value::ACE_Time_Value");
  this->set (file_time);
}

void ACE_Time_Value::set (const FILETIME &file_time)
{
  //  Initializes the ACE_Time_Value object from a Win32 FILETIME
#if defined (ACE_LACKS_LONGLONG_T)
  ACE_U_LongLong LL_100ns(file_time.dwLowDateTime, file_time.dwHighDateTime);
  LL_100ns -= ACE_Time_Value::FILETIME_to_timval_skew;
  // Convert 100ns units to seconds;
  this->tv_.tv_sec = (long) (LL_100ns / ((double) (10000 * 1000)));
  // Convert remainder to microseconds;
  this->tv_.tv_usec = (suseconds_t)((LL_100ns % ((ACE_UINT32)(10000 * 1000))) / 10);
#else
  // Don't use a struct initializer, gcc don't like it.
  ULARGE_INTEGER _100ns;
  _100ns.LowPart = file_time.dwLowDateTime;
  _100ns.HighPart = file_time.dwHighDateTime;

  _100ns.QuadPart -= ACE_Time_Value::FILETIME_to_timval_skew;

  // Convert 100ns units to seconds;
  this->tv_.tv_sec = (long) (_100ns.QuadPart / (10000 * 1000));
  // Convert remainder to microseconds;
  this->tv_.tv_usec = (suseconds_t) ((_100ns.QuadPart % (10000 * 1000)) / 10);
#endif // ACE_LACKS_LONGLONG_T
  this->normalize ();
}

// Returns the value of the object as a Win32 FILETIME.

ACE_Time_Value::operator FILETIME () const
{
  FILETIME file_time;
  // ACE_OS_TRACE ("ACE_Time_Value::operator FILETIME");

#if defined (ACE_LACKS_LONGLONG_T)
  ACE_U_LongLong LL_sec(this->tv_.tv_sec);
  ACE_U_LongLong LL_usec(this->tv_.tv_usec);
  ACE_U_LongLong LL_100ns = LL_sec * (ACE_UINT32)(10000 * 1000) +
                            LL_usec * (ACE_UINT32)10 +
                            ACE_Time_Value::FILETIME_to_timval_skew;
  file_time.dwLowDateTime = LL_100ns.lo();
  file_time.dwHighDateTime = LL_100ns.hi();
#else
  ULARGE_INTEGER _100ns;
  _100ns.QuadPart = (((DWORDLONG) this->tv_.tv_sec * (10000 * 1000) +
                     this->tv_.tv_usec * 10) +
                     ACE_Time_Value::FILETIME_to_timval_skew);

  file_time.dwLowDateTime = _100ns.LowPart;
  file_time.dwHighDateTime = _100ns.HighPart;
#endif //ACE_LACKS_LONGLONG_T

  return file_time;
}

#endif /* ACE_WIN32 */

void
ACE_Time_Value::dump (void) const
{
#if defined (ACE_HAS_DUMP)
  // ACE_OS_TRACE ("ACE_Time_Value::dump");
#if 0
  ACE_DEBUG ((LM_DEBUG, ACE_BEGIN_DUMP, this));
  ACE_DEBUG ((LM_DEBUG, ACE_LIB_TEXT ("\ntv_sec_ = %d"), this->tv_.tv_sec));
  ACE_DEBUG ((LM_DEBUG, ACE_LIB_TEXT ("\ntv_usec_ = %d\n"), this->tv_.tv_usec));
  ACE_DEBUG ((LM_DEBUG, ACE_END_DUMP));
#endif /* 0 */
#endif /* ACE_HAS_DUMP */
}

void
ACE_Time_Value::normalize (void)
{
  // // ACE_OS_TRACE ("ACE_Time_Value::normalize");
  // From Hans Rohnert...

  if (this->tv_.tv_usec >= ACE_ONE_SECOND_IN_USECS)
    {
      /*! \todo This loop needs some optimization.
       */
      do
        {
          ++this->tv_.tv_sec;
          this->tv_.tv_usec -= ACE_ONE_SECOND_IN_USECS;
        }
      while (this->tv_.tv_usec >= ACE_ONE_SECOND_IN_USECS);
    }
  else if (this->tv_.tv_usec <= -ACE_ONE_SECOND_IN_USECS)
    {
      /*! \todo This loop needs some optimization.
       */
      do
        {
          --this->tv_.tv_sec;
          this->tv_.tv_usec += ACE_ONE_SECOND_IN_USECS;
        }
      while (this->tv_.tv_usec <= -ACE_ONE_SECOND_IN_USECS);
    }

  if (this->tv_.tv_sec >= 1 && this->tv_.tv_usec < 0)
    {
      --this->tv_.tv_sec;
      this->tv_.tv_usec += ACE_ONE_SECOND_IN_USECS;
    }
// tv_sec in qnxnto is unsigned
#if !defined ( __QNXNTO__)
  else if (this->tv_.tv_sec < 0 && this->tv_.tv_usec > 0)
    {
      ++this->tv_.tv_sec;
      this->tv_.tv_usec -= ACE_ONE_SECOND_IN_USECS;
    }
#endif /* __QNXNTO__  */
}


ACE_Time_Value &
ACE_Time_Value::operator *= (double d)
{
  // double is long enough (16 digits) to not lose the accuracy.
  double time_total =
    (this->sec ()
     + static_cast<double> (this->usec ()) / ACE_ONE_SECOND_IN_USECS) * d;

  // shall we saturate the result?
#if !defined(ACE_LACKS_NUMERIC_LIMITS)
  static const double max_int = std::numeric_limits<time_t>::max () + 0.999999;
  static const double min_int = std::numeric_limits<time_t>::min () - 0.999999;
#else
  static const double max_int = LONG_MAX + 0.999999;
  static const double min_int = LONG_MIN - 0.999999;
#endif

  if (time_total > max_int)
    time_total = max_int;
  if (time_total < min_int)
    time_total = min_int;

  const time_t time_sec = static_cast<time_t> (time_total);

  time_total -= time_sec;
  time_total *= ACE_ONE_SECOND_IN_USECS;

  long time_usec = static_cast<long> (time_total);

  // round up the result to save the last usec
  if (time_usec > 0 && (time_total - time_usec) >= 0.5)
    ++time_usec;
  else if (time_usec < 0 && (time_total - time_usec) <= -0.5)
    --time_usec;

  this->set (time_sec, time_usec);

  return *this;
}

ACE_END_VERSIONED_NAMESPACE_DECL
