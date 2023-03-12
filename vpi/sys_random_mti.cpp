module;
#include <stdlib.h>
#include "vpi_user.h"

export module sys.random.mti;
import mt19937int;
import sys.priv;

export {
    PLI_INT32 sys_mti_random_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
    PLI_INT32 sys_mti_dist_uniform_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
}

module :private;

/*
 * Implement the $random system function using the ``Mersenne
 * Twister'' random number generator MT19937.
 */

 /* make sure this matches N+1 in mti19937int.c */
#define NP1	624+1

/* Icarus seed cookie */
#define COOKIE	0x1ca1ca1c

static struct context_s global_context = { NP1, {0} };

PLI_INT32 sys_mti_random_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh, argv, seed = 0;
    s_vpi_value val;
    int i_seed = COOKIE;
    struct context_s* context;

    (void)name; /* Parameter is not used. */

    /* Get the argument list and look for a seed. If it is there,
       get the value and reseed the random number generator. */
    callh = vpi_handle(vpiSysTfCall, 0);
    argv = vpi_iterate(vpiArgument, callh);
    val.format = vpiIntVal;
    if (argv) {
        seed = vpi_scan(argv);
        vpi_free_object(argv);
        vpi_get_value(seed, &val);
        i_seed = val.value.integer;

        /* Since there is a seed use the current
           context or create a new one */
        context = (struct context_s*)vpi_get_userdata(callh);
        if (!context) {
            context = (struct context_s*)calloc(1, sizeof(*context));
            context->mti = NP1;

            /* squirrel away context */
            vpi_put_userdata(callh, (void*)context);
        }

        /* If the argument is not the Icarus cookie, then
       reseed context */
        if (i_seed != COOKIE) sgenrand(context, i_seed);
    }
    else {
        /* use global context */
        context = &global_context;
    }

    /* Calculate and return the result */
    val.value.integer = genrand(context);
    vpi_put_value(callh, &val, 0, vpiNoDelay);

    /* mark seed with cookie */
    if (seed && i_seed != COOKIE) {
        val.value.integer = COOKIE;
        vpi_put_value(seed, &val, 0, vpiNoDelay);
    }

    return 0;
}

static long mti_dist_uniform(long* seed, long start, long end)
{
    (void)seed; /* Parameter is not used. */
    if (start >= end) return start;

    if ((start > LONG_MIN) || (end < LONG_MAX)) {
        long range = end - start;
        return start + genrand(&global_context) % range;
    }
    else {
        return genrand(&global_context);
    }
}


PLI_INT32 sys_mti_dist_uniform_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
    vpiHandle callh, argv, seed, start, end;
    s_vpi_value val;
    long i_seed, i_start, i_end;

    (void)name; /* Parameter is not used. */

    /* Get the argument handles and convert them. */
    callh = vpi_handle(vpiSysTfCall, 0);
    argv = vpi_iterate(vpiArgument, callh);
    seed = vpi_scan(argv);
    start = vpi_scan(argv);
    end = vpi_scan(argv);

    val.format = vpiIntVal;
    vpi_get_value(seed, &val);
    i_seed = val.value.integer;

    vpi_get_value(start, &val);
    i_start = val.value.integer;

    vpi_get_value(end, &val);
    i_end = val.value.integer;

    /* Calculate and return the result. */
    val.value.integer = mti_dist_uniform(&i_seed, i_start, i_end);
    vpi_put_value(callh, &val, 0, vpiNoDelay);

    /* Return the seed. */
    val.value.integer = i_seed;
    vpi_put_value(seed, &val, 0, vpiNoDelay);

    vpi_free_object(argv);
    return 0;
}
