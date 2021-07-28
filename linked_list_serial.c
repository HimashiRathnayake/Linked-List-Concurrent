#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include "list_node_s.h"
#include "functions.h"

#define MAX 65535
#define MIN 0
#define n 1000
#define m 10000

int * getRandom() {

    static int  random_array[n];

    // Use current time as seed for random generator
    srand(time(0));
 
    for(int i = 0; i<n; i++)
        random_array[i] = rand() % (MAX + 1 - MIN) + MIN;

    return random_array;
} /* get a random array */

int main(int argc, char* argv[]) {

    struct list_node_s my_list;

    my_list.data = 1;
    my_list.next = NULL;

    struct list_node_s *pointer;
  
    pointer = &my_list;

    float m_member_count;
    float m_insert_count;
    float m_delete_count;

    printf( "Enter member, insert, delete count :");
    scanf("%f %f %f", &m_member_count, &m_insert_count, &m_delete_count);

    int *random_array_pointer = getRandom();

    for(int loop = 0; loop < n; loop++) {
        int var = *(loop + random_array_pointer);
        Insert(var, &pointer);
    }

    // printf("\nThis is my linked list 2: %1d\n", Member(*(6 + random_array_pointer), pointer));
    // printf("This is my linked list 2: %1d\n", Member(65536, pointer));

    // // printf("%d", (int)m_member_count * m);

    clock_t time;

    time = clock();

    for(int loop=0; loop < m_member_count * m; loop++){
        int var = rand() % (MAX + 1 - MIN) + MIN;
        Member(var, pointer);
        // printf("\nMember of %d is %d",var, Member(var, pointer));
    }

    for(int loop=0; loop < m_insert_count * m; loop++){
        int var = rand() % (MAX + 1 - MIN) + MIN;
        Insert(var, &pointer);
        // printf("\nMember of %d is %d",var, Member(var, pointer));
    }

    for(int loop=0; loop < m_delete_count * m; loop++){
        int var = rand() % (MAX + 1 - MIN) + MIN;
        Delete(var, &pointer);
        // printf("\nMember of %d is %d",var, Member(var, pointer));
    }
    
    time = clock() - time;

    float time_taken = ((float)time)/CLOCKS_PER_SEC; // in seconds
    printf("\nMember take time for run %d = %f seconds\n", (int)(m * m_member_count), time_taken);

    return 0;

}