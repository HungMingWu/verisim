module;
#include "vpi_user.h"

export module sys.readmem.lex;

export {
	constexpr int MEM_ADDRESS = 257;
	constexpr int MEM_WORD = 258;
	constexpr int MEM_ERROR = 259;

	char* readmem_error_token;

	void sys_readmem_start_file(vpiHandle callh, FILE* in, int bin_flag,
		unsigned width, struct t_vpi_vecval* vv);

	int readmemlex();

	void destroy_readmem_lexor();
}

module :private;

void sys_readmem_start_file(vpiHandle callh, FILE* in, int bin_flag,
	unsigned width, struct t_vpi_vecval* vv)
{

}

int readmemlex() { return 0; }

void destroy_readmem_lexor() {}