// Linked list with std::shared_ptr

#include <iostream>
#include <memory>

class Node {
    int _data;
    std::shared_ptr<Node> next;

  public:
    Node(int data) : _data(data), next{} {}
    int get_data() { return _data; }
    std::shared_ptr<Node>& get_next() { return next; }
};

void insert(std::shared_ptr<Node>& head, int data) {
    // create a new Node
    auto newNode = std::make_shared<Node>(data);
    if (!head) { // empty list
        head = newNode;
    } else // otherwise
    {
        auto copy_head = head; // make a copy, we don't want to modify the head
        while (copy_head->get_next()) {
            copy_head = copy_head->get_next();
        }
        copy_head->get_next() = newNode; // link the new Node
    }
}

void print(std::shared_ptr<Node> head) {
    while (head) {
        std::cout << head->get_data() << std::endl;
        head = head->get_next();
    }
}

int main() {
    std::shared_ptr<Node> my_list{};
    insert(my_list, 10);
    insert(my_list, 20);
    insert(my_list, 30);
    print(my_list);
}
