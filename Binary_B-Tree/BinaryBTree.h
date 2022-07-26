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

        // ��� �� ���� ������, ���� �-������
        bool isGrowth_;

    private:

        // ��������� ������� ������
        static void deleteTree(Node* root);

        // ��������� ������ � �����
        static std::stringstream readTree(const Node* const root);

        // ��������� ������ ������
        static int sizeTree(const Node* const root);

        // ����������� ������ ������
        static int getHeightTree(const Node* const root);

        // ����������� ������ ������, ��� ���������� �������
        static int heightTreeNumberOfLevels(const Node* const root, bool isGrowth);

        // ����������� ������� ������ ������
        static int middleHeightTree(const Node* const root, int level);

        // ����������� ������� ������ ������, ��� ���������� �������
        static int middleHeightTreeNumberOfLevels(const Node* const root, int level);

        //����������� ���-����� ������
        static long long hashTree(const Node* const root);


        // ������� ��� ������ ������
        bool toAVL();

        // ��������� ������ ���������� ����������
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

        // ������� �� ������ ������������ � ���������
        BinaryBTree() = delete;
        BinaryBTree(const BinaryBTree& bt) = delete;
        BinaryBTree(BinaryBTree&& bt) = delete;
        BinaryBTree& operator =(const BinaryBTree& bt) = delete;
        BinaryBTree& operator =(BinaryBTree&& bt) = delete;

        // ������� ��� ������ � ����������� ��������� size
        BinaryBTree(int size);

        // ������� ���� ������ �� ������ ���
        BinaryBTree(BinaryBTree* bt);
        ~BinaryBTree();

        // ���������� ������ ������
        size_t getSize()		        const;

        // ���������� ����� � ������� ����������� ����� ������
        std::stringstream print()	    const;

        // ���������� ������ ������
        int getHeightTree()		        const;

        // ���������� ������� ������ ������
        int getMiddleHeight()	        const;

        // ���������� ���-����� ������
        long long hash()	            const;

        // ��������� ������� ������
        void deleteTree();

        // ����������� ������ ������, ��� ���������� �������
        int getHeightTreeNumberOfLevels() const;

        // ����������� ������� ������ ������, ��� ���������� �������
        int getMiddleHeightTreeNumberOfLevels() const;

        // ���������� ��� ������
        TypeTree getTypeTree()          const;



    };

}