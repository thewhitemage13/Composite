#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item abstract {
protected:
    string item_name;
    string owner_name;
public:
    Item(string name) : item_name(name){}

    void SetOwner(string owner) {
        owner_name = owner;
    }
    virtual void Add(Item* SubItem) = 0;
    virtual void Remove(Item* SubItem) = 0;
    virtual void Display() = 0;
};

class ClickableItem : public Item {
public:
    ClickableItem(string name) : Item(name){}
    void Add(Item* SubItem) override {
        throw exception();
    }
    void Remove(Item* SubItem) override {
        throw exception();
    }
    void Display() override {
        cout << item_name << "\n";
    }
};

class DropDownItem : public Item {
private:
    vector<Item*>children;
public:
    DropDownItem(string name) : Item(name) {}
    void Add(Item* SubItem) override {
        SubItem->SetOwner(this->item_name);
        children.push_back(SubItem);
    }
    void Remove(Item* SubItem) override {
        children.erase(std::remove(children.begin(), children.end(), SubItem), children.end());
    }
    void Display() override {
        for (const auto& child : children) {
            if (owner_name != "")
                cout << owner_name << item_name << "\n";
            child->Display();
        }
    }
};

int main(){
    Item* file = new DropDownItem("File->");
    Item* create = new DropDownItem("Create->");
    Item* open = new DropDownItem("Open->");
    Item* exit = new ClickableItem("Exit");
    
    file->Add(create);
    file->Add(open);
    file->Add(exit);

    Item* project = new ClickableItem("Project...");
    Item* repository = new ClickableItem("Repository...");

    create->Add(project);
    create->Add(repository);

    Item* solution = new ClickableItem("Solution...");
    Item* folder = new ClickableItem("Folder...");

    open->Add(solution);
    open->Add(folder);

    file->Display();
    cout << "\n";
    file->Remove(create);
    file->Display();
}