#include "BinaryBTree.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>


namespace KHAS {

    void BinaryBTree::deleteTree(Node* root)
    {
        if (root) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }

    std::stringstream BinaryBTree::readTree(const Node* const root)
    {
        if (!root) return std::stringstream{};
        std::stringstream ss;
        ss << readTree(root->left).str();
        ss << root->data << " ";
        ss << readTree(root->right).str();
        return ss;
    }

    int BinaryBTree::sizeTree(const Node* const root)
    {
        // ���� Node == nullptr
        if (!root) return 0;
        // ����� 1 + ������(����� Node) + ������(������ Node)
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int BinaryBTree::heightTree(const Node* const root)
    {
        // ���� Node == nullptr �� ���������� 0
        if (!root) return 0;
        // ���������� ������ ������ ������
        int left_height{ heightTree(root->left) };
        // ���������� ������ ������� ������
        int right_height{ heightTree(root->right) };

        // ���������� ������� ������ �� ������ � ������� ������ � ��������� �������, �.�. +1
        return (left_height > right_height ? left_height : right_height) + 1;		
    }

    int BinaryBTree::middleHeightTree(const Node* const root, int level)
    {
        // ���� Node == nullptr �� ���������� 0
        if (!root) return 0;
        // ���������� ������� ������ ������ � ������� ������ ������ ������� �� +1
        return level 
            + middleHeightTree(root->left, level + 1)
            + middleHeightTree(root->right, level + 1);
    }

    long long BinaryBTree::hashTree(const Node* const root)
    {
        // ���� Node == nullptr  �� ���������� 0.
        if (!root) return 0;

        using out_type = long long;

        // ���������� ���-����� ������ + ���-����� ������� ������ + ������
        return (
            static_cast<out_type>(root->data)
            + hashTree(root->left)
            + hashTree(root->right) );

    }

    bool BinaryBTree::isSearchTree(const Node* const root)
    {
        if(root && (
            (root->left && (root->data <= root->left->data || isSearchTree(root->left)))
            || (root->right && (root->data >= root->right->data || !isSearchTree(root->right)))
            )){
            return false;
        }
        return true;
    }

    bool BinaryBTree::toAVL()
    {
        if (vec_buffer_.size() == 0) return false;

        for (auto&& it: vec_buffer_) {
            insert(it, &root_);            
        }
        return true;
    }


    Node* BinaryBTree::toISDP(int left, int right)
    {
        // ��������� ������� � �������

        // ���� ����� ������� ������, �� ��� �� ���������, ���������� nullptr
        if (left > right) return nullptr;

        int size{ static_cast<int>(vec_buffer_.size()) };

        if (size == 0) return nullptr;

        // ���� ������ ������� ������ ������� �������, ��� ������ 0, �� ������� nullptr
        if (right >= size || left < 0) return nullptr;

        int middle{ left + ((right - left) / 2) };

        // ������� Node � ������� �� ������ ������� �� ��������� "middle".
        Node* nd{ new (std::nothrow) Node(vec_buffer_[middle]) };

        // ���� Node �� ��������, �� ������� nullptr
        if (!nd) return nullptr;

        // ������ ������� ����� � ������ Node
        nd->left = toISDP(left, middle - 1);
        nd->right = toISDP(middle + 1, right);

        // ���������� ��������� �� ��������� Node
        return nd;

    }

    bool BinaryBTree::fillVector(int size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-10000, 10000);
        


        for (int i{}, ie{ size }; i != ie; ++i) {

            auto tmp{ dist(gen) };
            while (std::find(vec_buffer_.begin(), vec_buffer_.end(), tmp) != vec_buffer_.end()) {
                tmp = dist(gen);
            }
            vec_buffer_.emplace_back(tmp);
        }     


        if (vec_buffer_.size() != size) {
            return false;
        }
        return true;
    }

    void BinaryBTree::insert(int key, Node** root)
    {
        while (*root) {
            if (key < (*root)->data) root = &(*root)->left;
            else if (key > (*root)->data) root = &(*root)->right;
            else return;
        }
        if (*root == nullptr) *root = new (std::nothrow) Node(key);
    }

    BinaryBTree::BinaryBTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::AVL) {

        vec_buffer_.reserve(size);

        if (!fillVector(size)) {
            std::cout << "������! ���������� ������� ����! " << std::endl;
            system("pause");
            exit(1);
        }

        if (!toAVL()) {
            std::cout << "������! ���������� ������� ������! " << std::endl;
            system("pause");
            exit(1);
        }

    }

    BinaryBTree::BinaryBTree(BinaryBTree* bt)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::ISDP) {

        if (bt == this) return;

        vec_buffer_ = bt->vec_buffer_;

        root_ = toISDP(0, static_cast<int>(vec_buffer_.size() - 1));
    }

    BinaryBTree::~BinaryBTree()
    {
        if(root_) deleteTree(root_);
    }

    size_t BinaryBTree::size() const
    {
        return sizeTree(root_);
    }

    std::stringstream BinaryBTree::print() const
    {        
        return readTree(root_);
    }

    int BinaryBTree::height() const
    {
        return heightTree(root_);
    }

    int BinaryBTree::middleHeight() const
    {
        return middleHeightTree(root_, 1) / sizeTree(root_);
    }

    long long BinaryBTree::hash() const
    {
        return hashTree(root_);
    }

    bool BinaryBTree::isSearch() const
    {
        return isSearchTree(root_);
    }
    void BinaryBTree::deleteTree()
    {
        deleteTree(root_);
    }
}