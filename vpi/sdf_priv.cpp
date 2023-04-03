module;
#include <stdio.h>

export module sdf.priv;

export {
	void sdf_process_file(FILE* fd, const char* path);
}

module :private;

void sdf_process_file(FILE* fd, const char* path) {

}