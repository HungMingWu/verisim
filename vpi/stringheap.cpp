module;
#include <assert.h>
#include <stdlib.h>
#include <string.h>

export module stringheap;

export {
    struct stringheap_cell;

    struct stringheap_s {
        struct stringheap_cell* cell_lst;
        unsigned cell_off;
    };

    /*
     * Allocate the string from the heap.
     */
    const char* strdup_sh(struct stringheap_s* hp, const char* str);

    void string_heap_delete(struct stringheap_s* hp);
}

module :private;

struct stringheap_cell {
    struct stringheap_cell* next;
};

# define PAGE_SIZE 8192
# define STRINGHEAP_SIZE (PAGE_SIZE - sizeof(struct stringheap_cell))

const char* strdup_sh(struct stringheap_s* hp, const char* txt)
{
    char* res;
    unsigned len = strlen(txt);
    assert(len < STRINGHEAP_SIZE);

    if (hp->cell_lst == 0) {
        hp->cell_lst = (stringheap_cell*)malloc(PAGE_SIZE);
        hp->cell_lst->next = 0;
        hp->cell_off = 0;
    }

    if ((STRINGHEAP_SIZE - hp->cell_off - 1) <= len) {
        struct stringheap_cell* tmp = (stringheap_cell*)malloc(PAGE_SIZE);
        tmp->next = hp->cell_lst;
        hp->cell_lst = tmp;
        hp->cell_off = 0;
    }

    res = (char*)(hp->cell_lst + 1);
    res += hp->cell_off;
    strcpy(res, txt);
    hp->cell_off += len + 1;

    return res;
}

void string_heap_delete(struct stringheap_s* hp)
{
    struct stringheap_cell* cur, * tmp;

    for (cur = hp->cell_lst; cur; cur = tmp) {
        tmp = cur->next;
        free((char*)cur);
    }
    hp->cell_lst = 0;
    hp->cell_off = 0;
}