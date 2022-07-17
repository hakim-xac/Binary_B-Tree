#include "Interface.h"
#include <string>

namespace KHAS {

    void Interface::showHeader()
    {
        // добавляет отформатированные строки в буфер
        using namespace std::literals;
        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Лабораторная работа:"s, "номер 3"s));
        pushToBuffer(bufferItem("Тема:"s, "Двоичное Б-дерево поиска (ДБД)"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Выполнил студент:"s, "Хакимов А.С."s));
        pushToBuffer(delimiter('='));

        // сбрасывает буфер на вывод в консоль
        show();
    }

    void Interface::readCommand()
    {
        std::cout << std::string(fieldWidth_, '_')
            << std::string(fieldWidth_, '\b')
            << "Введите команду:";

        // получаем один символ, остальное очищаем
        int cmd{ std::cin.get() };
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // определяем команду
        switch (cmd)
        {
        case 49: activeCommand_ = InputCommand::Print;      break; // 1 
        case 57: activeCommand_ = InputCommand::Exit;       break; // 9

        default: activeCommand_ = InputCommand::ErrorCommands;            
        }
        
    }

    Interface::~Interface()
    {
        // при уничтожении объекта, сбрасывает на вывод всё что есть у него в буфере
        show();
    }

    void Interface::show()
    {
        // сбрасывает буфер на стандартный вывод
        while (!buffer_.empty()) {

            std::cout << buffer_.front() << "\n";
            buffer_.pop();
        }
        std::flush(std::cout);
    }



    void Interface::showStatusBar()
    {
        // сбрасывает буфер на стандартный вывод

        if (!bufferStatusBar_.empty()) {
            push(delimiter('-'));
            while (!bufferStatusBar_.empty()) {
                std::cout << bufferStatusBar_.front() << "\n";
                bufferStatusBar_.pop();
            }
            std::flush(std::cout);
        }
    }

    InputCommand Interface::getActiveCommand() const
    {
        // возвращает активную команду
        return activeCommand_;
    }

    void Interface::clearActiveCommand()
    {
        // очищает активную команду
        activeCommand_ = InputCommand::NoCommand;
    }



    void Interface::view()
    {
        // запускает цикл и выполняет команды полученные от пользователя
        while (true) {

            // очищает экран
            system("cls");

            // выводит заголовок
            showHeader();

            // выполняет функции зависящие от полученной команды
            functionLaunch();

            // выводит результат функций
            showStatusBar();

            // выводит меню пользователю
            showMenu();

            // получает команду от пользователя
            readCommand();
        }
    }

}
