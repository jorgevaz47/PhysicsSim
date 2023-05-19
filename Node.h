/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Node header file
 * 
*/

#pragma once
#include "Particle.h"

class Node {
public:
    Node(const Particle& particle, Node* nextNode = nullptr);
    Particle getParticle() const;
    Node* getNext() const;
    void setNext(Node* nextNode);

private:
    Particle particle;
    Node* next;
};
