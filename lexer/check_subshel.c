#include "lexer.h"
/**
 ** status_main - Core accessor for the global last exit status.
 ** @action: Operation selector (GET == 0 to read, SET == 1 to write).
 ** @value:  Pointer to int; on GET, receives current status; on SET,
 **          provides the new status value.
 **
 ** Uses a static variable to persist the last exit status across calls.
 ** Assumes @value is non-NULL.
 **
 ** Return: void.
 */
void    status_sub_main(int action, int *value)
{
    static int    last_status = 0;

    if (action == GET)
        *value = last_status;
    else if (action == SET)
        last_status = *value;
}
/**
 ** sub_get_status - Get the current last exit status.
 **
 ** Return: The stored status value.
 */

int    sub_get_status(void)
{
    int    value;

    status_sub_main(GET, &value);
    return (value);
}
/**
 ** status_set_sub - Update the last exit status.
 ** @value: New status to store.
 **
 ** Return: void.
 */

void    sub_set_status(int value)
{
    status_sub_main(SET, &value);
}