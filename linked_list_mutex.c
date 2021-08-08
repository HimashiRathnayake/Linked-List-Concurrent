#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "list_node_s.h"
#include "functions.h"
#include <pthread.h>

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
int thread_count;
pthread_mutex_t mutex;
struct list_node_s *pointer;
long thread;
pthread_t* thread_handles;

void* ThreadFunction(void* rank){
    long my_rank = (long) rank;

    int local_gap = m / thread_count;
    int local_start = local_gap * my_rank;
    int local_end = local_start + local_gap;

    for(int loop = local_start; loop < local_end; loop++) {
        int var = rand() % (MAX + 1 - MIN) + MIN;

        if(strcmp(operations_list[loop], "Member") == 0){
            pthread_mutex_lock(&mutex);
            Member(var, pointer);
            pthread_mutex_unlock(&mutex);
        } else if(strcmp(operations_list[loop], "Insert") == 0){
            pthread_mutex_lock(&mutex);
            Insert(var, &pointer);
            pthread_mutex_unlock(&mutex);
        } else if(strcmp(operations_list[loop], "Delete") == 0){
            pthread_mutex_lock(&mutex);
            Delete(var, &pointer);
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

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

    pthread_mutex_init(&mutex, NULL);

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, ThreadFunction, (void*) thread);

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    pthread_mutex_destroy(&mutex);

    clock_t end = clock();
    float time_taken = ((float)(end-begin)) / CLOCKS_PER_SEC;
    return time_taken;

}

int main(int argc, char* argv[]) {

    float time_array[sample_size];

    thread_count = strtol(argv[1], NULL, 10);

    thread_handles = malloc (thread_count*sizeof(pthread_t));

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

    free(thread_handles);

    return 0;

}