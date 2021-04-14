#include "Pilha.h"

Pilha::Pilha() {
    this->topo=-1;
}

bool Pilha::push(long elemento) {
    if (this->topo >= (MAX-1)) {
        return false;
    }
    else {
        this->pilha[++this->topo] = elemento;
        return true;
    }
}

long Pilha::pop() {
    if (this->topo < 0) {
        return -1;
    }
    else {
        long elemento = this->pilha[this->topo--];
        return elemento;
    }
}

bool Pilha::pilhaVazia() {
    return (this->topo<0);
}

long Pilha::getTopo() {
    return this->topo;
}