#pragma once

namespace KHAS {

    class Node {

    public:

        // указатель на левое дерево
        Node* left{ nullptr };

        // указатель на правое дерево
        Node* right{ nullptr };

        // данные
        int data{};

        // уровень баланса
        int balance{};


        Node(int value, int balance = 0)
            : left(nullptr)
            , right(nullptr)
            , data(value)
            , balance(balance) {}

        Node() = delete;
    };

}