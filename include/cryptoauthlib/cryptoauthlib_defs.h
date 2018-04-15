/*!
 * \file cryptoauthlib/cryptoauthlib_defs.h
 * \brief Definitions needed for cryptoauthlib
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#ifndef __CRYPTOAUTHLIB_DEFS_H__
#define __CRYPTOAUTHLIB_DEFS_H__

#ifdef CRYPTOAUTHLIB_EXPORTS
#define CRYPTOAUTHLIB_API __declspec(dllexport)
#elif CRYPTOAUTHLIB_USE
#define CRYPTOAUTHLIB_API __declspec(dllimport)
#else
#define CRYPTOAUTHLIB_API
#endif

#endif

