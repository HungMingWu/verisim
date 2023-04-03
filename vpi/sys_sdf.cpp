module;
#include <stdlib.h>
#include <string.h>
#include "vpi_user.h"

export module sys.sdf;
import sys.priv;
import sdf.priv;

/*
 * These are static context
 */

int sdf_flag_warning = 0;
int sdf_flag_inform = 0;
int sdf_min_typ_max;

/* Scope of the $sdf_annotate call. Annotation starts here. */
static vpiHandle sdf_scope;
static vpiHandle sdf_callh = 0;
/* The cell in process. */
static vpiHandle sdf_cur_cell;

static vpiHandle find_scope(vpiHandle scope, const char* name)
{
    vpiHandle idx = vpi_iterate(vpiModule, scope);
    /* If this scope has no modules then it can't have the one we
     * are looking for so just return 0. */
    if (idx == 0) return 0;

    vpiHandle cur;
    while ((cur = vpi_scan(idx))) {

        if (strcmp(name, vpi_get_str(vpiName, cur)) == 0) {
            vpi_free_object(idx);
            return cur;
        }
    }

    return 0;
}

static void check_command_line_args(void)
{
    struct t_vpi_vlog_info vlog_info;
    int idx;

    static int sdf_command_line_done = 0;
    if (sdf_command_line_done)
        return;

    vpi_get_vlog_info(&vlog_info);

    for (idx = 0; idx < vlog_info.argc; idx += 1) {
        if (strcmp(vlog_info.argv[idx], "-sdf-warn") == 0) {
            sdf_flag_warning = 1;

        }
        else if (strcmp(vlog_info.argv[idx], "-sdf-info") == 0) {
            sdf_flag_inform = 1;

        }
        else if (strcmp(vlog_info.argv[idx], "-sdf-verbose") == 0) {
            sdf_flag_warning = 1;
            sdf_flag_inform = 1;
        }
    }

    sdf_command_line_done = 1;
}

static PLI_INT32 sys_sdf_annotate_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle module;

    check_command_line_args();

    /* Check that we have a file name argument. */
    if (argv == 0) {
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s requires a file name argument.\n", name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
        return 0;
    }
    if (!is_string_obj(vpi_scan(argv))) {
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s's file name must be a string.\n", name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
    }

    /* The module argument is optional. */
    module = vpi_scan(argv);
    if (module == 0) return 0;
    if (vpi_get(vpiType, module) != vpiModule) {
        vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s's second argument must be a module instance.\n",
            name);
        vpip_set_return_value(1);
        vpi_control(vpiFinish, 1);
    }

    /* Warn the user that we only use the first two arguments. */
    if (vpi_scan(argv) != 0) {
        vpi_printf("WARNING: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("%s currently only uses the first two argument.\n",
            name);
        vpi_free_object(argv);
    }

    return 0;
}

static PLI_INT32 sys_sdf_annotate_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    FILE* sdf_fd;
    char* fname = get_filename(callh, name, vpi_scan(argv));

    if (fname == 0) {
        vpi_free_object(argv);
        return 0;
    }

    sdf_fd = fopen(fname, "r");
    if (sdf_fd == 0) {
        vpi_printf("WARNING: %s:%d: ", vpi_get_str(vpiFile, callh),
            (int)vpi_get(vpiLineNo, callh));
        vpi_printf("Unable to open SDF file \"%s\"."
            " Skipping this annotation.\n", fname);
        vpi_free_object(argv);
        free(fname);
        return 0;
    }

    /* The optional second argument is the scope to annotate. */
    sdf_scope = vpi_scan(argv);
    if (sdf_scope) vpi_free_object(argv);
    else sdf_scope = vpi_handle(vpiScope, callh);

    /* Select which delay to use. */
    sdf_min_typ_max = vpi_get(_vpiDelaySelection, 0);

    sdf_cur_cell = 0;
    sdf_callh = callh;
    sdf_process_file(sdf_fd, fname);
    sdf_callh = 0;

    fclose(sdf_fd);
    free(fname);
    return 0;
}

void sys_sdf_register(void)
{
    s_vpi_systf_data tf_data;
    vpiHandle res;

    tf_data.type = vpiSysTask;
    tf_data.tfname = const_cast<char*>("$sdf_annotate");
    tf_data.calltf = sys_sdf_annotate_calltf;
    tf_data.compiletf = sys_sdf_annotate_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = const_cast<char*>("$sdf_annotate");
    res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}