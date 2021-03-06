/*
 * COPYRIGHT:         GNU GPL - See COPYING in the top level directory
 * PROJECT:           ReactOS Run-Time Library
 * PURPOSE:
 * FILE:              lib/rtl/i386/res_asm.S
 * PROGRAMER:
 */

//#include <asm.inc>
//#include <ks386.inc>
//
//EXTERN _LdrpAccessResource@16:PROC

/*
 * On x86, Shrinker, an executable compressor, depends on the
 * "call access_resource" instruction being there.
 */
//.code
int
_declspec(naked)
LdrAccessResource(int, int, int, int)
//PUBLIC _LdrAccessResource@16
//_LdrAccessResource@16:
{
    _asm {
        push ebp
        mov ebp, esp
        sub esp, 4
        push [ebp + 24]
        push [ebp + 20]
        push [ebp + 16]
        push [ebp + 12]
        push [ebp + 8]
        call LdrpAccessResource
        leave
        ret 16
    }
}
//END
