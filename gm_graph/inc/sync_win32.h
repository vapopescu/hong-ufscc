#ifndef _SYNC_WIN32_H
#define _SYNC_WIN32_H

#include <intrin.h>

template <bool, class _Tp> struct __sync_win32_enable_if {};
template <class _Tp> struct __sync_win32_enable_if<true, _Tp> { typedef _Tp type; };

template <class _Tp>
__forceinline _Tp __sync_add_and_fetch(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchangeAdd((long*)(__ptr), (long)(__val))) + __val;
}

template <class _Tp>
__forceinline _Tp __sync_add_and_fetch(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchangeAdd64((__int64*)(__ptr), (__int64)(__val))) + __val;
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_add(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchangeAdd((long*)(__ptr), (long)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_add(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchangeAdd64((__int64*)(__ptr), (__int64)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_lock_test_and_set(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchange8((char*)(__ptr), (char)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_lock_test_and_set(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(short), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchange16((short*)(__ptr), (short)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_lock_test_and_set(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchange((long*)(__ptr), (long)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_lock_test_and_set(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedExchange64((__int64*)(__ptr), (__int64)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_val_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange8((char*)(__ptr), (char)(__new_val),
        (long)(__old_val));
}

template <class _Tp>
__forceinline _Tp __sync_val_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(short), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange16((short*)(__ptr), (short)(__new_val),
        (long)(__old_val));
}

template <class _Tp>
__forceinline _Tp __sync_val_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange((long*)(__ptr), (long)(__new_val),
        (long)(__old_val));
}

template <class _Tp>
__forceinline _Tp __sync_val_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange64((__int64*)(__ptr), (__int64)(__new_val),
        (__int64)(__old_val));
}

template <class _Tp>
__forceinline bool __sync_bool_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange8((char*)(__ptr), (char)(__new_val),
        (long)(__old_val)) == (long)(__old_val);
}

template <class _Tp>
__forceinline bool __sync_bool_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(short), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange16((short*)(__ptr), (short)(__new_val),
        (long)(__old_val)) == (long)(__old_val);
}

template <class _Tp>
__forceinline bool __sync_bool_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange((long*)(__ptr), (long)(__new_val),
        (long)(__old_val)) == (long)(__old_val);
}

template <class _Tp>
__forceinline bool __sync_bool_compare_and_swap(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __old_val,
    typename __sync_win32_enable_if<true, _Tp>::type __new_val)
{
    return _InterlockedCompareExchange64((__int64*)(__ptr), (__int64)(__new_val),
        (__int64)(__old_val)) == (__int64)(__old_val);
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_or(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __val)
{
    return (_Tp)(_InterlockedOr8((char*)(__ptr), (char)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_or(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedOr((long*)(__ptr), (long)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_or(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedOr64((__int64*)(__ptr), (__int64)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_and(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __val)
{
    return (_Tp)(_InterlockedAnd8((char*)(__ptr), (char)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_and(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedAnd((long*)(__ptr), (long)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_and(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedAnd64((__int64*)(__ptr), (__int64)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_xor(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(char), _Tp>::type __val)
{
    return (_Tp)(_InterlockedXor8((char*)(__ptr), (char)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_xor(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(long), _Tp>::type __val)
{
    return (_Tp)(_InterlockedXor((long*)(__ptr), (long)(__val)));
}

template <class _Tp>
__forceinline _Tp __sync_fetch_and_xor(
    _Tp* __ptr,
    typename __sync_win32_enable_if<sizeof(_Tp) == sizeof(__int64), _Tp>::type __val)
{
    return (_Tp)(_InterlockedXor64((__int64*)(__ptr), (__int64)(__val)));
}

#endif // _SYNC_WIN32_H