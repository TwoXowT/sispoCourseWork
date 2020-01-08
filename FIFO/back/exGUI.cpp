

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


char* fifo1 = "/home/twoxowt/Univer/sispoCourseWork/FIFO/firstGateway.txt";
char* fifo2 = "/home/twoxowt/Univer/sispoCourseWork/FIFO/secondGateway.txt";
char* fifo3 = "/home/twoxowt/Univer/sispoCourseWork/FIFO/thirdGateway.txt";
char* fifo4 = "/home/twoxowt/Univer/sispoCourseWork/FIFO/fourthGateway.txt";

int choose_gateway(int choose){
  int buf;
  switch(choose){
    case 1: buf = open(fifo1, O_WRONLY); break;
    case 2: buf = open(fifo2, O_WRONLY); break;
    case 3: buf = open(fifo3, O_WRONLY); break;
    case 4: buf = open(fifo4, O_WRONLY); break;
    default:

      std::cout<<"Шлюза с таким номером не существует\n Подключаемся к 1 шлюзу\n";
      buf = open(fifo1, O_WRONLY);
      break;
  }  
  close(buf);
  return buf;         
}


char* choose_gate(int gate){
  switch (gate){
    case 1: return fifo1;
    case 2: return fifo2;
    case 3: return fifo3;
    case 4: return fifo4;
    default: return fifo1;
  }

  
}




void menu(){
  std::cout<< "111-Открыть верхний створ\n"
                    "110-Закрыть верхний створ\n"
                    "121-Включить звуковой сигнал на верхнем створе\n"
                    "120-Отключить звуковой сигнал на верхнем створе\n"
                    "131-Включить визуальный сигнал на верхнем створе\n"
                    "130-Отключить визуальный сигнал на верхнем створе\n"
                    "190-Поднять шлюз вверх\n"
                    "211-Открыть нижний створ\n"
                    "210-Закрыть нижний створ\n"
                    "220-Включить звуковой сигнал на нижнем створе\n"
                    "221-Отключить звуковой сигнал на нижнем створе\n"
                    "231-Включить визуальный сигнал на нижнем створе\n"
                    "230-Отключить визуальный сигнал на нижнем створе\n"
                    "290-Опустить шлюз вниз\n"
                    "311-Прекратить работу шлюза\n"
                    "310-Возобновить работу шлюза\n"
                    "320-Увеличить скорость работы шлюза\n"
                    "321-Понизить скорость работы шлюза\n"
                    "999-Выбрать другой шлюз\n";
}

int main()
{
  unlink("/home/twoxowt/Univer/sispoCourseWork/FIFO/firstGateway.txt");
  unlink("/home/twoxowt/Univer/sispoCourseWork/FIFO/secondGateway.txt");
  unlink("/home/twoxowt/Univer/sispoCourseWork/FIFO/thirdGateway.txt");
  unlink("/home/twoxowt/Univer/sispoCourseWork/FIFO/fourthGateway.txt");
  int pip1 = mkfifo(fifo1, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  if(pip1 == -1){
      std::cout<<"Ошибка! Канал для 1 шлюза не создан\n";
      exit(0);
    }
  int pip2 = mkfifo(fifo2, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  if(pip2 == -1){
      std::cout<<"Ошибка! Канал для 2 шлюза не создан\n";
      exit(0);
    }
  int pip3 = mkfifo(fifo3, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  if(pip3 == -1){
      std::cout<<"Ошибка! Канал для 3 шлюза не создан\n";
      exit(0);
    }
  int pip4 = mkfifo(fifo4, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
  if(pip4 == -1){
      std::cout<<"Ошибка! Канал для 4 шлюза не создан\n";
      exit(0);
    }


    int fd;
    std::cout<<"Выберите шлюз для отправки команды:\n"
              "1. Первый шлюз\n"
              "2. Второй шлюз\n"
              "3. Третий шлюз\n"
              "4. Четвертый шлюз\n";
              int choose;
              std::cin>>choose;
              system("clear");
    char * myfifo = choose_gate(choose);
  
    std::cout<<"LOG: Диспетчер подключился к каналу\n";

    char arr1[4], arr2[4];

    while (1)
    {
        menu();
        std::cout<<"LOG: Введите команду:\n";
        std::cin>>arr2;
        int act = ((int)arr2[0]-'0')*100 +((int)arr2[1]-'0')*10 + ((int)arr2[2]-'0');
        if(act == 999){
          
          std::cout<<"Выберите шлюз для отправки команды:\n"
              "1. Первый шлюз\n"
              "2. Второй шлюз\n"
              "3. Третий шлюз\n"
              "4. Четвертый шлюз\n";
              
              std::cin>>choose;
              system("clear");
           
           continue;
        }
        
        switch (choose)
        {
        case 1: pip1 = open(fifo1,O_WRONLY);
                write(pip1, arr2, strlen(arr2)+1);
                close(pip1);
          break;
        case 2: pip2 = open(fifo2,O_WRONLY);
                write(pip2, arr2, strlen(arr2)+1);
                close(pip2);
          break;
        case 3:pip3 = open(fifo3,O_WRONLY);
                write(pip3, arr2, strlen(arr2)+1);
                close(pip3);
          break;
        case 4: pip4 = open(fifo4,O_WRONLY);
                write(pip4, arr2, strlen(arr2)+1);
                close(pip4);
          break;    
        default: pip2 = open(fifo2,O_WRONLY);
                write(pip2, arr2, strlen(arr2)+1);
                close(pip2);
                
          break;
        }

        sleep(2);
        system("clear");
        
    }
    return 0;
}
