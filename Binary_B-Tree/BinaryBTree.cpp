#include "BinaryBTree.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <cassert>


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
        if (root->left) ss << readTree(root->left).str();
        ss << root->data << " ";
        if (root->right) ss << readTree(root->right).str();
        return ss;
    }

    int BinaryBTree::sizeTree(const Node* const root)
    {
        // если Node == nullptr
        if (!root) return 0;
        // иначе 1 + размер(лева€ Node) + размер(права€ Node)
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int BinaryBTree::getHeightTreeNumberOfLevels() const
    {
        return heightTreeNumberOfLevels(root_, isGrowth_);
    }

    int BinaryBTree::getMiddleHeightTreeNumberOfLevels() const
    {
        return middleHeightTreeNumberOfLevels(root_, 1) / sizeTree(root_);
    }

    TypeTree BinaryBTree::getTypeTree() const
    {
        return typeTree_;
    }

    int BinaryBTree::getHeightTree(const Node* const root)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        int left_height{ getHeightTree(root->left) };
        int right_height{ getHeightTree(root->right) };

        return (left_height > right_height ? left_height : right_height) + 1;
    }

    int BinaryBTree::heightTreeNumberOfLevels(const Node* const root, bool isGrowth)
    {
        if (!root) return 0;
        int left_height{ heightTreeNumberOfLevels(root->left, isGrowth) };
        int right_height{};
        if (isGrowth) {
            right_height = heightTreeNumberOfLevels(root->right, isGrowth);
        }

        return (left_height > right_height ? left_height : right_height) + 1;
    }

    int BinaryBTree::middleHeightTree(const Node* const root, int level)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // возвращаем среднюю высоту левого и правого дерева мен€ем уровень на +1
        return level
            + middleHeightTree(root->left, level + 1)
            + middleHeightTree(root->right, level + 1);
    }

    int BinaryBTree::middleHeightTreeNumberOfLevels(const Node* const root, int level)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        if (root->height == 1) {
            return level
                + middleHeightTreeNumberOfLevels(root->right, level)
                + middleHeightTreeNumberOfLevels(root->left, level + 1);
        }

        return level
            + middleHeightTreeNumberOfLevels(root->left, level + 1)
            + middleHeightTreeNumberOfLevels(root->right, level + 1);
    }

    long long BinaryBTree::hashTree(const Node* const root)
    {
        // если Node == nullptr  то возвращаем 0.
        if (!root) return 0;

        using out_type = long long;

        // возвращаем хеш-сумму левого + хеш-сумму правого дерева + данные
        return (
            static_cast<out_type>(root->data)
            + hashTree(root->left)
            + hashTree(root->right));

    }

    bool BinaryBTree::toAVL()
    {
        if (vec_buffer_.size() == 0) return false;

        for (auto&& it : vec_buffer_) {
            root_ = insertToAVL(it, root_);
        }
        return true;
    }

    bool BinaryBTree::fillVector(int size)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist(-9999, 9999);



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

    int BinaryBTree::getHeight(const Node* const root)
    {
        if (!root) return 0;
        return root->height;
    }

    Node* BinaryBTree::rotateLeft(Node* root)
    {
        assert(root);
        Node* node{ root->right };
        assert(node);
        root->right = node->left;
        node->left = root;
        fixNodeHeight(root);
        fixNodeHeight(node);
        return node;
    }

    Node* BinaryBTree::rotateRight(Node* root)
    {
        assert(root);
        Node* node{ root->left };
        assert(node);
        root->left = node->right;
        node->right = root;
        fixNodeHeight(root);
        fixNodeHeight(node);
        return node;
    }

    void BinaryBTree::fixNodeHeight(Node* root)
    {
        assert(root);
        auto height_left{ getHeight(root->left) };
        auto height_right{ getHeight(root->right) };
        root->height = (height_left > height_right ? height_left : height_right) + 1;
    }

    int BinaryBTree::getBalanceFactor(Node* root)
    {
        assert(root);
        return getHeight(root->right) - getHeight(root->left);
    }

    Node* BinaryBTree::balanceTree(Node* root)
    {
        assert(root);
        fixNodeHeight(root);

        if (getBalanceFactor(root) == 2) {
            if (getBalanceFactor(root->right) < 0)
                root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        else if (getBalanceFactor(root) == -2) {
            if (getBalanceFactor(root->left) > 0)
                root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        return root;
    }

    Node* BinaryBTree::insertToAVL(int key, Node* root)
    {
        if (root == nullptr) {
            return new (std::nothrow) Node(key);
        }
        if (key < root->data)   root->left = insertToAVL(key, root->left);
        else                    root->right = insertToAVL(key, root->right);

        return balanceTree(root);
    }

    void BinaryBTree::insertToDBD(int key, Node*& root, InsertTypeInBTree itib)
    {
        static bool hr_{};
        if (itib == InsertTypeInBTree::Next) {
            isGrowth_ = hr_ = false;
        }

        if (root == nullptr) {
            root = new (std::nothrow) Node(key);
            assert(root);
            return;
        }
        if (root->data >= key) {
            insertToDBD(key, root->left, InsertTypeInBTree::Next);
            if (!isGrowth_) {
                hr_ = false;
                return;
            }
            if (root->height == 0) {

                Node* node{ root->left };
                assert(node);
                root->left = node->right;
                node->right = root;
                node->height = 1;
                isGrowth_ = false;
                hr_ = true;
                return;
            }
            root->height = 0;
            isGrowth_ = true;
            hr_ = false;
        }
        else {
            insertToDBD(key, root->right, InsertTypeInBTree::Next);
            if (isGrowth_) {
                root->height = 1;
                isGrowth_ = false;
                hr_ = true;
            }
            else if (hr_) {
                if (root->height != 1) {
                    hr_ = false;
                    return;
                }
                Node* node{ root->right };
                assert(node);
                root->height = 0;
                node->height = 0;
                root->right = node->left;
                node->left = root;
                root = node;
                isGrowth_ = true;
                hr_ = false;
            }
        }

    }

    BinaryBTree::BinaryBTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::AVL)
        , isGrowth_() {

        vec_buffer_.reserve(size);

        if (!fillVector(size)) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ Ѕј«”! " << std::endl;
            system("pause");
            exit(1);
        }

        if (!toAVL()) {
            std::cout << "ќЎ»Ѕ ј! Ќ≈¬ќ«ћќ∆Ќќ —ќ«ƒј“№ ƒ≈–≈¬ќ! " << std::endl;
            system("pause");
            exit(1);
        }

    }

    BinaryBTree::BinaryBTree(BinaryBTree* bt)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::DBD)
        , isGrowth_() {

        if (bt == this) return;

        vec_buffer_ = bt->vec_buffer_;

        if (vec_buffer_.size() == 0) {
            delete root_;
            return;
        }
        root_ = new (std::nothrow) Node(vec_buffer_[0]);
        assert(root_);

        for (int i{ 1 }, ie{ static_cast<int>(vec_buffer_.size()) }; i < ie; ++i) {
            insertToDBD(vec_buffer_[i], root_, InsertTypeInBTree::Begin);
        }

    }

    BinaryBTree::~BinaryBTree()
    {
        if (root_) deleteTree(root_);
    }

    size_t BinaryBTree::getSize() const
    {
        return sizeTree(root_);
    }

    std::stringstream BinaryBTree::print() const
    {
        return readTree(root_);
    }

    int BinaryBTree::getHeightTree() const
    {
        if (!root_) return 0;
        return getHeightTree(root_);
    }

    int BinaryBTree::getMiddleHeight() const
    {
        if (!root_) return 0;
        return middleHeightTree(root_, 1) / sizeTree(root_);
    }

    long long BinaryBTree::hash() const
    {
        if (!root_) return 0;
        return hashTree(root_);
    }
    void BinaryBTree::deleteTree()
    {
        deleteTree(root_);
    }
}