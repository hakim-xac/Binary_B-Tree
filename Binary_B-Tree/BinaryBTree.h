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
    private:

        // безопасно удаляет дерево
        static void deleteTree(Node* root)                             ;

        // считывает дерево в поток
        static std::stringstream readTree(const Node* const root)      ;

        // вычисляет размер дерева
        static int sizeTree(const Node* const root)                    ;

        // высчитывает высоту дерева
        static int heightTree(const Node* const root)                  ;

        // высчитывает среднюю высоту дерева
        static int middleHeightTree(const Node* const root, int level) ;

        //высчитывает хеш-сумму дерева
        static long long hashTree(const Node* const root)              ;

        // проверяет, является ли дерево, деревом поиска
        static bool isSearchTree(const Node* const root)               ;

        // создает АВЛ дерево поиска
        bool toAVL()                                                   ;

        // создает идеальное сбалансированное дерево поиска
        Node* toISDP(int left, int right)                              ;

        // заполняет массив случайными значениями
        bool fillVector(int size)                                      ;

        // добавляет ключ в дерево
        void insert(int key, Node** root)                            ;

    public:

        // удаляем не нужные конструкторы и операторы
        BinaryBTree() =                               delete;
        BinaryBTree(const BinaryBTree& bt) =              delete;
        BinaryBTree(BinaryBTree&& bt) =                   delete;
        BinaryBTree& operator =(const BinaryBTree& bt) =  delete;
        BinaryBTree& operator =(BinaryBTree&& bt) =       delete;

        // создает СДП дерево с количеством элементов size
        BinaryBTree(int size);

        // создает ИСДП дерево из дерева СДП
        BinaryBTree(BinaryBTree* bt);
        ~BinaryBTree();

        // возвращает размер дерева
        size_t size()		            const;

        // возвращает поток в который осуществлен вывод дерева
        std::stringstream print()	    const;

        // возвращает высоту дерева
        int height()		            const;

        // возвращает среднюю высоту дерева
        int middleHeight()	            const;

        // возвращает хеш-сумму дерева
        long long hash()	            const;

        // проверяет, является ли дерево, деревом поиска
        bool isSearch()                 const;

        // безопасно удаляет дерево
        void deleteTree()                    ;


    };

}