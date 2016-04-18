#include "utils.h"

#define DEBUG_UTILS


int deletedir1(char* dirpath);
int deletedir2(char* dirpath, char* file_type);

#define LOGE(...)     va_printfE(stderr, __VA_ARGS__);

static void va_printfE(FILE* flag, ...)
{
	va_list args;
	va_start(args, flag);
	vfprintf(flag, "%s", args);
	fprintf(flag, "errno=%d, strerror(errno)=%s\n", errno, strerror(errno));
	va_end(args);
}

int strrfind(char* source, char* str)
{
	int i;
	long lsource = strlen(source);
	long lstr    = strlen(str);
	source += lsource - 1;
	
	for (i = 0; i < lsource; ++i) {
		//printf("source=%s, str=%s\n", source, str);
		if (!strncmp(source, str, lstr)) {
			return (lsource - i - 1);
		}
		--source;
	}

	return -1;
}

int deletedirEx(int count, ...)
{
	char* dir_path_name = NULL;
	char* file_type = NULL;
	va_list args;
	va_start(args, count);	

	if (count > 0) {
		dir_path_name = va_arg(args, char*);
	}

	switch (count) {
		case 1 :			
			deletedir1(dir_path_name);
			break;
		case 2 : 
			file_type = va_arg(args, char*);
			deletedir2(dir_path_name, file_type);
			break;
		default : break;
	}
	va_end(args);



	return 0;//success
}

int deletedir1(char* dirpath)
{
	int ret = -1;
	DIR* dp;
	struct dirent *entry;
	struct stat statbuf;
	char* buf_dirpath;

	if (NULL == (dp = opendir(dirpath))) {
		//fprintf(stderr, "open dir \"%s\" failed, errno=%d, strerror(errno)=%s\n", \
		//		dir, errno, strerror(errno));
		LOGE(stderr, "open dir \"%s\" failed, errno=%d, strerror(errno)=%s\n", \
			dirpath, errno, strerror(errno));
		return -1;
	}

	//if (-1 == chdir(dirpath)) {
	//	fprintf(stderr, "chdir to \"%s\" filed, errno=%d, strerror(errno)=%s\n", \
	//			dirpath, errno, strerror(errno));
	//	return -1;
	//}

	while (entry = readdir(dp)) {
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
			continue;
		}

		buf_dirpath = (char*)malloc(strlen(dirpath) + 1 + strlen(entry->d_name));
		printf("p=%p\n", buf_dirpath);
		sprintf(buf_dirpath, "%s/%s", dirpath, entry->d_name);
		if (-1 == lstat(buf_dirpath, &statbuf)) {
			LOGE(stderr, "get file lstat failed, file_name=%s, error=%d, strerror(errno)=%s\n", \
					entry->d_name, errno, strerror(errno));
		}

		if (buf_dirpath) {
			if (statbuf.st_mode & S_IFDIR) {
				if (-1 == (ret = deletedir1(buf_dirpath))) {
					return ret;
				}
			}
			else {
				printf("delete file path=%p,%s\n", buf_dirpath, buf_dirpath);
				if (-1 == (ret = remove(buf_dirpath))) {
					LOGE("remove failed, %p, file path=%s\n", buf_dirpath, buf_dirpath);
					return ret;
				}
			}
			printf("1\n");
			printf("buf=%s\n", buf_dirpath);
			free(buf_dirpath);
			printf("2\n");
			buf_dirpath = NULL;
		}
		else {
			LOGE("malloc failed");
		}
	}
	closedir(dp);
	if (-1 == (ret = remove(dirpath))) {
		LOGE("remove dir failed, dir path=%s\n", buf_dirpath);
		return ret;
	}

	return 0;
}

int deletedir2(char* dirpath, char* file_type)
{
	DIR* dp;
	struct dirent *entry;
	struct stat statbuf;

	return -1;

}



