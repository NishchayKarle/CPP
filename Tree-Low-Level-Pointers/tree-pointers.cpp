#include <iostream>
#include <memory>

using std::make_unique;
using std::unique_ptr;

struct node
{
    std::string str;
    bool isLeaf;
    node *parent;
    node *left;
    node *right;

    node(std::string s) : str(s), isLeaf(false), parent(nullptr), left(nullptr), right(nullptr){};

    void set_leaf(bool leaf)
    {
        isLeaf = leaf;
    }
};

struct Tree
{
    node *root;

    Tree()
    {
        root = new node("Can it Fly?");

        node *left = new node("Hawk");
        left->set_leaf(true);

        node *right = new node("Ox");
        right->set_leaf(true);

        root->left = left;
        root->right = right;
        left->parent = root;
        right->parent = root;
    }

    void insert_new_node(node *curr, std::string q, std::string a)
    {
        node *question = new node(q);

        node *animal = new node(a);
        animal->set_leaf(true);

        node *parent = curr->parent;
        question->left = animal;
        question->right = curr;
        question->parent = parent;

        if (parent->left == curr)
            parent->left = question;

        else
            parent->right = question;
    }

    void traverse()
    {
        node *temp = root;
        while (true)
        {
            if (temp->isLeaf)
            {
                std::cout << "Is it a " << temp->str << "?" << std::endl;
                std::string ans;
                std::getline(std::cin, ans);

                if (ans == "yes")
                    std::cout << "computer wins" << std::endl;

                else
                {
                    std::string q;
                    std::string a;
                    std::cout << "Q: "; 
                    std::getline(std::cin, q);
                    std::cout << "A: ";
                    std::getline(std::cin, a);
                    insert_new_node(temp, q, a);
                }
                break;
            }

            else
            {
                std::cout << temp->str << std::endl;
                std::string ans;
                std::getline(std::cin, ans);
                if (ans == "yes")
                    temp = temp->left;
                else
                    temp = temp->right;
            }
        }
    }

    void destroy(node *curr)
    {
        if (curr == NULL)
            return;

        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }

    ~Tree()
    {
        destroy(root);
    }
};

int main()
{
    Tree t;
    std::cout << "use 'yes' and 'no' as answers" << std::endl;
    std::string cont;
    do {
        t.traverse();
        std::cout << "do you want to continue?: ";
        getline(std::cin, cont);
    } while(cont == "yes");
    return 0;
}