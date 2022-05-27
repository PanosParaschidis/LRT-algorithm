/* author: Paraschidis Panagiotis, 3164*/


#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "t_params.h"

#define set_total_computation_time 342
#define get_remaining_time 343

int main(){
	unsigned long long wait=0;
	int res,status;
	pid_t pid;
	struct t_params *temp=malloc(sizeof(struct t_params));
	res=syscall(set_total_computation_time,getpid(),2);
	while(wait<100000000){
		wait++;
	}
	if(res==0){
		printf("set computation time succeeded\n");
	}
	else{
		printf("set computation time failed\n");
	}

	res=syscall(get_remaining_time,getpid(),temp);
	if(res==0){
		printf("get time succeeded\n");
	}
	else{
		printf("get time failed\n");
	}

	pid=fork();
	if(pid>0){
		res=syscall(set_total_computation_time,pid,1);
		wait=0;
		while(wait<100000000){
		wait++;
	}
		if(res==0){
			printf("set computation time succeeded\n");
		}
		else{
			printf("set computation time failed\n");
		}
		res=syscall(get_remaining_time,pid,temp);
		if(res==0){
			printf("get time succeeded\n");
		}
			
		else{
			printf("get time failed\n");
		}

		res=syscall(set_total_computation_time,pid,10);
		wait=0;
		while(wait<100000000){
		wait++;
	}
		if(res==0){
			printf("set computation time succeeded\n");
		}
		else{
			printf("set computation time failed\n");
		}
		



		
	}
	else if(pid==0){
		res=syscall(set_total_computation_time,getpid(),3);
		wait=0;
		while(wait<100000000){
		wait++;
	}
	if(res==0){
		printf("set computation time succeeded\n");
	}
	else{
		printf("set computation time failed\n");
	}

		
	}


}