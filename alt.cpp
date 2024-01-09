#include<algorithm>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<map>

struct Item {
  std::string name;
  int val;
  int wgt;
  int amt;
  bool is_craftable;

  Item(std::string x, int y, int z, bool a) {
    name = x;
    val = y;
    wgt = z;
    is_craftable = a;
  }

  ~Item(){};

};

struct Person {
  std::string name;
  int hp;
  int money;
  std::vector<Item*> inv;

  Person() {
    name = "Mike";
    hp = 100;
    money = 1000;
  }

  ~Person(){};

  void fight(Person* person1, Person* person2) {
    person1->hp-=10;
    person2->hp-=10;
  }

  void addItem(Item* item) {
    inv.push_back(item);
  }

  void removeItem(int item_address) {
    inv[item_address] = 0;
  }

};

struct stockPointers {
  Item* apples = new Item("Apples", 5, 1, false);
  Item* jacket = new Item("Jacket", 10, 5, true);
  Item* bananas = new Item("Bananas", 10, 1, false);
};

struct Market {
  bool is_open;
  std::vector<Item*> stock;

  Market() {};

  ~Market() {};

  void buyItem(Item* product, Person* buyer, Person* seller) {
    buyer->money -= product->val;
    buyer->inv.push_back(product);
  }

  void sellItem(Item* product, Person* buyer, Person* seller) {
    seller->money += product->val;
    seller->inv.erase(std::remove_if(seller->inv.begin(), seller->inv.end(), [product](Item* ptr) { 
			    return ptr == product; 
			    }), seller->inv.end());
  }

};

int main() {
  stockPointers sp;
  Item* a = sp.apples;
  Person* b = new Person();
  std::cout<<b->name<<" has $"<<b->money<<" and wants to buy "<<a->name<<" for $"<<a->val<< std::endl;
  delete b;
  return 0;
}
