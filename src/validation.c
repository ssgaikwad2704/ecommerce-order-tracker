#include "validation.h"
#include "record.h"

int isValidId(int id) {
    return (id > 0) ? 1 : 0;
}

int isUniqueId(int id) {
    if (findOrderIndexById(id) == -1) {
        return 1;
    }
    return 0;
}

int isValidStatus(int status) {
    if (status >= STATUS_PENDING && status <= STATUS_RETURNED) {
        return 1;
    }
    return 0;
}