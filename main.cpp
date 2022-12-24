/*#include <iostream>
using namespace std;

class Truck
{

private:
    string make;

public:
    Truck(string make) : make(make) {}

    static Truck *getTruck(string &make)
    {
        return new Truck(make);
    }

    Truck &operator=(const Truck &tr1)
    {
        // Item 11
        if (this == &tr1)
        {
            return *this;
        }
        else
        {
            this->make = tr1.make;
            return *this; // Item 10
        }
    }

    void toString()
    {
        cout << "Make: " << make << endl;
    }

protected:
    string getMake()
    {
        return make;
    }
};

class Driver : public Truck
{

private:
    string name;
    string departureCity;
    string arrivalCity;

public:
    Driver(string name, string departureCity, string arrivalCity, string make) : departureCity(departureCity),
                                                                                 arrivalCity(arrivalCity),
                                                                                 name(name),
                                                                                 Truck(make) {}

    ~Driver()
    {
        delete truck;
    }

    Driver(const Driver &drv1) : name(drv1.name),
                                 departureCity(drv1.departureCity),
                                 arrivalCity(drv1.arrivalCity),
                                 Truck(drv1) {}

    Driver &operator=(const Driver &drv1)
    {
        // Item 11
        if (this == &drv1)
        {
            return *this;
        }
        else
        {
            this->name = drv1.name;
            this->departureCity = drv1.departureCity;
            this->arrivalCity = drv1.arrivalCity;
            Truck::operator=(drv1); // Item 12
            return *this;           // Item 10
        }
    }

    void toString()
    {
        cout << "Name: " << name << " Departure City: " << departureCity << " Arrival City: " << arrivalCity << endl;
        cout << "Truck Make: " << getMake() << endl;
    }
};

class Uncopyable
{
protected:           // allow construction
    Uncopyable() {}  // and destruction of
    ~Uncopyable() {} // derived objects...
private:
    Uncopyable(const Uncopyable &); // ...but prevent copying
    Uncopyable &operator=(const Uncopyable &);
};

class Trail : private Uncopyable
{
private:
    int number;
    int capacity;

public:
    Trail(int number, int capacity) : number(number), capacity(capacity) {}

    void toString()
    {
        cout << "Number of trails: " << number << " Capacity of one trail: " << capacity << endl;
    }
};

int main(int, char **)
{
    cout << "Item 4:" << endl;
    Driver d1("Mihai", "Arad", "Timisoara", "Volvo");
    Driver d2(d1);
    Driver d3 = d1;

    d1.toString();
    d2.toString();
    d3.toString();

    cout << "Item 5:" << endl;
    Truck tr1("Volvo");
    Truck tr2(tr1);

    tr1.toString();
    tr2.toString();

    cout << "Item 6:" << endl;
    Trail t1(2, 75);
    t1.toString();

    return 0;
}*/
//Tema 3
#define _HAS_AUTO_PTR_ETC 1
#include <iostream>
#include <memory>
using namespace std;
class Food
{

private:
    string name;
    float price;
    string allergens;

public:
    Food(string name, float price, string allergens) : name(name),
                                                       price(price),
                                                       allergens(allergens)
    {
    }

    Food(void);
    Food *createFood();
    void setName(string name)
    {
        this->name = name;
    }
    void setPrice(float price)
    {
        this->price = price;
    }
    void setAllergens(string allergens)
    {
        this->allergens = allergens;
    }

    Food &operator=(const Food &food1)
    {
        if (this == &food1)
        {
            return *this;
        }
        else
        {
            this->name = food1.name;
            this->price = food1.price;
            this->allergens = food1.allergens;
            return *this;
        }
    }

    string getName()
    {
        return this->name;
    }
};

Food *createFood(const string &name, float price, const string &allergens)
{
    return new Food(name, price, allergens);
}

// Aici incepe item 14
// Am creat un restaurant sa ca putem simula inchisul si deschisul lui
class Restaurant
{
private:
    string name;
    bool locked = false;

public:
    Restaurant(string name)
    {
        this->name = name;
    }

    Restaurant(const Restaurant &r)
    {
        this->name = r.name;
        this->locked = r.locked;
    }

    ~Restaurant() {}

    string getName()
    {
        return this->name;
    }

    bool getLocked()
    {
        return this->locked;
    }

    void setLocked(bool locked)
    {
        this->locked = locked;
    }

    void isRestaurantLocked()
    {
        if (this->locked)
            std::cout << "The Restaurant " << this->name << " is locked" << endl;
        else
            std::cout << "The Restaurant " << this->name << " is unlocked" << endl;
    }
};

// Mai jos am creat funcitile care ajute la inchisul si deschisul restaurantului
void lock(Restaurant &r)
{
    r.setLocked(true);
}

void unlock(Restaurant &r)
{
    r.setLocked(false);
}

// Si la final am creat o clasa chef care are dreptul sa deschisa si sa inchida restaurantul
class Chef
{
private:
    Restaurant &restaurant;

public:
    // Cand creeem un chef pentru un restarurant, aceste se pune pe locked
    Chef(Restaurant &r) : restaurant(r)
    {
        lock(restaurant);
    }
    // Iar cand chef-ul este distrus restaurantul devine unlocked
    ~Chef()
    {
        unlock(restaurant);
    }
};

int main()
{
    // Item 13
    auto_ptr<Food> f1(createFood("Paste carbonare", 30, "ou, lapte"));
    cout << f1->getName() << endl;
    auto_ptr<Food> f2(f1);
    cout << f2->getName() << endl;
    // Daca incercam sa rulam linia de cod urmatoare o sa ne rezulte segmentation fault
    // Pentru ca la linia anteriaore se sterge automat f1
    // cout << f1->getName() << endl;

    // Item 14
    //  La inceput restarantul este unlocked, iar apoi cand ii asignam un chef devine automat locked
    //  Si la "distrugerea" chef-ului el va fii unlocked din nou
    Restaurant restaurant("Students Pub");
    restaurant.isRestaurantLocked();
    std::cout << "\n";
    Chef Andrei(restaurant);
    restaurant.isRestaurantLocked();
    std::cout << "\n";

    return 0;
}