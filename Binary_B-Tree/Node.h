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
        int height{};


        Node(int value, int height = 1)
            : left(nullptr)
            , right(nullptr)
            , data(value)
            , height(height) {}

        Node() = delete;
    };

}