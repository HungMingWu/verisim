module;
#include "vpi_user.h"

export module sys.vcdoff;
import sys.priv;
import vcd.priv;

export {
    void sys_vcdoff_register();
}

module :private;

static int dump_flag = 0;

static PLI_INT32 sys_dummy_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    (void)name; /* Parameter is not used. */
    return 0;
}

static PLI_INT32 sys_dumpvars_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    (void)name; /* Parameter is not used. */
    if (dump_flag == 0) {
        vpi_printf("VCD info: dumping is suppressed.\n");
        dump_flag = 1;
    }

    return 0;
}

void sys_vcdoff_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    /* All the compiletf routines are located in vcd_priv.c. */

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpall");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpall");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpfile");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_one_string_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpfile");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpflush");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpflush");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumplimit");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumplimit");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpoff");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpoff");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpon");
    tf_data.calltf = sys_dummy_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpon");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$dumpvars");
    tf_data.calltf = sys_dumpvars_calltf;
    tf_data.compiletf = sys_dumpvars_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$dumpvars");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}
