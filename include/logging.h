#ifndef LOGGING_H 
#define LOGGING_H


#define LOGGING_MAX_STRING_SIZE 256



uint32_t log_int_to_str(int num, char *str, uint32_t base);
void log_0(char *msg);
void log_1(char *msg, uint32_t int1);


#endif
