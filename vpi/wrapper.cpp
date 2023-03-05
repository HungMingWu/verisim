import vpi;

#include "vpi_user.h"



void sys_convert_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiRealFunc;
    tf_data.user_data = const_cast<char*>("$bitstoreal");
    tf_data.tfname = tf_data.user_data;
    tf_data.sizetf = 0;
    tf_data.compiletf = sys_convert_compiletf;
    tf_data.calltf = sys_bitstoreal_calltf;
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiRealFunc;
    tf_data.user_data = const_cast<char*>("$itor");
    tf_data.tfname = tf_data.user_data;
    tf_data.sizetf = 0;
    tf_data.compiletf = sys_convert_compiletf;
    tf_data.calltf = sys_itor_calltf;
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSizedFunc;
    tf_data.user_data = const_cast<char*>("$realtobits");
    tf_data.tfname = tf_data.user_data;
    tf_data.sizetf = sizetf_64;
    tf_data.compiletf = sys_convert_compiletf;
    tf_data.calltf = sys_realtobits_calltf;
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.user_data = const_cast<char*>("$rtoi");
    tf_data.tfname = tf_data.user_data;
    tf_data.sizetf = 0;
    tf_data.compiletf = sys_convert_compiletf;
    tf_data.calltf = sys_rtoi_calltf;
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}
