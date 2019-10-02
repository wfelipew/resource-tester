#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * Author: William Felipe Welter <william.welter@4linux.com.br>
 * GPL-3 License (2019)
 */


int main (int argc, char* argv[]){

	char *mem_ptr,*temp_ptr;
	int mem_size_mb;
	size_t  mem_size_bytes;


	int mem_block_size=1024;
	int total_blocks;
	int block_count;
	char random_text[1024];

	if(argc<2){
		printf("Error: Need number of megabytes of memory to fill\n");
		printf("Syntax: memory-fill <MEM_SIZE_IN_MEGABYTES> \n");
		exit(1);
	}

	printf("Starting the memory fill test With: %sMB\n",argv[1]);

	mem_size_mb = atoi(argv[1]);
	mem_size_bytes = ( (size_t) mem_size_mb * 1024 ) * 1024;
	printf("Trying to allocate %dMB (%lu bytes)\n",mem_size_mb,mem_size_bytes);
	mem_ptr=malloc(mem_size_bytes);

	if(mem_ptr == NULL){
		printf("Error: Failed to allocate requested memory\n");
		exit(1);
	}

	printf("Memory succesfully allocated %dMB (%lu bytes)\n",mem_size_mb,mem_size_bytes);

	printf("Trying to filling %dMB (%lu bytes)\n",mem_size_mb,mem_size_bytes);

	total_blocks = mem_size_bytes / mem_block_size;
	temp_ptr = mem_ptr;
	for(block_count=0;block_count<total_blocks;block_count++){
		if(block_count % 1024){
			printf("\t Progress: %dMB of %dMB\r",block_count/1024, mem_size_mb);
		}
		strcpy(temp_ptr,random_text);
		temp_ptr+=1024;
	}

	printf("Memory Successfully Filled %dMB (%lu bytes)\n",mem_size_mb,mem_size_bytes);

	printf("\nPress any key to free allocated memory:");
	getchar();

	free(mem_ptr);

	printf("\nTest complete - Press any key to exit:");
	getchar();
	exit(0);

}
