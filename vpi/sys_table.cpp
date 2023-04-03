module;
#include <stdlib.h>
#include <string.h>
#include "vpi_user.h"

export module sys.table;
import sys.vcd;
import vcd.priv;
import sys.vcdoff;

#ifdef HAVE_LIBZ
#ifdef HAVE_LIBBZ2
extern void sys_lxt_register(void);
#else
static void sys_lxt_register(void) { fputs("LXT support disabled since libbzip2 not available\n", stderr); exit(1); }
#endif
extern void sys_lxt2_register(void);
extern void sys_fst_register(void);
#else
static void sys_lxt_register(void) { fputs("LXT support disabled since zlib not available\n", stderr); exit(1); }
static void sys_lxt2_register(void) { fputs("LXT2 support disabled since zlib not available\n", stderr); exit(1); }
static void sys_fst_register(void) { fputs("FST support disabled since zlib not available\n", stderr); exit(1); }
#endif

static void sys_lxt_or_vcd_register(void)
{
	int idx;
	struct t_vpi_vlog_info vlog_info;

	const char* dumper;

	/* Get the dumper of choice from the IVERILOG_DUMPER
	   environment variable. */
	dumper = getenv("IVERILOG_DUMPER");
	if (dumper) {
		const char* cp = strchr(dumper, '=');
		if (cp != 0)
			dumper = cp + 1;

	}
	else {
		dumper = "vcd";
	}

	/* Scan the extended arguments, looking for flags that select
	   major features. This can override the environment variable
	   settings. */
	vpi_get_vlog_info(&vlog_info);

	for (idx = 0; idx < vlog_info.argc; idx += 1) {

		if (strcmp(vlog_info.argv[idx], "-fst") == 0) {
			dumper = "fst";

		}
		else if (strcmp(vlog_info.argv[idx], "-fst-space") == 0) {
			dumper = "fst";

		}
		else if (strcmp(vlog_info.argv[idx], "-fst-speed") == 0) {
			dumper = "fst";

		}
		else if (strcmp(vlog_info.argv[idx], "-fst-space-speed") == 0) {
			dumper = "fst";
		}
		else if (strcmp(vlog_info.argv[idx], "-fst-speed-space") == 0) {
			dumper = "fst";

		}
		else if (strcmp(vlog_info.argv[idx], "-fst-none") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt") == 0) {
			dumper = "lxt";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt-space") == 0) {
			dumper = "lxt";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt-speed") == 0) {
			dumper = "lxt";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt-none") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt2") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt2-space") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt2-speed") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lxt2-none") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-lx2") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lx2-space") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lx2-speed") == 0) {
			dumper = "lxt2";

		}
		else if (strcmp(vlog_info.argv[idx], "-lx2-none") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-vcd") == 0) {
			dumper = "vcd";

		}
		else if (strcmp(vlog_info.argv[idx], "-vcd-off") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-vcd-none") == 0) {
			dumper = "none";

		}
		else if (strcmp(vlog_info.argv[idx], "-none") == 0) {
			dumper = "none";

		}
		else if (strncmp(vlog_info.argv[idx], "-dumpfile=", 10) == 0) {
			vcd_set_dump_path_default(vlog_info.argv[idx] + 10);
		}
	}

	if (strcmp(dumper, "vcd") == 0)
		sys_vcd_register();

	else if (strcmp(dumper, "VCD") == 0)
		sys_vcd_register();

	else if (strcmp(dumper, "fst") == 0)
		sys_fst_register();

	else if (strcmp(dumper, "FST") == 0)
		sys_fst_register();

	else if (strcmp(dumper, "lxt") == 0)
		sys_lxt_register();

	else if (strcmp(dumper, "LXT") == 0)
		sys_lxt_register();

	else if (strcmp(dumper, "lxt2") == 0)
		sys_lxt2_register();

	else if (strcmp(dumper, "LXT2") == 0)
		sys_lxt2_register();

	else if (strcmp(dumper, "lx2") == 0)
		sys_lxt2_register();

	else if (strcmp(dumper, "LX2") == 0)
		sys_lxt2_register();

	else if (strcmp(dumper, "none") == 0)
		sys_vcdoff_register();

	else if (strcmp(dumper, "NONE") == 0)
		sys_vcdoff_register();

	else {
		vpi_mcd_printf(1, "system.vpi: Unknown dumper format: %s,"
			" using VCD instead.\n", dumper);
		sys_vcd_register();
	}
}