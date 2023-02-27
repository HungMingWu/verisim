#include <vector>
#include <iostream>
#include "vpi_priv.h"
#include "dylib.hpp"

using vlog_startup_routines_t = void (*)(void);

namespace fs = std::filesystem;

static constexpr std::size_t VPIP_MODULE_PATH_MAX = 64;
static std::vector<fs::path> vpip_module_path;
static std::vector<dylib> dll_list;

void vpip_load_module(std::filesystem::path name)
{
	auto fullname = [&] {
		if (!name.parent_path().empty()) {
			/* If the name has at least one directory character in
		   it, then assume it is a complete name, maybe including any
		   possible .vpi suffix. */
		   if (fs::exists(name)) return name;
		   /* did we find a file? */
			/* no, try with a .vpi suffix too */
		   auto vpiname = name;
		   vpiname.replace_extension(".vpi");
		   if (fs::exists(vpiname)) return vpiname;
		   auto vplname = name;
		   /* Try also with the .vpl suffix. */
		   vplname.replace_extension(".vpl");
		   if (fs::exists(vplname)) return vplname;
		}
		else {
			for (const auto path : vpip_module_path) {
				auto vpiname = path / name;
				vpiname.replace_extension(".vpi");
				if (fs::exists(vpiname)) return vpiname;

				auto vplname = path / name;
				vplname.replace_extension(".vpl");
				if (fs::exists(vplname)) return vplname;
			}
		}
		return fs::path{};
	}();

	const auto extension = fullname.extension();
	const bool result = extension == ".vpl";
	if (fullname.empty()) return;

	/* must have found some file that could possibly be a vpi module
	* try to open it as a shared object.
	*/
	try {
		dylib dll(fullname, result);
		vpi_mode_flag = VPI_MODE::REGISTER;
		auto routines = dll.get_function<vlog_startup_routines_t>("vlog_startup_routines");
		for (unsigned tmp = 0; routines[tmp]; tmp += 1) {
			(routines[tmp])();
		}
		vpi_mode_flag = VPI_MODE::NONE;
		/* Add the dll to the list so it can be closed when we are done. */
		dll_list.push_back(std::move(dll));
	}
	catch (...) {

	}
}