module;
#include <assert.h>
#include "vpi_user.h"

export module sys.deposit;
import sys.priv;

export {
    PLI_INT32 sys_deposit_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
    PLI_INT32 sys_deposit_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name);
}

module :private;

PLI_INT32 sys_deposit_calltf(ICARUS_VPI_CONST PLI_BYTE8*)
{
    vpiHandle callh, argv, target, value;
    s_vpi_value val;

    callh = vpi_handle(vpiSysTfCall, 0);
    argv = vpi_iterate(vpiArgument, callh);
    target = vpi_scan(argv);
    assert(target);
    value = vpi_scan(argv);
    assert(value);

    val.format = vpiIntVal;
    vpi_get_value(value, &val);

    vpi_put_value(target, &val, 0, vpiNoDelay);

    vpi_free_object(argv);
    return 0;
}

PLI_INT32 sys_deposit_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle target, value;

    /* Check that there are arguments. */
    if (argv == 0) {
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s requires two arguments.\n", name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
        return 0;
    }

    /* Check that there are at least two arguments. */
    target = vpi_scan(argv);  /* This should never be zero. */
    value = vpi_scan(argv);
    if (value == 0) {
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s requires two arguments.\n", name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
        return 0;
    }

    assert(target);

    /* Check the targets type. It must be a net or a register. */
    switch (vpi_get(vpiType, target)) {
    case vpiNet:
    case vpiReg:
        break;
    default:
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("invalid target type (%s) for %s.\n",
            vpi_get_str(vpiType, target), name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
    }

    /* Check that there is at most two arguments. */
    check_for_extra_args(argv, callh, name, "two arguments", 0);

    return 0;
}
