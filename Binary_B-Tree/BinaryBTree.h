#pragma once

#include "Node.h"
#include "Enums.h"
#include <sstream>
#include <vector>

namespace KHAS {

    class BinaryBTree {

    private:

        // ������ � �������
        std::vector<int> vec_buffer_;

        // ������� ������
        Node* root_;

        // ��� ������
        TypeTree typeTree_;
    private:

        // ��������� ������� ������
        static void deleteTree(Node* root)                             ;

        // ��������� ������ � �����
        static std::stringstream readTree(const Node* const root)      ;

        // ��������� ������ ������
        static int sizeTree(const Node* const root)                    ;

        // ����������� ������ ������
        static int getHeightTree(const Node* const root)               ;

        // ����������� ������� ������ ������
        static int middleHeightTree(const Node* const root, int level) ;

        //����������� ���-����� ������
        static long long hashTree(const Node* const root)              ;

        // ���������, �������� �� ������, ������� ������
        static bool isSearchTree(const Node* const root)               ;

        // ������� ��� ������ ������
        bool toAVL()                                                   ;

        // ��������� ������ ���������� ����������
        bool fillVector(int size)                                      ;

        static int getHeight(const Node* const root)                   ;
        static Node* rotateLeft(Node* root)                            ;
        static Node* rotateRight(Node* root)                           ;
        static void fixNodeHeight(Node* root)                          ;
        static int getBalanceFactor(Node* root)                        ;
        static Node* balanceTree(Node* root)                           ;
        static Node* insertToAVL(int key, Node* root)                  ;
    public:

        // ������� �� ������ ������������ � ���������
        BinaryBTree() =                                   delete;
        BinaryBTree(const BinaryBTree& bt) =              delete;
        BinaryBTree(BinaryBTree&& bt) =                   delete;
        BinaryBTree& operator =(const BinaryBTree& bt) =  delete;
        BinaryBTree& operator =(BinaryBTree&& bt) =       delete;

        // ������� ��� ������ � ����������� ��������� size
        BinaryBTree(int size);

        // ������� ���� ������ �� ������ ���
        BinaryBTree(BinaryBTree* bt);
        ~BinaryBTree();

        // ���������� ������ ������
        size_t size()		            const;

        // ���������� ����� � ������� ����������� ����� ������
        std::stringstream print()	    const;

        // ���������� ������ ������
        int getHeight()		            const;

        // ���������� ������� ������ ������
        int middleHeight()	            const;

        // ���������� ���-����� ������
        long long hash()	            const;

        // ���������, �������� �� ������, ������� ������
        bool isSearch()                 const;

        // ��������� ������� ������
        void deleteTree()                    ;
        // ����������� ������ ������
        int getHeightTree()             const;


    };

}