#include "vpi_user.h"
#include "sv_vpi_user.h"

import sys.convert;
import sys.counterdrivers;
import sys.darray;
import sys.deposit;
import sys.display;
import sys.fileio;
import sys.finish;
import sys.plusargs;
import sys.queue;
import sys.random;
import sys.random.mti;

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

/*
 * Routine to register the system tasks/functions provided in this file.
 */
void sys_countdrivers_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSizedFunc;
    tf_data.tfname = const_cast<char*>("$countdrivers");
    tf_data.calltf = sys_countdrivers_calltf;
    tf_data.compiletf = sys_countdrivers_compiletf;
    tf_data.sizetf = sys_countdrivers_sizetf;
    tf_data.user_data = const_cast<char*>("$countdrivers");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_darray_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = "$size";
    tf_data.calltf = dobject_size_calltf;
    tf_data.compiletf = dobject_size_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$size");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_fileio_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    /*============================== fopen */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fopen");
    tf_data.calltf = sys_fopen_calltf;
    tf_data.compiletf = sys_fopen_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fopen");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fopenr */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fopenr");
    tf_data.calltf = sys_fopenrwa_calltf;
    tf_data.compiletf = sys_one_string_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fopenr");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fopenw */
    tf_data.tfname = const_cast<char*>("$fopenw");
    tf_data.user_data = const_cast<char*>("$fopenw");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fopena */
    tf_data.tfname = const_cast<char*>("$fopena");
    tf_data.user_data = const_cast<char*>("$fopena");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fclose */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fclose");
    tf_data.calltf = sys_fclose_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fclose");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fflush */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fflush");
    tf_data.calltf = sys_fflush_calltf;
    tf_data.compiletf = sys_one_opt_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fflush");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fgetc */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fgetc");
    tf_data.calltf = sys_common_fd_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fgetc");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fgets */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fgets");
    tf_data.calltf = sys_fgets_calltf;
    tf_data.compiletf = sys_fgets_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fgets");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fread */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fread");
    tf_data.calltf = sys_fread_calltf;
    tf_data.compiletf = sys_fread_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fread");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== ungetc */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$ungetc");
    tf_data.calltf = sys_ungetc_calltf;
    tf_data.compiletf = sys_two_numeric_args_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$ungetc");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== ftell */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$ftell");
    tf_data.calltf = sys_common_fd_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$ftell");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fseek */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fseek");
    tf_data.calltf = sys_fseek_calltf;
    tf_data.compiletf = sys_fseek_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fseek");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
    vpip_make_systf_system_defined(res);

    /*============================== rewind */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$rewind");
    tf_data.calltf = sys_common_fd_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$rewind");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== ferror */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$ferror");
    tf_data.calltf = sys_ferror_calltf;
    tf_data.compiletf = sys_ferror_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$ferror");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* $feof() is from 1364-2005. */
    /*============================== feof */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$feof");
    tf_data.calltf = sys_common_fd_calltf;
    tf_data.compiletf = sys_one_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$feof");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* Icarus specific. */
    /*============================== fputc */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$fputc");
    tf_data.calltf = sys_fputc_calltf;
    tf_data.compiletf = sys_two_numeric_args_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fputc");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_finish_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$finish");
    tf_data.calltf = sys_finish_calltf;
    tf_data.compiletf = sys_one_opt_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$finish");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$stop");
    tf_data.calltf = sys_finish_calltf;
    tf_data.compiletf = sys_one_opt_numeric_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$stop");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_deposit_register(void)
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$deposit");
    tf_data.calltf = sys_deposit_calltf;
    tf_data.compiletf = sys_deposit_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$deposit");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_display_register()
{
    s_cb_data cb_data;
    s_vpi_systf_data tf_data;
    vpiHandle res;

    check_command_line_args();

    /*============================== display */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$display");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$display");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$displayh");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$displayh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$displayo");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$displayo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$displayb");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$displayb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== write */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$write");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$write");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$writeh");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$writeh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$writeo");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$writeo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$writeb");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$writeb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== strobe */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$strobe");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$strobe");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$strobeh");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$strobeh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$strobeo");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$strobeo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$strobeb");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$strobeb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fstrobe */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fstrobe");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fstrobe");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fstrobeh");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fstrobeh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fstrobeo");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fstrobeo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fstrobeb");
    tf_data.calltf = sys_strobe_calltf;
    tf_data.compiletf = sys_strobe_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fstrobeb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== monitor */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitor");
    tf_data.calltf = sys_monitor_calltf;
    tf_data.compiletf = sys_monitor_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitor");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitorh");
    tf_data.calltf = sys_monitor_calltf;
    tf_data.compiletf = sys_monitor_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitorh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitoro");
    tf_data.calltf = sys_monitor_calltf;
    tf_data.compiletf = sys_monitor_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitoro");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitorb");
    tf_data.calltf = sys_monitor_calltf;
    tf_data.compiletf = sys_monitor_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitorb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitoron");
    tf_data.calltf = sys_monitoron_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitoron");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$monitoroff");
    tf_data.calltf = sys_monitoroff_calltf;
    tf_data.compiletf = sys_no_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$monitoroff");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fdisplay */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fdisplay");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fdisplay");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fdisplayh");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fdisplayh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fdisplayo");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fdisplayo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fdisplayb");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fdisplayb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== fwrite */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fwrite");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fwrite");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fwriteh");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fwriteh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fwriteo");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fwriteo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fwriteb");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fwriteb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================== swrite */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$swrite");
    tf_data.calltf = sys_swrite_calltf;
    tf_data.compiletf = sys_swrite_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$swrite");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$swriteh");
    tf_data.calltf = sys_swrite_calltf;
    tf_data.compiletf = sys_swrite_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$swriteh");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$swriteo");
    tf_data.calltf = sys_swrite_calltf;
    tf_data.compiletf = sys_swrite_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$swriteo");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$swriteb");
    tf_data.calltf = sys_swrite_calltf;
    tf_data.compiletf = sys_swrite_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$swriteb");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$sformat");
    tf_data.calltf = sys_sformat_calltf;
    tf_data.compiletf = sys_sformat_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$sformat");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiStringFunc;
    tf_data.tfname = const_cast<char*>("$sformatf");
    tf_data.calltf = sys_display_calltf;
    tf_data.compiletf = sys_sformatf_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$sformatf");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================ timeformat */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$timeformat");
    tf_data.calltf = sys_timeformat_calltf;
    tf_data.compiletf = sys_timeformat_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$timeformat");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$printtimescale");
    tf_data.calltf = sys_printtimescale_calltf;
    tf_data.compiletf = sys_printtimescale_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$printtimescale");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /*============================ severity tasks */
    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$fatal");
    tf_data.calltf = sys_severity_calltf;
    tf_data.compiletf = sys_fatal_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$fatal");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$error");
    tf_data.calltf = sys_severity_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$error");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$warning");
    tf_data.calltf = sys_severity_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$warning");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$info");
    tf_data.calltf = sys_severity_calltf;
    tf_data.compiletf = sys_display_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$info");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    cb_data.reason = cbEndOfCompile;
    cb_data.time = 0;
    cb_data.cb_rtn = sys_end_of_compile;
    cb_data.user_data = const_cast<char*>("system");
    vpi_register_cb(&cb_data);

    cb_data.reason = cbEndOfSimulation;
    cb_data.cb_rtn = sys_end_of_simulation;
    cb_data.user_data = const_cast<char*>("system");
    vpi_register_cb(&cb_data);
}

void sys_plusargs_register()
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$test$plusargs");
    tf_data.calltf = sys_test_plusargs_calltf;
    tf_data.compiletf = sys_one_string_arg_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$test$plusargs");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiIntFunc;
    tf_data.tfname = const_cast<char*>("$value$plusargs");
    tf_data.calltf = sys_value_plusargs_calltf;
    tf_data.compiletf = sys_value_plusargs_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$value$plusargs");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_queue_register(void)
{
    s_vpi_systf_data tf_data;
    s_cb_data cb;
    vpiHandle res;

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$q_initialize");
    tf_data.calltf = sys_q_initialize_calltf;
    tf_data.compiletf = sys_q_initialize_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$q_initialize");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$q_add");
    tf_data.calltf = sys_q_add_calltf;
    tf_data.compiletf = sys_q_add_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$q_add");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$q_remove");
    tf_data.calltf = sys_q_remove_calltf;
    tf_data.compiletf = sys_q_remove_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$q_remove");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$q_full");
    tf_data.calltf = sys_q_full_calltf;
    tf_data.compiletf = sys_q_full_compiletf;
    tf_data.sizetf = 0;  /* Not needed for a vpiSysFuncInt. */
    tf_data.user_data = const_cast<char*>("$q_full");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$q_exam");
    tf_data.calltf = sys_q_exam_calltf;
    tf_data.compiletf = sys_q_exam_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$q_exam");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* Create a callback to clear all the queue memory when the
     * simulator finishes. */
    cb.time = NULL;
    cb.reason = cbEndOfSimulation;
    cb.cb_rtn = cleanup_queue;
    cb.user_data = 0x0;
    cb.obj = 0x0;

    vpi_register_cb(&cb);
}

void sys_random_register(void)
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$random");
    tf_data.calltf = sys_random_calltf;
    tf_data.compiletf = sys_random_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$random");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* From SystemVerilog. */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncSized;
    tf_data.tfname = const_cast<char*>("$urandom");
    tf_data.calltf = sys_urandom_calltf;
    tf_data.compiletf = sys_random_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$urandom");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    /* From SystemVerilog. */
    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncSized;
    tf_data.tfname = const_cast<char*>("$urandom_range");
    tf_data.calltf = sys_urandom_range_calltf;
    tf_data.compiletf = sys_urandom_range_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$urandom_range");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_uniform");
    tf_data.calltf = sys_dist_uniform_calltf;
    tf_data.compiletf = sys_rand_three_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_uniform");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_normal");
    tf_data.calltf = sys_dist_normal_calltf;
    tf_data.compiletf = sys_rand_three_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_normal");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_exponential");
    tf_data.calltf = sys_dist_exponential_calltf;
    tf_data.compiletf = sys_rand_two_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_exponential");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_poisson");
    tf_data.calltf = sys_dist_poisson_calltf;
    tf_data.compiletf = sys_rand_two_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_poisson");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_chi_square");
    tf_data.calltf = sys_dist_chi_square_calltf;
    tf_data.compiletf = sys_rand_two_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_chi_square");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_t");
    tf_data.calltf = sys_dist_t_calltf;
    tf_data.compiletf = sys_rand_two_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_t");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$dist_erlang");
    tf_data.calltf = sys_dist_erlang_calltf;
    tf_data.compiletf = sys_rand_three_args_compiletf;
    tf_data.sizetf = sys_rand_func_sizetf;
    tf_data.user_data = const_cast<char*>("$dist_erlang");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void sys_random_mti_register(void)
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$mti_random");
    tf_data.calltf = sys_mti_random_calltf;
    tf_data.compiletf = sys_random_compiletf;
    tf_data.user_data = const_cast<char*>("$mti_random");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);

    tf_data.type = vpiSysFunc;
    tf_data.sysfunctype = vpiSysFuncInt;
    tf_data.tfname = const_cast<char*>("$mti_dist_uniform");
    tf_data.calltf = sys_mti_dist_uniform_calltf;
    tf_data.compiletf = sys_rand_three_args_compiletf;
    tf_data.user_data = const_cast<char*>("$mti_dist_uniform");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}