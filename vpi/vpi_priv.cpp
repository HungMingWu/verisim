module;
#include "vpi_user.h"

export module vpi.priv;

export {
/*
 * This structure is the very base of a vpiHandle. Every handle
 * structure is derived from this class so that the library can
 * internally pass the derived types as pointers to one of these.
 */
    class __vpiHandle {
    public:
        inline __vpiHandle() { }
        virtual ~__vpiHandle() = default;

        virtual int get_type_code(void) const = 0;
        virtual int vpi_get(int code);
        virtual char* vpi_get_str(int code);

        virtual void vpi_get_value(p_vpi_value val);
        virtual vpiHandle vpi_put_value(p_vpi_value val, int flags);
        virtual vpiHandle vpi_handle(int code);
        virtual vpiHandle vpi_iterate(int code);
        virtual vpiHandle vpi_index(int idx);
        virtual void vpi_get_delays(p_vpi_delay del);
        virtual void vpi_put_delays(p_vpi_delay del);

        // Objects may have destroyer functions of their own. If so,
        // then this virtual method will return a POINTER to that
        // function. The pointer is used to "delete" the object, which
        // is why the function itself cannot be a method.
        typedef int (*free_object_fun_t)(vpiHandle);
        virtual free_object_fun_t free_object_fun(void);
    };
}

module :private;
