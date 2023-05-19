/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Node implementation file
 * 
*/

#include "Node.h"

Node::Node(const Particle& particle, Node* nextNode): particle(particle), next(nextNode) {}

Particle Node::getParticle() const {
    return particle;
}

Node* Node::getNext() const {
    return next;
}

void Node::setNext(Node* nextNode) {
    next = nextNode;
}