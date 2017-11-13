#include<my_global.h>
#include<mysql.h>

int main()
{
	printf("current myclient version is %s\n",mysql_get_client_info());
	return 0;	
	
}
