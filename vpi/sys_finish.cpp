module;
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "vpi_user.h"

export module sys.finish;
import sys.priv;

export {
	PLI_INT32 sys_finish_calltf(ICARUS_VPI_CONST PLI_BYTE8* name);
}

module :private;

PLI_INT32 sys_finish_calltf(ICARUS_VPI_CONST PLI_BYTE8* name)
{
	vpiHandle callh, argv;
	s_vpi_value val;
	int diag_msg = 1;
	int had_arg = 0;

	/* Get the argument list and look for the diagnostic message level. */
	callh = vpi_handle(vpiSysTfCall, 0);
	argv = vpi_iterate(vpiArgument, callh);
	if (argv) {
		vpiHandle arg = vpi_scan(argv);
		vpi_free_object(argv);
		val.format = vpiIntVal;
		vpi_get_value(arg, &val);
		diag_msg = val.value.integer;
		if ((diag_msg < 0) || (diag_msg > 2)) {
			vpi_printf("WARNING: %s:%d: ", vpi_get_str(vpiFile, callh),
				(int)vpi_get(vpiLineNo, callh));
			vpi_printf("%s(%d) argument must be 0, 1, or 2.\n",
				(const char*)name, (int)diag_msg);
		}
		had_arg = 1;
	}

	if (diag_msg != 0) {
		s_vpi_time now;
		int units;
		uint64_t raw_time;
		vpi_printf("%s:%d: %s",
			vpi_get_str(vpiFile, callh),
			(int)vpi_get(vpiLineNo, callh),
			(const char*)name);
		if (had_arg) vpi_printf("(%d)", diag_msg);
		now.type = vpiSimTime;
		vpi_get_time(0, &now);
		raw_time = now.high;
		raw_time <<= 32;
		raw_time |= now.low;
		vpi_printf(" called at %llu", raw_time);
		units = vpi_get(vpiTimePrecision, 0);
		switch (units) {
		case   2: vpi_printf(" (100s)\n");  break;
		case   1: vpi_printf(" (10s)\n");   break;
		case   0: vpi_printf(" (1s)\n");    break;
		case  -1: vpi_printf(" (100ms)\n"); break;
		case  -2: vpi_printf(" (10ms)\n");  break;
		case  -3: vpi_printf(" (1ms)\n");   break;
		case  -4: vpi_printf(" (100us)\n"); break;
		case  -5: vpi_printf(" (10us)\n");  break;
		case  -6: vpi_printf(" (1us)\n");   break;
		case  -7: vpi_printf(" (100ns)\n"); break;
		case  -8: vpi_printf(" (10ns)\n");  break;
		case  -9: vpi_printf(" (1ns)\n");   break;
		case -10: vpi_printf(" (100ps)\n"); break;
		case -11: vpi_printf(" (10ps)\n");  break;
		case -12: vpi_printf(" (1ps)\n");   break;
		case -13: vpi_printf(" (100fs)\n"); break;
		case -14: vpi_printf(" (10fs)\n");  break;
		case -15: vpi_printf(" (1fs)\n");   break;
		default:
			vpi_printf("unknown time unit '%d'", units);
			assert(0);
		}
	}

	if (strcmp((const char*)name, "$stop") == 0) {
		vpi_control(vpiStop, diag_msg);
		return 0;
	}

	vpip_set_return_value(0);

	vpi_control(vpiFinish, diag_msg);
	return 0;
}