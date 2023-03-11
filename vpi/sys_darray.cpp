module;
#include <assert.h>
#include "vpi_user.h"
#include "sv_vpi_user.h"

export module sys.darray;

export {
	PLI_INT32 dobject_size_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name);
	PLI_INT32 dobject_size_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
}

module :private;

PLI_INT32 dobject_size_compiletf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
	vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
	vpiHandle argv, arg;

	argv = vpi_iterate(vpiArgument, callh);
	if (argv == 0) {
		vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
			(int)vpi_get(vpiLineNo, callh));
		vpi_printf("%s requires a dynamic array, queue or string "
			"argument.\n", name);
		vpip_set_return_value(1);
		vpi_control(vpiFinish, 1);
		return 0;
	}

	arg = vpi_scan(argv);  /* This should never be zero. */
	assert(arg);

	/* The argument must be a dynamic array, queue or string. */
	switch (vpi_get(vpiType, arg)) {
	case vpiStringVar:
		break;
	case vpiArrayVar:
		switch (vpi_get(vpiArrayType, arg)) {
		case vpiDynamicArray:
		case vpiQueueArray:
			break;
		default:
			vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
				(int)vpi_get(vpiLineNo, callh));
			vpi_printf("%s argument must be a dynamic array, queue or "
				"string.\n", name);
			vpip_set_return_value(1);
			vpi_control(vpiFinish, 1);
		}
		break;
	default:
		vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
			(int)vpi_get(vpiLineNo, callh));
		vpi_printf("%s argument must be a dynamic array, queue or string, "
			"given a %s.\n", name, vpi_get_str(vpiType, arg));
		vpip_set_return_value(1);
		vpi_control(vpiFinish, 1);
	}

	arg = vpi_scan(argv);
	if (arg != 0) {
		vpi_printf("ERROR: %s:%d: ", vpi_get_str(vpiFile, callh),
			(int)vpi_get(vpiLineNo, callh));
		vpi_printf("%s has too many arguments.\n", name);
		vpip_set_return_value(1);
		vpi_control(vpiFinish, 1);
		vpi_free_object(argv);
	}

	return 0;
}

PLI_INT32 dobject_size_calltf(ICARUS_VPI_CONST PLI_BYTE8*)
{
    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle arg = vpi_scan(argv);

    vpi_free_object(argv);

    s_vpi_value value;
    value.format = vpiIntVal;
    value.value.integer = vpi_get(vpiSize, arg);

    vpi_put_value(callh, &value, 0, vpiNoDelay);

    return 0;
}