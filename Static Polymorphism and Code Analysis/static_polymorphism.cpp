#include <iostream>
#include <string>
#include <memory>

using namespace std;

template <class T>
struct Animal
{
    string name()
    {
        return static_cast<T *>(this)->get_name();
    }

    string eats()
    {
        return static_cast<T *>(this)->get_eats();
    }
};

struct Cat : Animal<Cat>
{
    string name = "cat1", eats = "meat";
    Cat(){};
    Cat(string name, string eats) : name(name), eats(eats){};
    string get_name()
    {
        return name;
    }

    string get_eats()
    {
        return eats;
    }
};

struct Dog : Animal<Dog>
{
    string name = "dog1", eats = "pedigree";
    Dog(){};
    Dog(string name, string eats) : name(name), eats(eats){};
    string get_name()
    {
        return name;
    }

    string get_eats()
    {
        return eats;
    }
};

int main()
{
    unique_ptr<Animal<Cat>> a = make_unique<Cat>();
    cout << a->name() << " eats " << a->eats() << endl;

    unique_ptr<Animal<Dog>> b = make_unique<Dog>();
    cout << b->name() << " eats " << b->eats() << endl;

    return 0;
}

// Yes. Using this method, the type (Cat or Dog) is known at compile time, so the compiler knows which function will be called at compile time.
// In the prev version, the compiler doesn't know which method is called at compile time.