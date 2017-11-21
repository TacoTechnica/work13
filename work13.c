#include<unistd.h>
#include<stdio.h>


int main() {

    const int READ = 0;
    const int WRITE = 1;

    int fds1[2]; // Parent write, child read
    int fds2[2]; // Parent read, child write
    int f;


    pipe( fds1 );
    pipe( fds2 );
    f = fork();

    // If Parent 
    if ( f == 0 ) {
        close( fds1[READ] );
        close( fds2[WRITE] );
        int num_to_send = 2500000;
        //char s[10] = "HIYA!";
        sleep(2); // makes parent BLOCK on Read!
        printf("Parent sending %d\n", num_to_send);
        write( fds1[WRITE], &num_to_send, sizeof(num_to_send));

        int received_num;
        read( fds2[READ], &received_num, sizeof(received_num) );
        printf("Parent received number from child: %d\n", received_num);
    } else {
    // If child
        close( fds1[WRITE] );
        close( fds2[READ] );
        int received_num;
        read( fds1[READ], &received_num, sizeof(received_num) );
        printf("Child Received: %d\n", received_num);
 
        // Math
        received_num *= 2;
        printf("Child Math'd: %d\n", received_num);

        sleep(1);
        write( fds2[WRITE], &received_num, sizeof(received_num));
        
    }
    return 0;
}
