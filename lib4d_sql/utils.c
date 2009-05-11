#include <string.h>
#define isspace(x) (x==' ')
char *strstrip(char *s)
{
       size_t size;
       char *end;

       size = strlen(s);

       if (!size)
               return s;

       end = s + size - 1;
       while (end != s && isspace(*end))
               end--;
       *(end + 1) = '\0';

       while (*s && isspace(*s))
               s++;

       return s;
}