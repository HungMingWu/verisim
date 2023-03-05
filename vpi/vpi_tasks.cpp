module;
#include <vpi_user.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

export module vpi.tasks;
import vpi.priv;

/*
 * When a loaded VPI module announces a system task/function, one
 * __vpiUserSystf object is created to hold the definition of that
 * task/function. The distinction between task and function is stored
 * in the vpi_systf_data structure data that was supplied by the
 * external module.
 *
 * When the compiler encounters a %vpi_call statement, it creates a
 * __vpiSysTaskCall to represent that particular call. The call refers
 * to the definition handle so that when the %vpi_call instruction is
 * encountered at run-time, the definition can be located and used.
 *
 * The vpiSysTaskCall handles both functions and tasks, as the two are
 * extremely similar. The different VPI type is reflected in a
 * different vpi_type pointer in the base structure. The only
 * additional part is the vbit/vwid that is used by the put of the
 * system function call to place the values in the vthread bit space.
 */
struct __vpiUserSystf : public __vpiHandle {
    __vpiUserSystf();
    int get_type_code() const;

    s_vpi_systf_data info;
    bool is_user_defn;
};

/*
 * We keep a table of all the __vpiUserSystf objects that are created
 * so that the user can iterate over them. The def_table is an array
 * of pointers to __vpiUserSystf objects. This table can be searched
 * by name using the vpi_find_systf function, and they can be
 * collected into an iterator using the vpip_make_systf_iterator function.
 */
static struct __vpiUserSystf** def_table = 0;
static unsigned def_count = 0;

static struct __vpiUserSystf* allocate_def()
{
    if (def_table == 0) {
        def_table = (struct __vpiUserSystf**)
            malloc(sizeof(struct __vpiUserSystf*));

        def_table[0] = new __vpiUserSystf;

        def_count = 1;
        return def_table[0];
    }

    def_table = (struct __vpiUserSystf**)
        realloc(def_table, (def_count + 1) * sizeof(struct __vpiUserSystf*));

    def_table[def_count] = new __vpiUserSystf;

    return def_table[def_count++];
}

/*
 * This is the entry function that a VPI module uses to hook a new
 * task/function into the simulator. The function creates a new
 * __vpi_userSystf to represent the definition for the calls that come
 * to pass later.
 */
vpiHandle vpi_register_systf(const struct t_vpi_systf_data* ss)
{
    struct __vpiUserSystf* cur = allocate_def();
    assert(ss);
    switch (ss->type) {
    case vpiSysTask:
    case vpiSysFunc:
        break;
    default:
        fprintf(stderr, "Unsupported type %d.\n", (int)ss->type);
        assert(0);
    }

    cur->info = *ss;
    cur->info.tfname = strdup(ss->tfname);
    cur->is_user_defn = true;

    return cur;
}

module :private;

__vpiUserSystf::__vpiUserSystf() {

}

int __vpiUserSystf::get_type_code() const {
    return 0;
}