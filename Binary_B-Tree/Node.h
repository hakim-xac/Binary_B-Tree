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
        int height{};


        Node(int value, int height = 1)
            : left(nullptr)
            , right(nullptr)
            , data(value)
            , height(height) {}

        Node() = delete;
    };

}