

/*
Клиент принимает с клавиатуры команды и передает их серверу. 
Сервер выполняет эти команды, результаты возвращаются клиенту, 
который записывает их в файл.
*/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    int fd;

    unlink("/home/twoxowt/Univer/sispoCourseWork/FIFO/firstGateway.txt");
    char * myfifo = "/home/twoxowt/Univer/sispoCourseWork/FIFO/firstGateway.txt";

    int fd1 = mkfifo(myfifo, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if(fd1 == -1){
      std::cout<<"Ошибка!\n";
      exit(0);
    }
    std::cout<<"Клиент подключился к каналу\n";

    char arr1[4], arr2[4];
    while (1)
    {
        std::cout<<"Введите команду:\n";
        std::cin>>arr2;
        fd = open(myfifo, O_WRONLY);
        write(fd, arr2, strlen(arr2)+1);
        close(fd);
        
    }
    return 0;
}
