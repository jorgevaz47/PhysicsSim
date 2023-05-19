/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Stack implementation file
 * 
*/

#include "Stack.h"

// Inline constructor for the stack
Stack::Stack() : topNode(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(const Particle& particle) {
    Node* newNode = new Node;
    newNode->particle = particle;
    newNode->next = topNode;
    topNode = newNode;
}

void Stack::pop() {
    if (isEmpty()) {
        // Stack is empty, nothing to pop
        return;
    }

    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
}

const Particle& Stack::top() const {
    // Assumes stack is not empty
    return topNode->particle;
}

bool Stack::isEmpty() const {
    return topNode == nullptr;
}