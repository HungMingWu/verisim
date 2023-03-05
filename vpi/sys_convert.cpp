module;
#include <string.h>
#include "vpi_user.h"
#include <assert.h>

export module vpi;

vpiHandle   vpi_handle(PLI_INT32, vpiHandle) { return 0; }
vpiHandle   vpi_iterate(PLI_INT32, vpiHandle) { return 0; }
vpiHandle   vpi_scan(vpiHandle) { return 0; }
PLI_INT32    vpi_get(int, vpiHandle) { return 0; }
void* vpi_get_userdata(vpiHandle) { return 0; }
void vpi_get_value(vpiHandle expr, s_vpi_value* vp) {}

PLI_INT32 vpi_put_userdata(vpiHandle ref, void* data) { return 0; }
void check_for_extra_args(vpiHandle argv, vpiHandle callh, const PLI_BYTE8* name,
    const char* arg_str, unsigned opt)
{
    return;
}

static double bits2double(PLI_UINT32 bits[2])
{
    union conv {
        double rval;
        unsigned char bval[sizeof(double)];
    } conv;

#ifdef WORDS_BIGENDIAN
    conv.bval[7] = (bits[0] >> 0) & 0xff;
    conv.bval[6] = (bits[0] >> 8) & 0xff;
    conv.bval[5] = (bits[0] >> 16) & 0xff;
    conv.bval[4] = (bits[0] >> 24) & 0xff;
    conv.bval[3] = (bits[1] >> 0) & 0xff;
    conv.bval[2] = (bits[1] >> 8) & 0xff;
    conv.bval[1] = (bits[1] >> 16) & 0xff;
    conv.bval[0] = (bits[1] >> 24) & 0xff;
#else
    conv.bval[0] = (bits[0] >> 0) & 0xff;
    conv.bval[1] = (bits[0] >> 8) & 0xff;
    conv.bval[2] = (bits[0] >> 16) & 0xff;
    conv.bval[3] = (bits[0] >> 24) & 0xff;
    conv.bval[4] = (bits[1] >> 0) & 0xff;
    conv.bval[5] = (bits[1] >> 8) & 0xff;
    conv.bval[6] = (bits[1] >> 16) & 0xff;
    conv.bval[7] = (bits[1] >> 24) & 0xff;
#endif

    return conv.rval;
}

static void double2bits(double real, PLI_UINT32 bits[2])
{
    union conv {
        double rval;
        unsigned char bval[sizeof(double)];
    } conv;

    conv.rval = real;

#ifdef WORDS_BIGENDIAN
    bits[0] = conv.bval[7]
        | (conv.bval[6] << 8)
        | (conv.bval[5] << 16)
        | (conv.bval[4] << 24);
    bits[1] = conv.bval[3]
        | (conv.bval[2] << 8)
        | (conv.bval[1] << 16)
        | (conv.bval[0] << 24);
#else
    bits[0] = conv.bval[0]
        | (conv.bval[1] << 8)
        | (conv.bval[2] << 16)
        | (conv.bval[3] << 24);
    bits[1] = conv.bval[4]
        | (conv.bval[5] << 8)
        | (conv.bval[6] << 16)
        | (conv.bval[7] << 24);
#endif
}

void vpip_make_systf_system_defined(vpiHandle ref)
{

}

export
{
    PLI_INT32 sys_itor_calltf(PLI_BYTE8*)
    {
        vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
        vpiHandle arg = (vpiHandle)vpi_get_userdata(callh);
        s_vpi_value value;

        /* get value */
        value.format = vpiIntVal;
        vpi_get_value(arg, &value);

        /* convert */
        value.value.real = value.value.integer;
        value.format = vpiRealVal;

        /* return converted value */
        vpi_put_value(callh, &value, 0, vpiNoDelay);

        return 0;
    }

    PLI_INT32 sys_rtoi_calltf(PLI_BYTE8*)
    {
        vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
        vpiHandle arg = (vpiHandle)vpi_get_userdata(callh);
        s_vpi_value value;
        static struct t_vpi_vecval res;
        double val;

        /* get value */
        value.format = vpiRealVal;
        vpi_get_value(arg, &value);

        /* If the value is NaN or +/- infinity then return 'bx */
        val = value.value.real;
        if (val != val || (val && (val == 0.5 * val))) {
            res.aval = ~(PLI_INT32)0;
            res.bval = ~(PLI_INT32)0;
        }
        else {
            /* This is not 100% correct since large real values may break this
             * code. See the verinum code for a more rigorous implementation. */
            if (val >= 0.0) res.aval = (PLI_UINT64)val;
            else res.aval = -(PLI_UINT64)-val;
            res.bval = 0;
        }

        value.format = vpiVectorVal;
        value.value.vector = &res;

        /* return converted value */
        vpi_put_value(callh, &value, 0, vpiNoDelay);

        return 0;
    }

    PLI_INT32 sys_realtobits_calltf(PLI_BYTE8* name)
    {
        vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
        vpiHandle arg = (vpiHandle)vpi_get_userdata(callh);
        s_vpi_value value;
        static struct t_vpi_vecval res[2];

        PLI_UINT32 bits[2];

        /* get value */
        value.format = vpiRealVal;
        vpi_get_value(arg, &value);

        /* convert */
        double2bits(value.value.real, bits);

        res[0].aval = bits[0];
        res[0].bval = 0;
        res[1].aval = bits[1];
        res[1].bval = 0;

        value.format = vpiVectorVal;
        value.value.vector = res;

        /* return converted value */
        vpi_put_value(callh, &value, 0, vpiNoDelay);

        return 0;
    }

    PLI_INT32 sys_bitstoreal_calltf(PLI_BYTE8*)
    {
        vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
        vpiHandle arg = (vpiHandle)vpi_get_userdata(callh);
        s_vpi_value value;

        PLI_UINT32 bits[2];

        /* get value */
        value.format = vpiVectorVal;
        vpi_get_value(arg, &value);

        /* convert */
        bits[0] = (value.value.vector[0]).aval;
        bits[1] = (value.value.vector[1]).aval;
        value.value.real = bits2double(bits);
        value.format = vpiRealVal;

        /* return converted value */
        vpi_put_value(callh, &value, 0, vpiNoDelay);

        return 0;
    }

    PLI_INT32 sys_convert_compiletf(PLI_BYTE8* name)
    {
        vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
        vpiHandle argv = vpi_iterate(vpiArgument, callh);
        vpiHandle arg;

        /* Check that there is an argument. */
        if (argv == 0) {
#if 0
            error_message(callh, "%s requires one argument.\n");
#endif
            return 0;
        }

        /* In Icarus if we have an argv we have at least one argument. */
        arg = vpi_scan(argv);

        /* Validate the argument. Only $bitstoreal for now. */
        if (!strcmp("$bitstoreal", (char*)(name)) && vpi_get(vpiSize, arg) != 64) {
#if 0
            error_message(callh, "%s requires a 64-bit argument.\n");
#endif
            return 0;
        }

        /* Save the argument away to make the calltf faster. */
        vpi_put_userdata(callh, (void*)arg);

        /* These functions only take one argument. */
        check_for_extra_args(argv, callh, name, "one argument", 0);

        return 0;
    }

    PLI_INT32 sizetf_64(PLI_BYTE8*)
    {
        return 64;
    }
}