#include <memory>
#include <iostream>
class Node
{
public:
    int Data;
    // std::shared_ptr<Node> Next; //Error - mem leak -> causes reference cycle problem
    std::weak_ptr<Node> Next;

    Node(int value) : Data(value), Next() {}
};

int main()
{

    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);

    node1->Next = node2;
    node2->Next = node1;

    std::cout << node1.use_count() << std::endl;
    std::cout << node2.use_count() << std::endl;
    std::cout << node1->Next.use_count() << std::endl;
    std::cout << node2->Next.use_count() << std::endl;
}