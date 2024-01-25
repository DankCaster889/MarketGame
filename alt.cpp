#include<algorithm>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<map>

struct Share {
  std::string owner;
  double val;

  Share() {
    owner = "NULL";
    val = 0;
  }

  ~Share(){};
};

struct defaultShare {
  Share* ptr = new Share();
};

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

struct stockPointers {
  Item* apples = new Item("Apples", 5, 1, false);
  Item* jacket = new Item("Jacket", 10, 5, true);
  Item* bananas = new Item("Bananas", 10, 1, false);

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

struct Company {
  std::string name;
  std::vector<Share*> shares;
  std::vector<Item*> inventory;
  double stockPrice;
  double totalValue;

  Company(const std::string& companyName, double initialStockPrice) : name(companyName), stockPrice(initialStockPrice) {};

  Share* assignShares(double val) {
    defaultShare ds;
    Share* defaultPtr = ds.ptr;
    Share* assignedShare;
    assignedShare = ds.ptr; 
    assignedShare->owner = name;
    assignedShare->val = val;
    return assignedShare;
  } 

  void issueShares(int numShares, double cost) {
    defaultShare ds;
    for (int i = 0; i < numShares; ++i) {
      Share* newShare = assignShares(cost);
      shares.push_back(newShare);
      totalValue += newShare->val;
    }

  }

  void stockInventory(Item* items) {
    stockPointers di;
    inventory.push_back(di.apples);
    inventory.push_back(di.jacket);
    inventory.push_back(di.bananas);
  }


  void displayInfo() const {
    std::cout<<"---------------------------\n";
    std::cout<<"Company:"<< name << "\n";
    std::cout<<"Stock Price: $"<< stockPrice << "\n";
    std::cout<<"Num of Shares:"<< shares.size() << "\n";
    std::cout<<"Shareholders:\n";
    int displayCount = std::min(static_cast<int>(shares.size()), 5);
    for (int i = 0; i < displayCount; ++i) {
      std::cout<<" Owner: "<< shares[i]->owner << ", Price: $" << shares[i]->val << "\n";
    }

    std::cout<<"---------------------------\n";
  }

  void sellShares(Company* buyer, int numShares) {
    if (numShares <= 0) {
      std::cout<< "Invalid" << std::endl;
      return;
    }
   if (numShares > shares.size()) {
      std::cout << "Not enough" << std::endl;
      return;
    }

    for (int i = 0; i < numShares; ++i) {
      buyer->shares.push_back(shares[i]);
      shares[i] = nullptr;
    }

    shares.erase(std::remove(shares.begin(), shares.end(), nullptr), shares.end());
    std::cout << "!!!!" << numShares << " shares sold to "<< buyer->name << "!!!!" << std::endl;

  }

  void clearMarket() {
    for (auto share : shares) {
      delete share;
    }
    shares.clear();
    std::cout<<"Market cleared!"<<std::endl;
  }

  ~Company() {
    clearMarket();
  }

};
  

int main() {
  stockPointers sp;
  Item* a = sp.apples;
  Person* b = new Person();
  Company myCompany("ABC", 50.0);
  Company myCompany2("XYZ", 50.0);
  Company* comp2 = &myCompany2;
  myCompany.issueShares(10, 10);
  myCompany.displayInfo();
  myCompany.sellShares(comp2, 5);
  myCompany.displayInfo();
  std::cout<<b->name<<" has $"<<b->money<<" and wants to buy "<<a->name<<" for $"<<a->val<< std::endl;
  return 0;
}
