module;
#include "vpi_user.h"

export module sys.icarus;
import sys.priv;

static PLI_INT32 finish_and_return_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle arg;
    s_vpi_value val;
    (void)name;  /* Not used! */

    /* Get the return value. */
    arg = vpi_scan(argv);
    vpi_free_object(argv);
    val.format = vpiIntVal;
    vpi_get_value(arg, &val);

    /* Set the return value. */
    vpip_set_return_value(val.value.integer);

    /* Now finish. */
    vpi_control(vpiFinish, 1);
    return 0;
}

static PLI_INT32 task_not_implemented_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);

    vpi_printf("SORRY: %s:%d: task %s() is not currently implemented.\n",
        vpi_get_str(vpiFile, callh), (int)vpi_get(vpiLineNo, callh),
        name);
    vpip_set_return_value(1);
    vpi_control(vpiFinish, 1);
    return 0;
}

/*
 * This is used to warn the user that the specified optional system
 * task/function is not available (from Annex C 1364-2005).
 */
static PLI_INT32 missing_optional_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);

    vpi_printf("SORRY: %s:%d: %s() is not available in Icarus Verilog.\n",
        vpi_get_str(vpiFile, callh), (int)vpi_get(vpiLineNo, callh),
        name);
    vpip_set_return_value(1);
    vpi_control(vpiFinish, 1);
    return 0;
}

/*
 * Register the function with Verilog.
 */
void sys_special_register(void)
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysTask;
    tf_data.calltf = finish_and_return_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.tfname = const_cast<char*>("$finish_and_return");
    tf_data.user_data = const_cast<char*>("$finish_and_return");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* These tasks are not currently implemented. */
    tf_data.type = vpiSysTask;
    tf_data.calltf = 0;
    tf_data.sizetf = 0;
    tf_data.compiletf = task_not_implemented_compiletf;

    tf_data.tfname = const_cast<char*>("$fmonitor");
    tf_data.user_data = const_cast<char*>("$fmonitor");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$fmonitorb");
    tf_data.user_data = const_cast<char*>("$fmonitorb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$fmonitoro");
    tf_data.user_data = const_cast<char*>("$fmonitoro");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$fmonitorh");
    tf_data.user_data = const_cast<char*>("$fmonitorh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$and$array");
    tf_data.user_data = const_cast<char*>("$async$and$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$nand$array");
    tf_data.user_data = const_cast<char*>("$async$nand$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$or$array");
    tf_data.user_data = const_cast<char*>("$async$or$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$nor$array");
    tf_data.user_data = const_cast<char*>("$async$nor$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$and$plane");
    tf_data.user_data = const_cast<char*>("$async$and$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$nand$plane");
    tf_data.user_data = const_cast<char*>("$async$nand$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$or$plane");
    tf_data.user_data = const_cast<char*>("$async$or$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$async$nor$plane");
    tf_data.user_data = const_cast<char*>("$async$nor$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$and$array");
    tf_data.user_data = const_cast<char*>("$sync$and$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$nand$array");
    tf_data.user_data = const_cast<char*>("$sync$nand$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$or$array");
    tf_data.user_data = const_cast<char*>("$sync$or$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$nor$array");
    tf_data.user_data = const_cast<char*>("$sync$nor$array");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$and$plane");
    tf_data.user_data = const_cast<char*>("$sync$and$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$nand$plane");
    tf_data.user_data = const_cast<char*>("$sync$nand$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$or$plane");
    tf_data.user_data = const_cast<char*>("$sync$or$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sync$nor$plane");
    tf_data.user_data = const_cast<char*>("$sync$nor$plane");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpports");
    tf_data.user_data = const_cast<char*>("$dumpports");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpportsoff");
    tf_data.user_data = const_cast<char*>("$dumpportsoff");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpportson");
    tf_data.user_data = const_cast<char*>("$dumpportson");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpportsall");
    tf_data.user_data = const_cast<char*>("$dumpportsall");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpportslimit");
    tf_data.user_data = const_cast<char*>("$dumpportslimit");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$dumpportsflush");
    tf_data.user_data = const_cast<char*>("$dumpportsflush");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* The following optional system tasks/functions are not implemented
     * in Icarus Verilog (from Annex C 1364-2005). */
    tf_data.type = vpiSysTask;
    tf_data.calltf = 0;
    tf_data.sizetf = 0;
    tf_data.compiletf = missing_optional_compiletf;

    tf_data.tfname = const_cast<char*>("$input");
    tf_data.user_data = const_cast<char*>("$input");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$key");
    tf_data.user_data = const_cast<char*>("$key");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$nokey");
    tf_data.user_data = const_cast<char*>("$nokey");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$list");
    tf_data.user_data = const_cast<char*>("$list");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$log");
    tf_data.user_data = const_cast<char*>("$log");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$nolog");
    tf_data.user_data = const_cast<char*>("$nolog");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$save");
    tf_data.user_data = const_cast<char*>("$save");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$restart");
    tf_data.user_data = const_cast<char*>("$restart");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$incsave");
    tf_data.user_data = const_cast<char*>("$incsave");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$scope");
    tf_data.user_data = const_cast<char*>("$scope");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$showscopes");
    tf_data.user_data = const_cast<char*>("$showscopes");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$showvars");
    tf_data.user_data = const_cast<char*>("$showvars");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sreadmemb");
    tf_data.user_data = const_cast<char*>("$sreadmemb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$sreadmemh");
    tf_data.user_data = const_cast<char*>("$sreadmemh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* Optional functions. */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;

    tf_data.tfname = const_cast<char*>("$getpattern");
    tf_data.user_data = const_cast<char*>("$getpattern");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.tfname = const_cast<char*>("$scale");
    tf_data.user_data = const_cast<char*>("$scale");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}