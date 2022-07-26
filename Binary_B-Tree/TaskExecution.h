#pragma once
#include "Interface.h"
#include "BinaryBTree.h"
#include "Enums.h"

namespace KHAS {

    class TaskExecution : public Interface {

        template <typename BTree>
        using isBinaryTree_t = std::enable_if_t<std::is_same_v<BTree, BinaryBTree>>;

        BinaryBTree* avlTree100_;
        BinaryBTree* avlTree200_;
        BinaryBTree* avlTree300_;
        BinaryBTree* avlTree400_;
        BinaryBTree* avlTree500_;

        BinaryBTree* dbdTree100_;
        BinaryBTree* dbdTree200_;
        BinaryBTree* dbdTree300_;
        BinaryBTree* dbdTree400_;
        BinaryBTree* dbdTree500_;


    private:

        /// <summary>
        /// создает дерево с количеством элементов count_tree
        /// </summary>
        static std::pair<BinaryBTree*, BinaryBTree*> create(int count_tree);

        /// <summary>
        /// проверяет на валидность созданные деревья
        /// </summary>
        bool checkIsTree();

        /// <summary>
        /// выводит, необходимый по условию задачи, результат в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void print(const BTree* const tree);

        /// <summary>
        /// считывает дерево и добовляет данные в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showReadTree(const BTree* const tree);

        /// <summary>
        /// считает хеш-сумму и выводит в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHashTree(const BTree* const tree);

        /// <summary>
        /// считает высоту дерева и выводит в буфер
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHeightTree(const BTree* const tree);

        /// <summary>
        /// считает размер дерева
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showSizeTree(const BTree* const tree);

        /// <summary>
        /// выводит среднюю высоту дерева
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showMiddleHeightTree(const BTree* const tree);

        /// <summary>
        /// выводит высоту как количество уровней
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHeightAsNumberOfLevels(const BTree* const tree);

        /// <summary>
        /// выбирает дерево по индексу
        /// </summary>
        BinaryBTree* selectTree(int index) const;

        /// <summary>
        /// меню выбора дерева
        /// </summary>
        BinaryBTree* selectTreeView();

        /// <summary>
        /// выполняет функцию, в зависимости от команды
        /// </summary>
        void functionLaunch() override;

        /// <summary>
        /// выходит из программы
        /// </summary>
        void quit()         const;

        /// <summary>
        /// добавляет данные о дереве в буфер
        /// </summary>
        void printView();



    public:
        TaskExecution();
        ~TaskExecution();
        void showMenu() const override;

    };



    template<typename BTree, typename T2>
    inline void TaskExecution::print(const BTree* const tree)
    {
        using namespace std::literals;

        push(delimiter('-'));
        push(bufferItem("Данные о дереве"s));
        push(delimiter('-'));

        showReadTree(tree);
        showSizeTree(tree);
        showHashTree(tree);
        showHeightTree(tree);
        showMiddleHeightTree(tree);
        showHeightAsNumberOfLevels(tree);
        showStatusBar();

    }

    template<typename BTree, typename T2>
    inline void TaskExecution::showReadTree(const BTree* const tree)
    {
        using namespace std::literals;

        std::stringstream ss{ tree->print() };

        push(delimiter('='));
        push(bufferItem("Вывод дерева"s));
        push(delimiter('='));

        std::string first{}, second{}, third{}, fourth{}, fiveth{};
        do {

            ss >> first >> second >> third >> fourth >> fiveth;
            if (ss.good()) {
                push(bufferItem(
                    first
                    , second
                    , third
                    , fourth
                    , fiveth));
            }
        } while (ss.good());
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showHashTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Хеш сумма дерева:"s
            , std::to_string(tree->hash())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Высота дерева:"s
            , std::to_string(tree->getHeightTree())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showSizeTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Размер дерева:"s
            , std::to_string(tree->getSize())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showMiddleHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("Средняя высота дерева:"s
            , std::to_string(tree->getMiddleHeight())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showHeightAsNumberOfLevels(const BTree* const tree) {

        if (tree->getTypeTree() == TypeTree::DBD) {

            using namespace std::literals;

            push(delimiter('='));
            push(bufferItem("Высота дерева, как количество уровней:"s
                , std::to_string(tree->getHeightTreeNumberOfLevels())));
            push(delimiter('='));
            push(bufferItem("Средняя высота дерева, как количество уровней:"s
                , std::to_string(tree->getMiddleHeightTreeNumberOfLevels())));
            push(delimiter('='));
        }
    }





}