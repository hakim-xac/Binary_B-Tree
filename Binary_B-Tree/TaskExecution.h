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
        /// ������� ������ � ����������� ��������� count_tree
        /// </summary>
        static std::pair<BinaryBTree*, BinaryBTree*> create(int count_tree);

        /// <summary>
        /// ��������� �� ���������� ��������� �������
        /// </summary>
        bool checkIsTree();

        /// <summary>
        /// �������, ����������� �� ������� ������, ��������� � �����
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void print(const BTree* const tree);

        /// <summary>
        /// ��������� ������ � ��������� ������ � �����
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showReadTree(const BTree* const tree);

        /// <summary>
        /// ������� ���-����� � ������� � �����
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHashTree(const BTree* const tree);

        /// <summary>
        /// ������� ������ ������ � ������� � �����
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHeightTree(const BTree* const tree);

        /// <summary>
        /// ������� ������ ������
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showSizeTree(const BTree* const tree);

        /// <summary>
        /// ������� ������� ������ ������
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showMiddleHeightTree(const BTree* const tree);

        /// <summary>
        /// ������� ������ ��� ���������� �������
        /// </summary>
        template <typename BTree, typename = isBinaryTree_t<BTree>>
        static void showHeightAsNumberOfLevels(const BTree* const tree);

        /// <summary>
        /// �������� ������ �� �������
        /// </summary>
        BinaryBTree* selectTree(int index) const;

        /// <summary>
        /// ���� ������ ������
        /// </summary>
        BinaryBTree* selectTreeView();

        /// <summary>
        /// ��������� �������, � ����������� �� �������
        /// </summary>
        void functionLaunch() override;

        /// <summary>
        /// ������� �� ���������
        /// </summary>
        void quit()         const;

        /// <summary>
        /// ��������� ������ � ������ � �����
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
        push(bufferItem("������ � ������"s));
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
        push(bufferItem("����� ������"s));
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
        push(bufferItem("��� ����� ������:"s
            , std::to_string(tree->hash())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("������ ������:"s
            , std::to_string(tree->getHeightTree())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showSizeTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("������ ������:"s
            , std::to_string(tree->getSize())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showMiddleHeightTree(const BTree* const tree) {

        using namespace std::literals;

        push(delimiter('='));
        push(bufferItem("������� ������ ������:"s
            , std::to_string(tree->getMiddleHeight())));
        push(delimiter('='));
    }

    template <typename BTree, typename T2>
    void TaskExecution
        ::showHeightAsNumberOfLevels(const BTree* const tree) {

        if (tree->getTypeTree() == TypeTree::DBD) {

            using namespace std::literals;

            push(delimiter('='));
            push(bufferItem("������ ������, ��� ���������� �������:"s
                , std::to_string(tree->getHeightTreeNumberOfLevels())));
            push(delimiter('='));
            push(bufferItem("������� ������ ������, ��� ���������� �������:"s
                , std::to_string(tree->getMiddleHeightTreeNumberOfLevels())));
            push(delimiter('='));
        }
    }





}