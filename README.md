<h1>Linked Lists with Concurrent Programming</h1>

* API used for multi-threading: Pthreads

### 1. Serial linked list implementation

Compile: 

``gcc -g -Wall -o .\linked_list_serial .\linked_list_serial.c  .\insert.c .\member.c .\delete.c .\functions.c``

Run: 

``.\linked_list_serial``

### 2. Mutex based linked list implementation

Compile: 

``gcc -g -Wall -o .\linked_list_mutex .\linked_list_mutex.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread``

Run: 

``.\linked_list_mutex <Thread Count>``

### 3. Read-write lock based linked list implementation

Compile: 

``gcc -g -Wall -o .\linked_list_rw_lock .\linked_list_rw_lock.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread``

Run: 

``.\linked_list_rw_lock <Thread Count>``
