#include <iostream>
#include "stack.h"
#include <stdexcept>
// TODO: Implementation of print for SValue
// void print(SValue) {}

// Implementation of default constructor
Stack::Stack()
    : depth(0)       // internal depth is 0
    , head(nullptr)  // internal linked list is null to start
{};
// The construction ": var1(val1), var2(val2) {}" is called a
// "list initializer" for a constructor, and is the preferred
// way of setting default field values for a class instance
// Here 0 is the default value for Stack::depth
// and nullptr is the default value for Stack::head


// Implementation of size method
std::size_t Stack::size() const
{
    // Recall that this is a keyword representing a pointer
    // to the current instance of Stack. Since Stack is a class,
    // it is a fancy struct, so the C notation of -> works to
    // extract the size field from the class instance properly
    return this->depth;
}


// Implementation of push method
void Stack::push(SValue val)
{
    // Create a unique_ptr named "new_node_ptr" to manage memory
    // First create a pointer to a zero-allocated Node struct using
    // the "new" keyword. See following equivalence:
    //    C++: Node *n = new Node();
    //    C  : Node *n = (Node *)calloc(1, sizeof(Node));
    //
    // Importantly "new" creates a pointer to an allocated memory block
    // This block needs to be deallocated. See the following equivalence:
    //    C++: delete n;
    //    C  : free(n);
    //
    // However, here we wrap this new block of memory inside a unique_ptr
    // The unique_ptr then manages the deallocation for us - if the
    // pointer ever goes out of scope, then unique_ptr automatically calls
    // delete on the corresponding block of memory
    // This mimics the action of a "garbage collector", which cleans up
    // blocks of memory that are no longer being used
    // This only works here because we are declaring that there are no
    // other references to this block of memory, so C++ is free to delete
    // at will
    //
    std::unique_ptr<Node> new_node_ptr(new Node());

    // Set the fields just as we would with a normal pointer
    new_node_ptr->data = val;
    // Since the old head pointer is unique, we cannot simply assign it to
    // something else. Instead, we have to "move" it so that the ownership
    // of the pointer transfers properly to the new variable (meaning that
    // the old head is still unique : there is only one reference to it)
    new_node_ptr->next = std::move(this->head);

    // As soon as the old "head" pointer goes out of scope here, it is
    // automatically deallocated, since it is a unique_ptr
    // Again, we must move the new pointer uniquely to become the new head
    this->head = std::move(new_node_ptr);
    this->depth++;
}


// Implementation of pop method
SValue Stack::pop()
{
    // Use the empty method to check whether Stack is empty
    if (this->empty())
    {
        throw std::length_error(" Empty Stack");
        // TODO: Fix this by throwing an exception properly
        // https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
        return -1;
    }

    SValue val = this->head->data;
    // We move the unique pointer of the old next to become the new head
    this->head = std::move(this->head->next);
    // Again, we allow the unique_ptr to the old head to be deallocated
    // automatically as it goes out of scope
    this->depth--;
    return val;
}


// TODO: Implementation of empty method
bool Stack::empty() const
 {
 if( this->depth==0){
     return true;
 }else{
     return false;
 }
 }
void print(SValue val){
    std::cout<< val;
}
// TODO: Implementation of print method
void Stack::print() const
{
  Node *temp = this->head.get();
  while(temp){
    std::cout << temp->data<< std::endl ;
    temp = temp->next.get();
  }

}
