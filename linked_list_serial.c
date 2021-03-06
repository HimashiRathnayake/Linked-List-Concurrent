#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "list_node_s.h"
#include "functions.h"

#define MAX 65535
#define MIN 0
#define n 1000
#define m 10000
#define sample_size 100

float m_member_count;
float m_insert_count;
float m_delete_count;
int members;
int inserts;
int deletes;
char operations_list[m][7];

float time_per_sample(){

    struct list_node_s my_list;
    struct list_node_s *pointer;

    my_list.data = 1;
    my_list.next = NULL;
  
    pointer = &my_list;

    int *random_array_pointer = getRandom();

    for(int loop = 0; loop < n; loop++) {
        int var = *(loop + random_array_pointer);
        Insert(var, &pointer);
    }

    for(int loop1=0; loop1 < members; loop1++){
        strcpy(operations_list[loop1], "Member");
    }

    for(int loop2=members; loop2 < members + inserts; loop2++){
        strcpy(operations_list[loop2], "Insert");
    }

    for(int loop3 = members + inserts; loop3 < members + inserts + deletes; loop3++){
        strcpy(operations_list[loop3], "Delete");
    }

    shuffle(operations_list, m);

    clock_t begin = clock();

    for(int loop = 0; loop < m; loop++) {
        int var = rand() % (MAX + 1 - MIN) + MIN;

        if(strcmp(operations_list[loop], "Member") == 0){
            Member(var, pointer);
        } else if(strcmp(operations_list[loop], "Insert") == 0){
            Insert(var, &pointer);
        } else if(strcmp(operations_list[loop], "Delete") == 0){
            Delete(var, &pointer);
        }
    }

    clock_t end = clock();
    float time_taken = ((float)(end-begin)) / CLOCKS_PER_SEC;
    return time_taken;

}

int main(int argc, char* argv[]) {

    float time_array[sample_size];
    
    printf( "Enter member, insert, delete count : ");
    scanf("%f %f %f", &m_member_count, &m_insert_count, &m_delete_count);

    members = (int)(m_member_count*m);
    inserts = (int)(m_insert_count*m);
    deletes = (int)(m_delete_count*m);

    for (int i = 0; i < sample_size; i++){

        float sample_time = time_per_sample();
        time_array[i] = sample_time;
        printf( "%f \n", sample_time);

    }

    float mean = get_mean(time_array, sample_size);
    float std = get_std(time_array, sample_size, mean);

    printf("\n%lf %1f\n", mean, std);

    return 0;

}