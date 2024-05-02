#include<stdio.h>
#include<stdbool.h>

struct files{
    int file_no;
    int file_size;
    int ass_block;
};

struct blocks{
    int block_no;
    int block_size;
    int frag;
    bool occupied;
};

int main(){
    int num_blocks, num_files;
    
    printf("Enter the number of blocks:");
    scanf("%d", &num_blocks);
    
    struct blocks b[num_blocks];
    
    printf("Enter the number of files:");
    scanf("%d", &num_files);
    
    struct files f[num_files];
    
    printf("Start entering the block sizes...\n");
    
    for(int i = 0; i < num_blocks; i++){
        printf("Enter the block size of block %d:", i+1);
        scanf("%d", &b[i].block_size);
        b[i].block_no = i+1;
        b[i].occupied = false; // Initialize occupied flag
    }
    
    for(int i = 0; i < num_files; i++){
        printf("Enter the file size of file %d:", i+1);
        scanf("%d", &f[i].file_size);
        f[i].file_no = i+1;
    }
    
    // Arranging the blocks in ascending order of block sizes
    for(int i = 0; i < num_blocks; i++){
        for(int j = 0; j < num_blocks-i-1; j++){
            if(b[j].block_size > b[j+1].block_size){
                struct blocks temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }
    
    // Inserting files into blocks using first fit algorithm
    for(int i = 0; i < num_files; i++) {
        for(int j = 0; j < num_blocks; j++) {
            if(f[i].file_size <= b[j].block_size && !b[j].occupied) {
                f[i].ass_block = b[j].block_no;
                b[j].frag = b[j].block_size - f[i].file_size;
                b[j].occupied = true;
                break; // Found a block, no need to search further
            }
        }
    }
    
    // Printing the table
    
	printf("\tFile_No\t \tFile_Size\t \tBlock_No\t \tBlock_Size\t \tFragment\t\n");
	for(int i = 0; i < num_files; i++) {
	    int block_index = f[i].ass_block - 1; // Adjust index to access blocks array
	    printf("%d\t %d\t %d\t %d\t", f[i].file_no, f[i].file_size, f[i].ass_block, b[block_index].block_size);
	    if (b[block_index].occupied) {
		printf("\t %d\t\n", b[block_index].frag);
	    } else {
		printf("\t -\t\n"); // Print a placeholder for fragment if block is not occupied
	    }
	}


    return 0;
}

