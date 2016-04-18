#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>

#define PP_NARG(...) PP_NARG_(__VA_ARGS__,PP_RSEQ_N()) /* 求参数个数 */
#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
                    __0,__1,__2,__3,__4,__5,__6,__7,__8,__9,_10, N,...) N
#define PP_RSEQ_N() \
                     13,12,11,10,9,8,7,6,5,4,3,2,1,0

int deletedirEx(int count, ...);

//delete dir
#define deletedir(...) deletedirEx(PP_NARG(__VA_ARGS__), __VA_ARGS__)


//delete dir
int deletedir1(char* dirpath);


//find string pos from back to front
int strrfind(char* source, char* str);


