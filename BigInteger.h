#ifndef BigInteger_h
#define BigInteger_h
struct Node {
    int data;
    struct Node *next;
};

struct BigInteger{
    struct Node *L;
    char sign;
    int size;
};

struct Node *createNode(int );
void display(struct BigInteger );
struct BigInteger initialize(char *);
int count(struct Node* );
int compareLists(struct Node* , struct Node* );
struct BigInteger * truncate(struct BigInteger*);
struct BigInteger add(struct BigInteger , struct BigInteger );
struct BigInteger sub(struct BigInteger , struct BigInteger );
struct BigInteger mul(struct BigInteger , struct BigInteger );
struct BigInteger div1(struct BigInteger , struct BigInteger );
struct BigInteger mod(struct BigInteger , struct BigInteger );
#endif