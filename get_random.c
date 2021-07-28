#define n 1000

int * getRandom() {

    static int  random_array[n];

    // Use current time as seed for random generator
    srand(time(0));
 
    for(int i = 0; i<n; i++)
        random_array[i] = rand() % (MAX + 1 - MIN) + MIN;

    return random_array;
} /* get a random array */