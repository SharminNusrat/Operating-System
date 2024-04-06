//8 processes will be created, and the printf statement will be executed 14 times...


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {

    int id;
    for(int i=0; i<3; i++) {
        id = fork();    
        printf("My child's id : %d. Hello Nusrat! I am from process: %d\n", id, getpid());
    }

    return 0;
}



/*

nusrat@nusrat:~/Documents/CSE401/fork$ ./a.out
My child's id : 5100. Hello Nusrat! I am from process: 5099
My child's id : 5101. Hello Nusrat! I am from process: 5099
My child's id : 5102. Hello Nusrat! I am from process: 5099
nusrat@nusrat:~/Documents/CSE401/fork$ My child's id : 0. Hello Nusrat! I am from process: 5100
My child's id : 5103. Hello Nusrat! I am from process: 5100
My child's id : 0. Hello Nusrat! I am from process: 5101
My child's id : 5104. Hello Nusrat! I am from process: 5101
My child's id : 0. Hello Nusrat! I am from process: 5102
My child's id : 5105. Hello Nusrat! I am from process: 5100
My child's id : 0. Hello Nusrat! I am from process: 5103
My child's id : 5106. Hello Nusrat! I am from process: 5103
My child's id : 0. Hello Nusrat! I am from process: 5104
My child's id : 0. Hello Nusrat! I am from process: 5105
My child's id : 0. Hello Nusrat! I am from process: 5106

*/