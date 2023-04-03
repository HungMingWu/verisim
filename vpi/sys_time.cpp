module;
#include <assert.h>
#include <math.h>
#include <string.h>
#include "vpi_user.h"

export module sys.time;
import sys.priv;

export {
    PLI_INT32 sys_time_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
    PLI_INT32 sys_realtime_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
}

module :private;

PLI_INT32 sys_time_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    s_vpi_value val;
    s_vpi_time  now;
    vpiHandle call_handle;
    vpiHandle mod;
    int units, prec;
    long scale;

    call_handle = vpi_handle(vpiSysTfCall, 0);
    assert(call_handle);

    mod = sys_func_module(call_handle);

    now.type = vpiSimTime;
    vpi_get_time(0, &now);

    /* All the variants but $simtime return the time in units of
       the local scope. The $simtime function returns the
       simulation time. */
    if (strcmp(name, "$simtime") == 0)
        units = vpi_get(vpiTimePrecision, 0);
    else
        units = vpi_get(vpiTimeUnit, mod);

    prec = vpi_get(vpiTimePrecision, 0);
    scale = 1;
    while (units > prec) {
        scale *= 10;
        units -= 1;
    }

    assert(8 * sizeof(long long) >= 64);
    { long frac;
    long long tmp_now = ((long long)now.high) << 32;
    tmp_now += (long long)now.low;
    frac = tmp_now % (long long)scale;
    tmp_now /= (long long)scale;

    /* Round to the nearest integer, which may be up. */
    if ((scale > 1) && (frac >= scale / 2))
        tmp_now += 1;

    now.low = tmp_now & 0xffffffff;
    now.high = tmp_now >> 32LL;
    }

    val.format = vpiTimeVal;
    val.value.time = &now;

    vpi_put_value(call_handle, &val, 0, vpiNoDelay);

    return 0;
}

/* This also supports $abstime() from VAMS-2.3. */
PLI_INT32 sys_realtime_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    s_vpi_value val;
    s_vpi_time  now;
    vpiHandle callh;
    vpiHandle mod;

    callh = vpi_handle(vpiSysTfCall, 0);
    assert(callh);

    mod = sys_func_module(callh);

    now.type = vpiScaledRealTime;
    vpi_get_time(mod, &now);

    /* For $abstime() we return the time in second. */
    if (strcmp(name, "$abstime") == 0) {
        PLI_INT32 scale = vpi_get(vpiTimeUnit, mod);
        if (scale >= 0) now.real *= pow(10.0, scale);
        else now.real /= pow(10.0, -scale);
    }

    val.format = vpiRealVal;
    val.value.real = now.real;
    vpi_put_value(callh, &val, 0, vpiNoDelay);

    return 0;
}
