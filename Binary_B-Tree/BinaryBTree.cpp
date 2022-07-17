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
        // если Node == nullptr
        if (!root) return 0;
        // иначе 1 + размер(лева€ Node) + размер(права€ Node)
        return 1 + sizeTree(root->left) + sizeTree(root->right);
    }

    int BinaryBTree::heightTree(const Node* const root)
    {
        // если Node == nullptr то возвращаем 0
        if (!root) return 0;
        // определ€ем высоту левого дерева
        int left_height{ heightTree(root->left) };
        // определ€ем высоту правого дерева
        int right_height{ heightTree(root->right) };

        // возвращаем большую высоту из левого и правого дерева и добавл€ем текущую, т.е. +1
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

    long long BinaryBTree::hashTree(const Node* const root)
    {
        // если Node == nullptr  то возвращаем 0.
        if (!root) return 0;

        using out_type = long long;

        // возвращаем хеш-сумму левого + хеш-сумму правого дерева + данные
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
        // принимаем границы в массиве

        // если лева€ граница больше, то это не правильно, возвращаем nullptr
        if (left > right) return nullptr;

        int size{ static_cast<int>(vec_buffer_.size()) };

        if (size == 0) return nullptr;

        // если права€ граница больше размера массива, или меньше 0, то возврат nullptr
        if (right >= size || left < 0) return nullptr;

        int middle{ left + ((right - left) / 2) };

        // —оздаем Node с данными из €чейки массива со смещением "middle".
        Node* nd{ new (std::nothrow) Node(vec_buffer_[middle]) };

        // если Node не создалс€, то возврат nullptr
        if (!nd) return nullptr;

        // теперь создаем левую и правую Node
        nd->left = toISDP(left, middle - 1);
        nd->right = toISDP(middle + 1, right);

        // возвращаем указатель на созданную Node
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

    void BinaryBTree::rotation(Node* root, RotationTree rt)
    {
        if (rt == RotationTree::LeftRight) rotationLR(root);
        else if (rt == RotationTree::RightLeft) rotationRL(root);
        else rotationLLRR(root, rt);
    }

    void BinaryBTree::rotationLLRR(Node* root, RotationTree rt)
    {
        if (!root) return;

        Node* node{ nullptr };
        Node* left{ nullptr };
        Node* right{ nullptr };

        if (rt == RotationTree::Left) {
            left = root->left;
            right = node->right;
        }
        else if (rt == RotationTree::Right) {
            left = root->right;
            right = node->left;
        }
        else {
            return;
        }

        node = left;
        root->balance = 0;
        left = right;

        right = root;
        root = node;

    }

    void BinaryBTree::rotationLR(Node* root)
    {
        if (!root) return;

        Node* node{ root->left };
        Node* node2{ node->right };

        if (!node || !node2) return;

        root->balance = (node2->balance < 0 ? 1 : 0);
        node->balance = (node2->balance > 0 ? node->balance - 1 : 0);
        node2->balance = 0;

        root->left = node2->right;
        node->right = node2->left;
        node2->left = node;
        node2->right = root;
        root = node2;
    }

    void BinaryBTree::rotationRL(Node* root)
    {
        if (!root) return;

        Node* node{ root->right };
        Node* node2{ node->left };

        if (!node || !node2) return;

        node->balance = (node2->balance < 0 ? node->balance + 1 : 0);
        root->balance = (node2->balance > 0 ? root->balance - 1 : 0);

        node2->balance = 0;

        root->right = node2->left;
        node->left = node2->right;

        node2->left = root;
        node2->right = node;
        root = node2;

    }

    BinaryBTree::BinaryBTree(int size)
        : vec_buffer_()
        , root_(nullptr)
        , typeTree_(TypeTree::AVL) {

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
        , typeTree_(TypeTree::DBD) {

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