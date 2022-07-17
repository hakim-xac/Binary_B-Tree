#pragma once

namespace KHAS {

    class Node {

    public:

        // ��������� �� ����� ������
        Node* left{ nullptr };

        // ��������� �� ������ ������
        Node* right{ nullptr };

        // ������
        int data{};

        // ������� �������
        int balance{};


        Node(int value, int balance = 0)
            : left(nullptr)
            , right(nullptr)
            , data(value)
            , balance(balance) {}

        Node() = delete;
    };

}