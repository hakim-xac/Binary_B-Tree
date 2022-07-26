#pragma once

#include "Node.h"
#include "Enums.h"
#include <sstream>
#include <vector>

namespace KHAS {

    class BinaryBTree {

    private:

        // массив с данными
        std::vector<int> vec_buffer_;

        // вершина дерева
        Node* root_;

        // тип дерева
        TypeTree typeTree_;

        // был ли рост дерева, если Б-дерево
        bool isGrowth_;

    private:

        // безопасно удаляет дерево
        static void deleteTree(Node* root);

        // считывает дерево в поток
        static std::stringstream readTree(const Node* const root);

        // вычисляет размер дерева
        static int sizeTree(const Node* const root);

        // высчитывает высоту дерева
        static int getHeightTree(const Node* const root);

        // высчитывает высоту дерева, как количество уровней
        static int heightTreeNumberOfLevels(const Node* const root, bool isGrowth);

        // высчитывает среднюю высоту дерева
        static int middleHeightTree(const Node* const root, int level);

        // высчитывает среднюю высоту дерева, как количество уровней
        static int middleHeightTreeNumberOfLevels(const Node* const root, int level);

        //высчитывает хеш-сумму дерева
        static long long hashTree(const Node* const root);


        // создает АВЛ дерево поиска
        bool toAVL();

        // заполняет массив случайными значениями
        bool fillVector(int size);

        static int getHeight(const Node* const root);
        static Node* rotateLeft(Node* root);
        static Node* rotateRight(Node* root);
        static void fixNodeHeight(Node* root);
        static int getBalanceFactor(Node* root);
        static Node* balanceTree(Node* root);
        static Node* insertToAVL(int key, Node* root);



        void insertToDBD(int key, Node*& root, InsertTypeInBTree itib);


    public:

        // удаляем не нужные конструкторы и операторы
        BinaryBTree() = delete;
        BinaryBTree(const BinaryBTree& bt) = delete;
        BinaryBTree(BinaryBTree&& bt) = delete;
        BinaryBTree& operator =(const BinaryBTree& bt) = delete;
        BinaryBTree& operator =(BinaryBTree&& bt) = delete;

        // создает СДП дерево с количеством элементов size
        BinaryBTree(int size);

        // создает ИСДП дерево из дерева СДП
        BinaryBTree(BinaryBTree* bt);
        ~BinaryBTree();

        // возвращает размер дерева
        size_t getSize()		        const;

        // возвращает поток в который осуществлен вывод дерева
        std::stringstream print()	    const;

        // возвращает высоту дерева
        int getHeightTree()		        const;

        // возвращает среднюю высоту дерева
        int getMiddleHeight()	        const;

        // возвращает хеш-сумму дерева
        long long hash()	            const;

        // безопасно удаляет дерево
        void deleteTree();

        // высчитывает высоту дерева, как количество уровней
        int getHeightTreeNumberOfLevels() const;

        // высчитывает среднюю высоту дерева, как количество уровней
        int getMiddleHeightTreeNumberOfLevels() const;

        // возвращает тип дерева
        TypeTree getTypeTree()          const;



    };

}