#include "main.h"
#include "logging.h"
#include "uart.h"


// declare a static array in memory to hold the output of print functions
// This has to be done because the string version of numbers will make the
// resulting log strings longer than the original buffer passed to the log function
static char logging_buffer[LOGGING_MAX_STRING_SIZE];



// convert integer to string representation in decimal. Return number of characters added to given buffer
uint32_t log_int_to_str(int num, char *str, uint32_t base)
{
    int rem;
    uint32_t begin, end, i = 0;
    char temp;

    // if 0, then short circuit the process
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }

    // store digits in reverse order then reverse the string at the end
    // TODO: This does not work yet because division isn't linked in correctly!!
    while (num > 0)
    {
        rem = num % base;
        str[i++] = rem > 9 ? ((rem - 10) + 'a') : (rem + '0');
        num = num / base;
    }


    if (base == 16)
    {
        str[i++] = 'x';
        str[i++] = '0'; 
    }

    //now reverse the string
    begin = 0;
    end = i;
    while (end > begin)
    {
        temp = str[begin];
        str[begin] = str[end];
        str[end] = temp;

        end--;
        begin++;
    }

    //return the number of digits 'printed'
    return i;
}



// log string with no arguments
void log_0(char *msg)
{
    UART_writestring(msg);
}


// log with one argument
void log_1(char *msg, uint32_t int1)
{
    uint32_t idx = 0;

    while (msg[idx] != '\0')
    {
        // look for %x or %d to indicate placement of integer argument in the string
        if (msg[idx]  == '%' && msg[idx-1] != '\\') 
        {
            if (msg[idx+1] == 'd')
            {
                idx += log_int_to_str(int1, &logging_buffer[idx], 10); //convert to string base 10
            }
            else if (msg[idx+1] == 'x')
            {
                idx += log_int_to_str(int1, &logging_buffer[idx], 16); //convert to string base 16
            }
            else
            {
                logging_buffer[idx] = msg[idx]; //if character after % doesn't match d or x, then just print the % in the string
            }
        }
        else  //otherwise just copy the next character
        {
            logging_buffer[idx] = msg[idx];
        }
        
        idx++;
    }

    //add new line and end of string character
    logging_buffer[idx] = '\n';
    logging_buffer[idx] = '\r';
    logging_buffer[idx] = '\0';

    //finally write the log to uart
    UART_writestring(logging_buffer);
}

