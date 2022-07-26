#include "TaskExecution.h"

namespace KHAS {
    std::pair<BinaryBTree*, BinaryBTree*> TaskExecution::create(int count_tree)
    {

        BinaryBTree* avl_tree{ new (std::nothrow) BinaryBTree(count_tree) };

        if (!avl_tree) return { nullptr, nullptr };

        BinaryBTree* dbd_tree{ new (std::nothrow) BinaryBTree(avl_tree) };

        if (!dbd_tree) {
            avl_tree->deleteTree();
            return { nullptr, nullptr };
        }

        return { avl_tree, dbd_tree };
    }

    bool TaskExecution::checkIsTree()
    {
        return (avlTree100_ != nullptr && avlTree200_ != nullptr
            && avlTree300_ != nullptr && avlTree400_ != nullptr
            && avlTree500_ != nullptr && dbdTree100_ != nullptr
            && dbdTree200_ != nullptr && dbdTree300_ != nullptr
            && dbdTree400_ != nullptr && dbdTree500_ != nullptr
            );
    }

    BinaryBTree* TaskExecution::selectTree(int index) const
    {
        BinaryBTree* bt{ nullptr };
        switch (index) {
        case 1:     bt = avlTree100_;  break;
        case 2:     bt = avlTree200_;  break;
        case 3:     bt = avlTree300_;  break;
        case 4:     bt = avlTree400_;  break;
        case 5:     bt = avlTree500_;  break;
        case 6:     bt = dbdTree100_;  break;
        case 7:     bt = dbdTree200_;  break;
        case 8:     bt = dbdTree300_;  break;
        case 9:     bt = dbdTree400_;  break;
        case 0:     bt = dbdTree500_;  break;
        default:    bt = nullptr;
        }
        return bt;
    }

    BinaryBTree* TaskExecution::selectTreeView()
    {
        using namespace std::literals;
        int index{};
        bool start{};
        bool isSelectBase{};
        BinaryBTree* bt{ nullptr };
        while (!isSelectBase || !start || std::cin.fail()) {
            std::cin.clear();
            if (start) {
                push(bufferItem("Ошибка ввода!"s));
                push(bufferItem("Повторите ввод!"s));
                std::cin.get();
            }
            push(delimiter('-'));
            push(bufferItem("Введите число от 0 до 9, в каком дереве хотим искать:"s));
            push(delimiter('-'));
            push(bufferItem("1 -"s, "АВЛ дерево размером в 100 элементов"s));
            push(bufferItem("2 -"s, "АВЛ дерево размером в 200 элементов"s));
            push(bufferItem("3 -"s, "АВЛ дерево размером в 300 элементов"s));
            push(bufferItem("4 -"s, "АВЛ дерево размером в 400 элементов"s));
            push(bufferItem("5 -"s, "АВЛ дерево размером в 500 элементов"s));
            push(delimiter('-'));
            push(bufferItem("6 -"s, "ДБД дерево размером в 100 элементов"s));
            push(bufferItem("7 -"s, "ДБД дерево размером в 200 элементов"s));
            push(bufferItem("8 -"s, "ДБД дерево размером в 300 элементов"s));
            push(bufferItem("9 -"s, "ДБД дерево размером в 400 элементов"s));
            push(bufferItem("0 -"s, "ДБД дерево размером в 500 элементов"s));
            push(delimiter('-'));
            showStatusBar();
            std::cin >> index;
            start = true;
            if (bt = selectTree(index)) isSelectBase = true;
        }

        std::cin.get();
        return bt;
    }

    void TaskExecution::functionLaunch()
    {
        // проверяет созданные деревья на валидность
        if (!checkIsTree()) {
            system("cls");
            std::cout << "Внимание! не удалось выделить память из кучи под данные!";
            exit(1);
        }

        // выполняет определенную пользователем команду
        switch (getActiveCommand()) {
        case InputCommand::Print:       printView();    break;
        case InputCommand::Exit:        quit();         break;
        default: break;
        }

        // очистка команды
        clearActiveCommand();
    }

    TaskExecution
        ::TaskExecution()
        : Interface()
        , avlTree100_(nullptr), avlTree200_(nullptr)
        , avlTree300_(nullptr), avlTree400_(nullptr)
        , avlTree500_(nullptr), dbdTree100_(nullptr)
        , dbdTree200_(nullptr), dbdTree300_(nullptr)
        , dbdTree400_(nullptr), dbdTree500_(nullptr) {

        // создает необходимые деревья
        std::tie(avlTree100_, dbdTree100_) = create(100);
        std::tie(avlTree200_, dbdTree200_) = create(200);
        std::tie(avlTree300_, dbdTree300_) = create(300);
        std::tie(avlTree400_, dbdTree400_) = create(400);
        std::tie(avlTree500_, dbdTree500_) = create(500);

    }

    TaskExecution::~TaskExecution()
    {
        // очищает деревья и обнуляет указатели
        avlTree100_->deleteTree();
        avlTree200_->deleteTree();
        avlTree300_->deleteTree();
        avlTree400_->deleteTree();
        avlTree500_->deleteTree();
        dbdTree100_->deleteTree();
        dbdTree200_->deleteTree();
        dbdTree300_->deleteTree();
        dbdTree400_->deleteTree();
        dbdTree500_->deleteTree();

        delete avlTree100_;     delete dbdTree100_;
        delete avlTree200_;     delete dbdTree200_;
        delete avlTree300_;     delete dbdTree300_;
        delete avlTree400_;     delete dbdTree400_;
        delete avlTree500_;     delete dbdTree500_;

        avlTree100_ = nullptr;  dbdTree100_ = nullptr;
        avlTree200_ = nullptr;  dbdTree200_ = nullptr;
        avlTree300_ = nullptr;  dbdTree300_ = nullptr;
        avlTree400_ = nullptr;  dbdTree400_ = nullptr;
        avlTree500_ = nullptr;  dbdTree500_ = nullptr;
    }

    void TaskExecution::quit() const
    {
        system("cls");
        exit(0);
    }

    void TaskExecution::printView()
    {
        BinaryBTree* bt{ selectTreeView() };
        print(bt);
    }

    void TaskExecution::showMenu() const
    {
        using namespace std::literals;

        // добавляет отформатированные строки в буфер
        pushToBuffer(delimiter('='));
        pushToBuffer(bufferItem("Меню"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("Клавиша"s, "Команда"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("1"s, "Распечать данные о дереве"s));
        pushToBuffer(delimiter('-'));
        pushToBuffer(bufferItem("9"s, "Закрыть приложение"s));
        pushToBuffer(delimiter('='));

        // сбрасывает на вывод в консоль
        show();
    }

}