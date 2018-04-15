/*!
 * \file cryptoauthlib/version.h
 * \brief Version info for cryptoauthlib
 *
 * \cond
 *__legal_b__
 *
 *__legal_e__
 * \endcond
 *
 */

#ifndef __CRYPTOAUTHLIB_VERSION_H__
#define __CRYPTOAUTHLIB_VERSION_H__

// Bump-up with each new version
#define CRYPTOAUTHLIB_MAJOR_VERSION    0
#define CRYPTOAUTHLIB_MINOR_VERSION    0
#define CRYPTOAUTHLIB_RELEASE_NUMBER   1
#define CRYPTOAUTHLIB_VERSION_STRING   _T("cryptoauthlib 0.0.1")

// Must be updated manually as well each time the version above changes
#define CRYPTOAUTHLIB_VERSION_NUM_DOT_STRING   "0.0.1"
#define CRYPTOAUTHLIB_VERSION_NUM_STRING       "0001"

// nothing should be updated below this line when updating the version

#define CRYPTOAUTHLIB_VERSION_NUMBER (CRYPTOAUTHLIB_MAJOR_VERSION * 1000) + (CRYPTOAUTHLIB_MINOR_VERSION * 100) + CRYPTOAUTHLIB_RELEASE_NUMBER
#define CRYPTOAUTHLIB_BETA_NUMBER      1
#define CRYPTOAUTHLIB_VERSION_FLOAT CRYPTOAUTHLIB_MAJOR_VERSION + (CRYPTOAUTHLIB_MINOR_VERSION/10.0) + (CRYPTOAUTHLIB_RELEASE_NUMBER/100.0) + (CRYPTOAUTHLIB_BETA_NUMBER/10000.0)

// check if the current version is at least major.minor.release
#define CRYPTOAUTHLIB_CHECK_VERSION(major,minor,release) \
    (CRYPTOAUTHLIB_MAJOR_VERSION > (major) || \
    (CRYPTOAUTHLIB_MAJOR_VERSION == (major) && CRYPTOAUTHLIB_MINOR_VERSION > (minor)) || \
    (CRYPTOAUTHLIB_MAJOR_VERSION == (major) && CRYPTOAUTHLIB_MINOR_VERSION == (minor) && CRYPTOAUTHLIB_RELEASE_NUMBER >= (release)))

#endif

