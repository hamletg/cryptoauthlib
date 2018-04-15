/*!
 * \file cryptoauthlib/cryptoauthlib.cpp
 * \brief Entry point for a DLL under windows
 *
 * \cond
 *__legal_b__
 *
 *__legal_e__
 * \endcond
 *
 */

#include "cryptoauthlib/cryptoauthlib_prec.h"
#include "cryptoauthlib/cryptoauthlib_defs.h"

#ifdef WIN32
CRYPTOAUTHLIB_API BOOL APIENTRY DllMain(HANDLE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
#endif

