# LinkedListConcurrent
Implement Linked List in C with Concurrent Programming

Serial linked list
Compile: gcc -g -Wall -o .\linked_list_serial .\linked_list_serial.c  .\insert.c .\member.c .\delete.c .\functions.c
Run: .\linked_list_serial

Mutex based linked list
Compile: gcc -g -Wall -o .\linked_list_mutex .\linked_list_mutex.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread`
Run: .\linked_list_mutex <Thread Count>

Read-write lock based linked list
Compile: gcc -g -Wall -o .\linked_list_rw_lock .\linked_list_rw_lock.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread
Run: .\linked_list_rw_lock <Thread Count>

