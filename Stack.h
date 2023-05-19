/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Stack header file
 * 
*/

#pragma once
#include "Particle.h"

class Stack {
public:
    Stack();
    ~Stack();

    void push(const Particle& particle);
    void pop();
    const Particle& top() const;
    bool isEmpty() const;

private:
    struct Node {
        Particle particle;
        Node* next;
    };

    Node* topNode;
};