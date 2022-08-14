/*
Ranks First Fit, Next Fit, Best Fit, and Worst Fit memory management algorithms by 
time taken to complete allocating processes to fixed amount of holes
in memory.
*/

// Load in header file stdio.h
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

// RNG function that takes minimum number and includes max number.
int rand_incl(int min, int max)
{
	//srand (time(NULL));
	return min + rand() % (max+1 - min); 

}

void print_arr(int *int_arr, int arr_size)
{
	printf("|");
	int loop;	
	for(loop = 0; loop < arr_size; loop++)
	{
		printf(" %d |", int_arr[loop]);
	}
	printf("\n");
}

// Declare M input function
// Number of holes in physical memory.
int get_M()
{
	char line[12]; //12 is max # of digits of Int incl. newline char
	int m_int;
	printf ("How many holes in memory are there (what is M)?: ");
	fgets (line, sizeof(line), stdin);
	sscanf (line, "%d", &m_int);
	
	return m_int;
}

// Declare N input function
// Number of processes that need to be assigned memory
int get_N()
{
	char line[12]; //12 is max # of digits of Int incl. newline char
	int n_int;
	printf ("How many processes need to be assigned memory (what is N)?: ");
	fgets (line, sizeof(line), stdin);
	sscanf (line, "%d", &n_int);
	
	return n_int;
}

// Minimum size of blocks
int get_min_size_block()
{
	char line[12]; //12 is max # of digits of Int incl. newline char
	int min_size;
	printf ("What is minimum size of blocks? ");
	fgets (line, sizeof(line), stdin);
	sscanf (line, "%d", &min_size);

	return min_size;	
}

// Maximum size of blocks
int get_max_size_block()
{
	char line[12]; //12 is max # of digits of Int incl. newline char
	int max_size;
	printf ("What is maximum size of blocks? ");
	fgets (line, sizeof(line), stdin);
	sscanf (line, "%d", &max_size);

	return max_size;	
}

// First fit. Find first fit in given array, return index or -1
int first_fit_search(int *mem_arr, int mem_arr_size, int proc)
{
	int i;	
	for(i = 0; i < mem_arr_size; i++)
	{
		if(mem_arr[i] >= proc)
		{
			return i;
		}
	}
	return -1;
}


// Next fit. Find next fit in given array, return index or -1
int next_fit_search(int *mem_arr, int mem_arr_size, int proc, int start_pt)
{ //start_pt is 0-indexed
	int i;	
	int j;
	for(i = start_pt; i < (mem_arr_size+start_pt); i++)
	{	if(i < mem_arr_size)
		{
			j = i;
		
			if(mem_arr[j] >= proc)
			{
				return j;
			}
		} else if (i >= mem_arr_size) {
			j = i - mem_arr_size;
			if(mem_arr[j] >= proc)
			{
				return j;
			}
		}
	}
	return -1;
}

// Best fit. Find best fit in given array, return index or -1
int best_fit_search(int *mem_arr, int mem_arr_size, int proc)
{
	int size_best_fit_so_far;
	size_best_fit_so_far = 0;
	int j;
	j = -1;
	int i;	
	for(i = 0; i < mem_arr_size; i++)
	{
		if(mem_arr[i] >= proc)
		{
			if(size_best_fit_so_far == 0)
			{
				size_best_fit_so_far = mem_arr[i];
				j = i;
			} else if(size_best_fit_so_far > mem_arr[i])
			{
				size_best_fit_so_far = mem_arr[i];
				j = i;
			}
				
		}
	}
	return j;
}


// Worst fit. Find worst fit in given array, return index or -1
int worst_fit_search(int *mem_arr, int mem_arr_size, int proc)
{
	int size_worst_fit_so_far;
	size_worst_fit_so_far = 0;
	int j;
	j = -1;
	int i;	
	for(i = 0; i < mem_arr_size; i++)
	{
		if(mem_arr[i] >= proc)
		{
			if(size_worst_fit_so_far == 0)
			{
				size_worst_fit_so_far = mem_arr[i];
				j = i;
			} else if(size_worst_fit_so_far < mem_arr[i])
			{
				size_worst_fit_so_far = mem_arr[i];
				j = i;
			}
				
		}
	}
	return j;
}

// Assign process by subtracting from number in memory arr
void assign_mem_to_proc(int *mem_arr, int mem_to_assign_i, int proc)
{
	mem_arr[mem_to_assign_i] = mem_arr[mem_to_assign_i] - proc;
}

// Using holding container for procs in memory, have proc release 
// its memory back.
void release_mem_from_proc(int *mem_arr, int mem_released_i, int proc)
{
	mem_arr[mem_released_i] = mem_arr[mem_released_i] + proc;
}

// Function to test whether array is full of NULLs or has some value somewhere
int is_arr_null(int *arr, int arr_len)
{
	int i;
	for(i = 0; i < arr_len; i++)
	{
		if(arr[i] != 0)
		{
			return 0;
		}
	}
	return 1;
}

// Function to test whether a 2D array is full of NULLs or has some value somewhere
int is_twod_arr_null(int (*twod_arr)[2], int twod_arr_len)
{
	int i;
	for(i = 0; i < twod_arr_len; i++)
	{
		if(twod_arr[i][1] != 0)
		{
			return 0;
		}
	}
	return 1;
}

// Take given array, find what spots are filled with numbers other than 0, then return as arr
int find_filled_spots_arr(int *arr_to_analyze, int arr_to_analyze_len, int *arr_filled_spots)
{
	int i;
	int j = 0;
	for(i = 0; i < arr_to_analyze_len; i++)
	{
		if(arr_to_analyze[i] == 1)
		{
			arr_filled_spots[j] = i;
			j++;
		}
	}

	return j;
}

// Run First Fit algorithm
void first_fit_complete_run(int *mem_arr, int mem_arr_len, int *proc_arr, int proc_arr_len)
{
	printf("\nFIRST FIT ALGORITHM\n");
	//to hold processes as working in memory
	int flags[proc_arr_len][2]; //1st holds i in memory, 2nd holds proc val
	int i;
	int j;
	for (i = 0; i < proc_arr_len; i++)
	{
		for(j = 0; j < 2; j++)
		{
			flags[i][j] = 0;
		}
	}		
	//to hold processes too big to fit in memory holes
	
	int is_flags_arr_null = 0;
	int is_proc_arr_null = 0;	
	int filled_mem_blocks[mem_arr_len]; //keep track of which mem blocks hold process(es)
	for(i = 0; i < mem_arr_len; i++)
	{
		filled_mem_blocks[i] = 0;
	}
	int arr_filled_spots[mem_arr_len];
	int filled_spots_counter;
	while((is_proc_arr_null != 1) && (is_flags_arr_null != 1))
	{
		int where_put_in_mem_arr;
		
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] > 0)
			{
				where_put_in_mem_arr = first_fit_search(mem_arr, mem_arr_len, proc_arr[i]);
			} else {
				where_put_in_mem_arr = -1;
			}
			if(where_put_in_mem_arr != -1) //Time to give the proc some memory.
			{
				printf("Putting process %d of size %d in memory block %d.\n", (i+1), proc_arr[i], (where_put_in_mem_arr)+1);
				flags[i][0] = where_put_in_mem_arr;
				flags[i][1] = proc_arr[i];
				assign_mem_to_proc(mem_arr, where_put_in_mem_arr, proc_arr[i]);
				proc_arr[i] = 0;

				filled_mem_blocks[where_put_in_mem_arr] = 1;
				
				
				printf("Memory currently looks like this:\n");
				print_arr(mem_arr, mem_arr_len);
				printf("Processes look like this:\n");
				print_arr(proc_arr, proc_arr_len);
			}
		}
		printf("\n");	
		//Test to see if proc_arr is empty from program
		is_proc_arr_null = is_arr_null(proc_arr, proc_arr_len);
		is_flags_arr_null = is_twod_arr_null(flags, proc_arr_len);
		
		//If proc_arr is not empty, pick just one allocated memory block to release. All processes in this memory block must be released.
		//Pick random memory block
		if(is_proc_arr_null != 1 && is_flags_arr_null != 1)
		{
			for(i = 0; i < mem_arr_len; i++)
			{
				arr_filled_spots[i] = 0;
			}	
			filled_spots_counter = find_filled_spots_arr(filled_mem_blocks, mem_arr_len, arr_filled_spots);
			//mem_to_pluck
			if(filled_spots_counter > 0) //TODO check
			{
			j = rand_incl(0, (filled_spots_counter-1));
			printf("Releasing memory block %d.\n", (arr_filled_spots[j] + 1));
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][0] == arr_filled_spots[j] && flags[i][1] != 0) //Time to release one memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					filled_mem_blocks[flags[i][0]] = 0;
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
					
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
			}
		} else
		{
		//If proc_arr is empty, loop through all flags and confirm all memory was released.
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][1] != 0) //Time to release all memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
				
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
		}
		printf("\n");
	}

	//If there is something in proc_arr still, present it as rejected processes
	if(is_proc_arr_null != 1)
	{
		printf("The following processes were rejected (numbering starts from 1):\n");
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] != 0)
			{
				printf("Process #%d of size %d\n", i+1, proc_arr[i]);
			}
		}
	}
	printf("Done.\n");
}

// Run Next Fit algorithm
void next_fit_complete_run(int *mem_arr, int mem_arr_len, int *proc_arr, int proc_arr_len)
{
	printf("\nNEXT FIT ALGORITHM\n");
	//to hold processes as working in memory
	int flags[proc_arr_len][2]; //1st holds i in memory, 2nd holds proc val
	int i;
	int j;
	for (i = 0; i < proc_arr_len; i++)
	{
		for(j = 0; j < 2; j++)
		{
			flags[i][j] = 0;
		}
	}		
	//to hold processes too big to fit in memory holes
	
	int is_flags_arr_null = 0;
	int is_proc_arr_null = 0;	
	int filled_mem_blocks[mem_arr_len]; //keep track of which mem blocks hold process(es)
	for(i = 0; i < mem_arr_len; i++)
	{
		filled_mem_blocks[i] = 0;
	}
	int arr_filled_spots[mem_arr_len];
	int filled_spots_counter;
	while((is_proc_arr_null != 1) && (is_flags_arr_null != 1))
	{
		int where_put_in_mem_arr;
		int last_successful_put_i = 0;
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] > 0)
			{
				where_put_in_mem_arr = next_fit_search(mem_arr, mem_arr_len, proc_arr[i], last_successful_put_i);
			} else {
				where_put_in_mem_arr = -1;
			}
			if(where_put_in_mem_arr != -1) //Time to give the proc some memory.
			{
				last_successful_put_i = where_put_in_mem_arr;
				printf("Putting process %d of size %d in memory block %d.\n", (i+1), proc_arr[i], (where_put_in_mem_arr)+1);
				flags[i][0] = where_put_in_mem_arr;
				flags[i][1] = proc_arr[i];
				assign_mem_to_proc(mem_arr, where_put_in_mem_arr, proc_arr[i]);
				proc_arr[i] = 0;

				filled_mem_blocks[where_put_in_mem_arr] = 1;
				
				printf("Memory currently looks like this:\n");
				print_arr(mem_arr, mem_arr_len);
				printf("Processes look like this:\n");
				print_arr(proc_arr, proc_arr_len);
			}
		}
		printf("\n");	
		//Test to see if proc_arr is empty from program
		is_proc_arr_null = is_arr_null(proc_arr, proc_arr_len);
		is_flags_arr_null = is_twod_arr_null(flags, proc_arr_len);
		
		//If proc_arr is not empty, pick just one allocated memory block to release. All processes in this memory block must be released.
		//Pick random memory block
		if(is_proc_arr_null != 1 && is_flags_arr_null != 1)
		{
			for(i = 0; i < mem_arr_len; i++)
			{
				arr_filled_spots[i] = 0;
			}	
			filled_spots_counter = find_filled_spots_arr(filled_mem_blocks, mem_arr_len, arr_filled_spots);
			//mem_to_pluck
			if(filled_spots_counter > 0) //TODO check
			{
			j = rand_incl(0, (filled_spots_counter-1));
			printf("Releasing memory block %d.\n", (arr_filled_spots[j] + 1));
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][0] == arr_filled_spots[j] && flags[i][1] != 0) //Time to release one memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					filled_mem_blocks[flags[i][0]] = 0;
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
					
					
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
			}
		} else
		{
		//If proc_arr is empty, loop through all flags and confirm all memory was released.
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][1] != 0) //Time to release all memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
				
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
		}
		printf("\n");
	}

	//If there is something in proc_arr still, present it as rejected processes
	if(is_proc_arr_null != 1)
	{
		printf("The following processes were rejected (numbering starts from 1):\n");
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] != 0)
			{
				printf("Process #%d of size %d\n", i+1, proc_arr[i]);
			}
		}
	}
	printf("Done.\n");
}

// Run Best Fit algorithm
void best_fit_complete_run(int *mem_arr, int mem_arr_len, int *proc_arr, int proc_arr_len)
{
	printf("\nBEST FIT ALGORITHM\n");
	//to hold processes as working in memory
	int flags[proc_arr_len][2]; //1st holds i in memory, 2nd holds proc val
	int i;
	int j;
	for (i = 0; i < proc_arr_len; i++)
	{
		for(j = 0; j < 2; j++)
		{
			flags[i][j] = 0;
		}
	}		
	//to hold processes too big to fit in memory holes
	
	int is_flags_arr_null = 0;
	int is_proc_arr_null = 0;	
	int filled_mem_blocks[mem_arr_len]; //keep track of which mem blocks hold process(es)
	for(i = 0; i < mem_arr_len; i++)
	{
		filled_mem_blocks[i] = 0;
	}
	int arr_filled_spots[mem_arr_len];
	int filled_spots_counter;
	while((is_proc_arr_null != 1) && (is_flags_arr_null != 1))
	{
		int where_put_in_mem_arr;
		
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] > 0)
			{
				where_put_in_mem_arr = best_fit_search(mem_arr, mem_arr_len, proc_arr[i]);
			} else {
				where_put_in_mem_arr = -1;
			}
			if(where_put_in_mem_arr != -1) //Time to give the proc some memory.
			{
				printf("Putting process %d of size %d in memory block %d.\n", (i+1), proc_arr[i], (where_put_in_mem_arr)+1);
				flags[i][0] = where_put_in_mem_arr;
				flags[i][1] = proc_arr[i];
				assign_mem_to_proc(mem_arr, where_put_in_mem_arr, proc_arr[i]);
				proc_arr[i] = 0;

				filled_mem_blocks[where_put_in_mem_arr] = 1;
				
				printf("Memory currently looks like this:\n");
				print_arr(mem_arr, mem_arr_len);
				printf("Processes look like this:\n");
				print_arr(proc_arr, proc_arr_len);
			}
		}
		printf("\n");	
		//Test to see if proc_arr is empty from program
		is_proc_arr_null = is_arr_null(proc_arr, proc_arr_len);
		is_flags_arr_null = is_twod_arr_null(flags, proc_arr_len);
		
		//If proc_arr is not empty, pick just one allocated memory block to release. All processes in this memory block must be released.
		//Pick random memory block
		if(is_proc_arr_null != 1 && is_flags_arr_null != 1)
		{
			for(i = 0; i < mem_arr_len; i++)
			{
				arr_filled_spots[i] = 0;
			}	
			filled_spots_counter = find_filled_spots_arr(filled_mem_blocks, mem_arr_len, arr_filled_spots);
			//mem_to_pluck
			if(filled_spots_counter > 0) //TODO check
			{
			j = rand_incl(0, (filled_spots_counter-1));
			printf("Releasing memory block %d.\n", (arr_filled_spots[j] + 1));
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][0] == arr_filled_spots[j] && flags[i][1] != 0) //Time to release one memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					filled_mem_blocks[flags[i][0]] = 0;
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
					
					
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
			}
		} else
		{
		//If proc_arr is empty, loop through all flags and confirm all memory was released.
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][1] != 0) //Time to release all memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
				
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
		}
		printf("\n");
	}

	//If there is something in proc_arr still, present it as rejected processes
	if(is_proc_arr_null != 1)
	{
		printf("The following processes were rejected (numbering starts from 1):\n");
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] != 0)
			{
				printf("Process #%d of size %d\n", i+1, proc_arr[i]);
			}
		}
	}
	printf("Done.\n");
}

// Run Worst Fit algorithm
void worst_fit_complete_run(int *mem_arr, int mem_arr_len, int *proc_arr, int proc_arr_len)
{
	printf("\nWORST FIT ALGORITHM\n");
	//to hold processes as working in memory
	int flags[proc_arr_len][2]; //1st holds i in memory, 2nd holds proc val
	int i;
	int j;
	for (i = 0; i < proc_arr_len; i++)
	{
		for(j = 0; j < 2; j++)
		{
			flags[i][j] = 0;
		}
	}		
	//to hold processes too big to fit in memory holes
	
	int is_flags_arr_null = 0;
	int is_proc_arr_null = 0;	
	int filled_mem_blocks[mem_arr_len]; //keep track of which mem blocks hold process(es)
	for(i = 0; i < mem_arr_len; i++)
	{
		filled_mem_blocks[i] = 0;
	}
	int arr_filled_spots[mem_arr_len];
	int filled_spots_counter;
	while((is_proc_arr_null != 1) && (is_flags_arr_null != 1))
	{
		int where_put_in_mem_arr;
		
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] > 0)
			{
				where_put_in_mem_arr = worst_fit_search(mem_arr, mem_arr_len, proc_arr[i]);
			} else {
				where_put_in_mem_arr = -1;
			}
			if(where_put_in_mem_arr != -1) //Time to give the proc some memory.
			{
				printf("Putting process %d of size %d in memory block %d.\n", (i+1), proc_arr[i], (where_put_in_mem_arr)+1);
				flags[i][0] = where_put_in_mem_arr;
				flags[i][1] = proc_arr[i];
				assign_mem_to_proc(mem_arr, where_put_in_mem_arr, proc_arr[i]);
				proc_arr[i] = 0;

				filled_mem_blocks[where_put_in_mem_arr] = 1;
				
				printf("Memory currently looks like this:\n");
				print_arr(mem_arr, mem_arr_len);
				printf("Processes look like this:\n");
				print_arr(proc_arr, proc_arr_len);
			}
		}
		printf("\n");	
		//Test to see if proc_arr is empty from program
		is_proc_arr_null = is_arr_null(proc_arr, proc_arr_len);
		is_flags_arr_null = is_twod_arr_null(flags, proc_arr_len);
		
		//If proc_arr is not empty, pick just one allocated memory block to release. All processes in this memory block must be released.
		//Pick random memory block
		if(is_proc_arr_null != 1 && is_flags_arr_null != 1)
		{
			for(i = 0; i < mem_arr_len; i++)
			{
				arr_filled_spots[i] = 0;
			}	
			filled_spots_counter = find_filled_spots_arr(filled_mem_blocks, mem_arr_len, arr_filled_spots);
			//mem_to_pluck
			if(filled_spots_counter > 0) //TODO check
			{
			j = rand_incl(0, (filled_spots_counter-1));
			printf("Releasing memory block %d.\n", (arr_filled_spots[j] + 1));
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][0] == arr_filled_spots[j] && flags[i][1] != 0) //Time to release one memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					filled_mem_blocks[flags[i][0]] = 0;
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
					
					
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
			}
		} else
		{
		//If proc_arr is empty, loop through all flags and confirm all memory was released.
			for(i = 0; i < proc_arr_len; i++)
			{
				if(flags[i][1] != 0) //Time to release all memory.
				{
					printf("Removing process %d of size %d from memory block %d.\n", (i+1), flags[i][1], (flags[i][0]+1));
					release_mem_from_proc(mem_arr, flags[i][0], flags[i][1]);
					flags[i][0] = 0;
					flags[i][1] = 0;
					proc_arr[i] = 0;
				
					printf("Memory currently looks like this:\n");
					print_arr(mem_arr, mem_arr_len);
					printf("Processes look like this:\n");
					print_arr(proc_arr, proc_arr_len);
				}
			}
		}
		printf("\n");
	}

	//If there is something in proc_arr still, present it as rejected processes
	if(is_proc_arr_null != 1)
	{
		printf("The following processes were rejected (numbering starts from 1):\n");
		for(i = 0; i < proc_arr_len; i++)
		{
			if(proc_arr[i] != 0)
			{
				printf("Process #%d of size %d\n", i+1, proc_arr[i]);
			}
		}
	}
	printf("Done.\n");
}

// Create arrays
void create_arrays()
{
	int m_int;
	m_int = get_M();
	int n_int;
	n_int = get_N();
	int min_block_size;
	min_block_size = get_min_size_block();
	int max_block_size;
	max_block_size = get_max_size_block();	

	int memory_hole_arr[m_int]; 
	int process_arr[n_int]; 

	int i;
	for (i = 0; i < m_int; i++)
	{
		memory_hole_arr[i] = rand_incl(min_block_size, max_block_size);
	}
	int size_mem;
	size_mem = sizeof(memory_hole_arr)/sizeof(memory_hole_arr[0]);
	
	for (i = 0; i < n_int; i++)
	{
		process_arr[i] = rand_incl(min_block_size, max_block_size);
	}
	int size_proc;
	size_proc = sizeof(process_arr)/sizeof(process_arr[0]);
	
	printf("Here are the memory blocks available:\n");
	print_arr(memory_hole_arr, size_mem);	
	printf("Here are the processes waiting to be assigned:\n");
	print_arr(process_arr, size_proc);
	printf("\n");
	
	//Copy memory, processes to be put into first_fit run
	int memory_copy[size_mem];
	for (i = 0; i < size_mem; i++)
	{
		memory_copy[i] = memory_hole_arr[i];
	}
	int proc_copy[size_proc];
	for (i = 0; i < size_proc; i++)
	{
		proc_copy[i] = process_arr[i];
	}
	clock_t start_first, end_first;
	double cpu_time_used_first;
	start_first = clock();
	first_fit_complete_run(memory_copy, size_mem, proc_copy, size_proc);	
	end_first = clock();
	cpu_time_used_first = ((double) (end_first - start_first)) / CLOCKS_PER_SEC;

	//next_fit run
	for (i = 0; i < size_mem; i++)
	{
		memory_copy[i] = memory_hole_arr[i];
	}
	for (i = 0; i < size_proc; i++)
	{
		proc_copy[i] = process_arr[i];
	}
	clock_t start_next, end_next;
	double cpu_time_used_next;
	start_next = clock();
	next_fit_complete_run(memory_copy, size_mem, proc_copy, size_proc);	
	end_next = clock();
	cpu_time_used_next = ((double) (end_next - start_next)) / CLOCKS_PER_SEC;

	//best_fit run
	for (i = 0; i < size_mem; i++)
	{
		memory_copy[i] = memory_hole_arr[i];
	}
	for (i = 0; i < size_proc; i++)
	{
		proc_copy[i] = process_arr[i];
	}
	clock_t start_best, end_best;
	double cpu_time_used_best;
	start_best = clock();
	best_fit_complete_run(memory_copy, size_mem, proc_copy, size_proc);	
	end_best = clock();
	cpu_time_used_best = ((double) (end_best - start_best)) / CLOCKS_PER_SEC;
	
	//worst_fit run
	for (i = 0; i < size_mem; i++)
	{
		memory_copy[i] = memory_hole_arr[i];
	}
	for (i = 0; i < size_proc; i++)
	{
		proc_copy[i] = process_arr[i];
	}
	clock_t start_worst, end_worst;
	double cpu_time_used_worst;
	start_worst = clock();
	worst_fit_complete_run(memory_copy, size_mem, proc_copy, size_proc);	
	end_worst = clock();
	cpu_time_used_worst = ((double) (end_worst - start_worst)) / CLOCKS_PER_SEC;
	
	printf("Algorithm\tRuntime (sec)\n");
	printf("First Fit\t%f\n", cpu_time_used_first);
	printf("Next Fit\t%f\n", cpu_time_used_next);
	printf("Best Fit\t%f\n", cpu_time_used_best);
	printf("Worst Fit\t%f\n", cpu_time_used_worst);
}

// Declare main execution function
int main()
{
	printf("Program: Dynamic Memory Allocation\n");
	//Run main program
	create_arrays();
	//Declare end of program
	return 0;
}
