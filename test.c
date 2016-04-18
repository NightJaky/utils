#include "utils.h"

void
foo(char *fmt, ...)
{
   va_list ap;
   int d;
   char c, *s;
	printf("111111:%s, ***=%c\n", fmt, *fmt);
   va_start(ap, fmt);
   while (*fmt)
//	   printf("%s, %c\n", fmt, *fmt);
       switch (*fmt++) {
       case 's':              /* string */
           s = va_arg(ap, char *);
           printf("string %s\n", s);
           break;
       case 'd':              /* int */
           d = va_arg(ap, int);
           printf("int %d\n", d);
           break;
       case 'c':              /* char */
           /* need a cast here since va_arg only
              takes fully promoted types */
           c = (char) va_arg(ap, int);
           printf("char %c\n", c);
           break;
       }
   va_end(ap);
}



int main()
{
	char* source = "abcdefg" ;
	char* test1  = "f";
	char* test2  = "de";
	char* test3  = "zz";
	char* test4  = "ab";

	char* p = "123";
	char* p1 = p;
	printf("p=%p, p1=%p\n", p, p1);
	p++;
	printf("p=%p, p1=%p\n", p, p1);

	
	printf("test1:%d\n", strrfind(source, test1));
	printf("test2:%d\n", strrfind(source, test2));
	printf("test3:%d\n", strrfind(source, test3));
	printf("test4:%d\n", strrfind(source, test4));

	//deletedir("111");
	deletedir1("111");
	
	return 0;




}
