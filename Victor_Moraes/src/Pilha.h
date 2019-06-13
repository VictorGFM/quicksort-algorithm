#ifndef PILHA_H
#define PILHA_H

#define MAX 500000

class Pilha {
    private:
        long topo;
        long pilha[MAX];
    public:
        Pilha();
        bool push(long);
        long pop();
        bool pilhaVazia();
        long getTopo();
};


#endif
