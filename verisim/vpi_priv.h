#pragma once
#include <filesystem>

/*
 * The VPI_MODE contains the major mode for VPI use. This is used
 * to generate error messages when vpi functions are called
 * incorrectly.
 */
enum class VPI_MODE {
    NONE = 0,
    /* The compiler is calling a register function. */
    REGISTER,
    /* The compiler is calling a compiletf function. */
    COMPILETF,
    /* The compiler is calling a calltf function. */
    CALLTF,
    /* We are in the midst of a RWSync callback. */
    RWSYNC,
    /* We are in a ROSync callback. */
    ROSYNC
};
extern VPI_MODE vpi_mode_flag;

/*
 * This function is called before any compilation to load VPI
 * modules. This gives the modules a chance to announce their
 * contained functions before compilation commences. It is called only
 * once per module.
 */
void vpip_load_module(std::filesystem::path name);