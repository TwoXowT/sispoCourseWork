#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
using namespace std;

class Gateway{
    private: 
        bool topAlignment;         // Верхний створ открыт\закрыт
        bool bottomAlignment;      // Нижний створ открыт\закрыт
        bool soundSignalTop;       // Наличие звукового сигнала вверх\низ
        bool soundSignalBottom;
        bool visualSignalTop;      // Наличие визуального сигнала вверх\низ
        bool visualSignalBottom;
        bool active;               // Состояние терминала рабочее\нерабочее
        bool available;            // Доступность шлюза свободен\в работе
        int speed;                 // Скорость слива\наполнения шлюза водой
        bool top;                  // Шлюз ждет сверху
        bool bottom;               // Шлюз ждет снизу

    public:

    //Изначально шлюзы ждут вверху канала
    Gateway(){
        topAlignment = true;
        bottomAlignment = false;
        soundSignalTop = true;
        soundSignalBottom = true;
        visualSignalTop = true;
        visualSignalBottom = true;
        active = true;
        available = true;
        speed = 2;
        top = true; 
        bottom = false;
    }


    // геттеры
    bool getTopAlignment(){
        return topAlignment;
    }
    bool getBottomAlignment(){
        return bottomAlignment;
    }
    bool getSoundSignalTop(){
        return soundSignalTop;
    }
    bool getSoundSignalBottom(){
        return soundSignalBottom;
    }
    bool getVisualSignalTop(){
        return visualSignalTop;
    }
    bool getVisualSignalBottom(){
        return visualSignalBottom;
    }
    bool getActive(){
        return active;
    }
    bool getAvailable(){
        return available;
    }
    int getSpeed(){
        return speed;
    }

    bool getTop(){
        return top;
    }

    bool getBottom(){
        return bottom;
    }

     bool isAvailable(){return available;}


    //сеттеры
    void setTopAlignment(bool val){
        topAlignment =  val;
    }
    void setBottomAlignment(bool val){
        bottomAlignment = val;
    }
    void setSoundSignalTop(bool val){
        soundSignalTop = val;
    }
    void setSoundSignalBottom(bool val){
        soundSignalBottom = val;
    }
    void setVisualSignalTop(bool val){
        visualSignalTop = val;
    }
    void setVisualSignalBottom(bool val){
        visualSignalBottom = val;
    }
    void setActive(bool val){
        active = val;
    }
    void setAvailable(bool val){
        available = val;
    }

    
    void setSpeed(bool val){

        if(speed == 0){
            std::cout<<"Скорость перекачки воды мгновенная\n";
            return;
        }

        if(val){
            speed++;
            std::cout<<"Скорость перекачки воды в шлюзе увеличена "<<speed<<"сек.  \n";
            return;
        }
        if(!val && (speed > 0)){
            speed--;
            std::cout<<"Скорость перекачки воды в шлюзе уменьшена "<<speed<<"сек.  \n";
            return;
        }
    }
    void setTop(bool val){
        top = val;
    }
    void setBottom(bool val){
        bottom = val;
    }

    //TO DO Звуковой и визуальный сигнал
   
    //Переправить корабль 
    void smuggle(){


        // Проверка на работоспособность шлюза
        if(!getActive()){
            return perror("LOG: Шлюз не работает ");
        }

        // Проверка на доступность шлюза 
        if(!isAvailable()){
            return perror("LOG: Шлюз занят");
        }

        setAvailable(false);

        // Если оба створа закрыты тогда спуск или залив воды
        if(!getTopAlignment() && !getBottomAlignment()){
            if(getTop()){
                setTop(false);
                sleep(speed);
                setBottom(true);
                setBottomAlignment(true);
                setAvailable(true);
                std::cout<<"Шлюз опустил уровень воды\n";
                return;
            }

            if(getBottom()){
                setBottom(false);
                sleep(speed);
                setTop(true);
                setTopAlignment(true);
                setAvailable(true);
                std::cout<<"Шлюз поднял уровень воды\n";
                return;
                
            }
        }

        // Переправа сверху вниз
        if(getTopAlignment() && !getBottomAlignment() ){
            setTopAlignment(false);
            setTop(false);
            sleep(speed);
            setBottom(true);
            setBottomAlignment(true);
            setAvailable(true);
            std::cout<<"Шлюз опустил уровень воды и открыл нижний створ\n";
            return;

        }
        // переправа снизу вверх
        if(!getTopAlignment() && getBottomAlignment() ){
            setBottomAlignment(false);
            setBottom(false);
            sleep(speed);
            setTop(true);
            setTopAlignment(true);
            setAvailable(true);
            std::cout<<"Шлюз поднял уровень воды и открыл верхний створ\n";
            return;
        }

        
        perror("LOG: Ошибка при переправе");
    }


    // Ждать подачи корабля сверху
    void waitBottom(){

         // Проверка на работоспособность шлюза
        if(!getActive()){
            return perror("LOG: Шлюз не работает ");
        }

        // Проверка на доступность шлюза 
        if(!isAvailable()){
            return perror("LOG: Шлюз занят");
        }

        setAvailable(false);


        if(!getBottom()){
            setTopAlignment(false);
            setTop(false);
            sleep(speed);
            setBottom(true);
            setBottomAlignment(true);
            setAvailable(true);
            std::cout<<"Шлюз опустил уровень воды и открыл нтжний створ створ\n";
            return;
        }
        setAvailable(true);
        std::cout<<"Шлюз уже ждёт корабль внизу течения\n";
        return;
    }

    // Ждать подачи корабля снизу
    void waitTop(){


         // Проверка на работоспособность шлюза
        if(!getActive()){
            return perror("LOG: Шлюз не работает ");
        }

        // Проверка на доступность шлюза 
        if(!isAvailable()){
            return perror("LOG: Шлюз занят");
        }

        setAvailable(false);


        if(!getTop()){
            setBottomAlignment(false);
            setBottom(false);
            sleep(speed);
            setTop(true);
            setTopAlignment(true);
            setAvailable(true);
            std::cout<<"Шлюз поднял уровень воды и открыл верхний створ\n";
            return;
        }
        setAvailable(true);
        std::cout<<"Шлюз уже ждёт корабль вверху течения\n";
        return;
    }


    void action(int arrive){
        switch (arrive)
        {
        case 111:
            setTopAlignment(true);
            std::cout<<"Верхнйий створ открыт\n";
            break;
        case 110:
            setTopAlignment(false);
            std::cout<<"Верхнйий створ закрыт\n";
            break;
        case 121:
            setSoundSignalTop(true);
            std::cout<<"Звуковой сигнал верхнего створа включен\n";
            break;
        case 120:
            setSoundSignalTop(false);
            std::cout<<"Звуковой сигнал верхнего створа отключен\n";
            break;
        case 131:
            setVisualSignalTop(true);
            std::cout<<"Визуальный сигнал верхнего створа включен\n";
            break;
        case 130:
            setVisualSignalTop(false);
            std::cout<<"Звуковой сигнал верхнего створа отключен\n";
            break;
        case 190:
            waitTop();

            break;            
        case 211:
            setBottomAlignment(true);
            std::cout<<"Нижний створ открыт\n";
            break;
        case 210:
            setBottomAlignment(false);
            std::cout<<"Нижний створ закрыт\n";
            break;   
        case 221:
            setSoundSignalBottom(true);
            std::cout<<"Звуковой сигнал нижнего створа включен\n";
            break;
        case 220:
            setSoundSignalBottom(false);
            std::cout<<"Звуковой сигнал нижнего створа отключен\n";
            break;
        case 231:
            setVisualSignalBottom(true);
            std::cout<<"Звуковой сигнал нижнего створа включен\n";
            break;
        case 230:
            setVisualSignalBottom(false);
            std::cout<<"Звуковой сигнал нижнего створа отключен\n";
            break;        
        case 290:
            waitBottom();
            break;
        case 300:
            smuggle();
            break;    
        case 310:
            setActive(false);
            std::cout<<"Шлюз закрыт на техобслуживание\n";
            break;
        case 311:
            setActive(true);
            std::cout<<"Шлюз начал работу\n";
            break;
        case 320:
            setSpeed(false);        
            break;     
        case 321:
            setSpeed(true);
            break; 
        default:
            std::cout<<"Неверная команда\n";
            break;
        }
    }


};

int main()
{
    // объект шлюза 
    Gateway first;

    unlink("/home/twoxowt/Univer/Course/FIFO/firstGateway.txt");
    char * pipe = "/home/twoxowt/Univer/Course/FIFO/firstGateway.txt";
    
    // Creating the named file(FIFO)
    int fd;
    int fd1 = mkfifo(pipe, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if(fd1 == -1){
      std::cout<<"LOG: Канал передачи информации недоступен\n";
      exit(0);
    }

    std::cout<<"LOG: Шлюз подключился к каналу\n";

    char arrive[4], depart[4];

    while (1)
    {
       // std::cout<<"Введите команду:\n";
       // std::cin>>arr2;
       // fd = open(pipe, O_WRONLY);
       // write(fd, arr2, strlen(arr2)+1);
       // close(fd);
        
        // открыли для чтения
        fd = open(pipe, O_RDONLY);
        // считываем команду с канала
        read(fd, arrive, sizeof(arrive));
        std::cout<<"LOG: Пришла команда "<<arrive[0]<<arrive[1]<<arrive[2]<<endl;
        int act = ((int)arrive[0]-'0')*100 +((int)arrive[1]-'0')*10 + ((int)arrive[2]-'0');
        std::cout<<"LOG: Конвертация результат - "<<act<<endl;
        first.action(act);


        close(fd);
        

    }
    return 0;
}
