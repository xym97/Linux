#include"comm.h"


int main()
{
	int shmid = getShm(0);
	char* buf = NULL;
	buf = shmat(shmid, NULL, 0);//将物理内存的一块映射到虚拟地址空间上
	
	int count = 0;
	while(count++  < 15){
		printf("client say :%s\n", buf);
		sleep(1);
	}
	//
	shmdt(buf);//解除虚拟地址空间与 之前映射的物理内存之间的关系
	
	return 0;
}
