#include <iostream>
#include <memory>

using namespace std;

struct node
{
    node(int val) : val(val), left(nullptr), right(nullptr) {}

    int val;
    shared_ptr<node> left, right;
};

class tree
{
    shared_ptr<node> root;

private:
    void insert_node(int val, shared_ptr<node> &new_node)
    {
        if (new_node)
        {
            if (val < new_node->val)
                insert_node(val, new_node->left);
            else
                insert_node(val, new_node->right);
        }

        else
            new_node = make_shared<node>(val);
    };

    shared_ptr<node> &search_node(int val, shared_ptr<node> &new_node)
    {
        if (not root)
            return root;

        if (val == new_node->val)
            return new_node;

        else if (val < new_node->val)
            return search_node(val, new_node->left);

        else
            return search_node(val, new_node->right);
    }

    void destroy(shared_ptr<node> &new_node)
    {
        if (new_node)
        {
            destroy(new_node->left);
            destroy(new_node->right);
        }
    };

public:
    tree() : root(nullptr){};

    tree(const tree &tree_original)
    {
        shared_ptr<node> new_node = tree_original.root, new_root = make_shared<node>(0);

        new_root->val = new_node->val;
        root = move(new_root);

        while (new_node)
        {
            (*this).insert_node(new_node->val);

            if (new_node->left)
                (*this).insert_node(new_node->left->val);

            new_node = new_node->left;
        }

        new_node = tree_original.root;
        while (new_node)
        {
            (*this).insert_node(new_node->val);

            if (new_node->right)
                (*this).insert_node(new_node->right->val);

            new_node = new_node->right;
        }
    }

    void insert_node(int val)
    {
        return insert_node(val, root);
    }

    shared_ptr<node> &search_node(int val)
    {
        return search_node(val, root);
    }

    void destroy()
    {
        return destroy(root);
    }
};

int main()
{
    tree tree1;
    tree1.insert_node(123);
    tree1.insert_node(321);
    tree1.insert_node(456);
    tree1.insert_node(654);
    tree tree2 = tree1;

    return 0;
}