#include <iostream>
#include <string>
#include <vector>

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define NUM 0
#define BRA 5
#define KET 6

#define PREFIX 0
#define INFEX 1
#define POSTFIX 2

using namespace std;

class node {
public:
    node *leftchild;
    node *rightchild;
    node *parent;

    int type;
    int value;
    char cvalue;

    ~node();
};
node::~node() {
    if (leftchild != NULL)
        delete leftchild;
    if (rightchild != NULL)
        delete rightchild;
}
class lexems {
public:
    vector<int> lexem;
    vector<int> value;
};
lexems* CreateLexems(string str) {
    lexems *lex = new lexems;
    int x;
    bool ConstructingInt = false;
    for (int i=0; i < str.size(); i++) {
        if (('0' <= str[i]) && (str[i] <= '9')) {
            if (!ConstructingInt) {
                (lex->lexem).push_back(NUM);
                ConstructingInt = true;
                x = 0;
            }
            x = x*10 + str[i]-'0';
        }
        else if (ConstructingInt) {
            (lex->value).push_back(x);
            ConstructingInt = false;
        }
        switch (str[i]) {
        case '+':
            (lex->lexem).push_back(ADD);
            (lex->value).push_back(0);
            break;
        case '-':
            (lex->lexem).push_back(SUB);
            (lex->value).push_back(0);
            break;
        case '*':
            (lex->lexem).push_back(MUL);
            (lex->value).push_back(0);
            break;
        case '/':
            (lex->lexem).push_back(DIV);
            (lex->value).push_back(0);
            break;
        }
    }
    if (ConstructingInt)
        (lex->value).push_back(x);
    return lex;
}

string *CreateString(lexems *lex) {
    string *x = new string;
    int t;
    for (int i=0; i < (lex->lexem).size(); i++) {
        switch ((lex->lexem)[i]) {
        case NUM:
            *x += to_string((lex->value)[i]);
            *x += ' ';
            break;
        case ADD:
            *x += '+';
            break;
        case SUB:
            *x += '-';
            break;
        case MUL:
            *x += '*';
            break;
        case DIV:
            *x += '/';
            break;
        case BRA:
            *x += '(';
            break;
        case KET:
            *x += ')';
            break;
        }
    }
    return x;
}

node* CreateHeap(lexems* lex, int *beg, int notation){
    node* Node;
    lexems *Lex;
    int Beg;

    if (*beg == (lex->lexem).size())
        return NULL;
    Node = new node;
    switch(notation) {
    case PREFIX:
        if ((lex->lexem)[*beg] == NUM) {
            Node->leftchild = NULL;
            Node->rightchild = NULL;
            Node->type = NUM;
            Node->value = (lex->value)[*beg];

            (*beg)++;
            return Node;
        } else
        if (true) {
            Node->type = (lex->lexem)[*beg];
            Node->value = 0;
            (*beg)++;
            Node->leftchild = CreateHeap(lex, beg, PREFIX);
            Node->rightchild = CreateHeap(lex, beg, PREFIX);
            return Node;
        }
    case POSTFIX:
        Lex = new lexems;
        for (int i = (lex->lexem).size() - 1; i >= 0; i--) {
            (Lex->lexem).push_back((lex->lexem)[i]);
            (Lex->value).push_back((lex->value)[i]);
        }
//        cout << "Here: ";
//        for(int i=0; i < (Lex->lexem).size(); i++)
//        cout <<"L : "<< (Lex->lexem)[i] << "  "<< (Lex ->value)[i] << '\n';
        Beg = 0;
        return CreateHeap(Lex, &Beg, PREFIX);
    }
}

void TranslateHeap(node *Node, lexems* lex, int notation) {
    switch(notation) {
    case PREFIX:
        if (Node->type == NUM) {
            lex->lexem.push_back(NUM);
            lex->value.push_back(Node->value);
//            cout << "Translating NUM: "<< Node->value<< '\n';
            return;
        } else
        if (Node == NULL) {
            return;
        } else
        if (true) {
            lex->lexem.push_back(Node->type);
            lex->value.push_back(0);
            TranslateHeap(Node->leftchild, lex, PREFIX);
            TranslateHeap(Node->rightchild, lex, PREFIX);
            return;
        }
    case POSTFIX:
        if (Node->type == NUM) {
            lex->lexem.push_back(NUM);
            lex->value.push_back(Node->value);
//            cout << "Translating NUM: "<< Node->value<< '\n';
            return;
        } else
        if (Node == NULL) {
            return;
        } else
        if (true) {
            TranslateHeap(Node->leftchild, lex, POSTFIX);
            TranslateHeap(Node->rightchild, lex, POSTFIX);
            lex->lexem.push_back(Node->type);
            lex->value.push_back(0);
            return;
        }
    case INFEX:
        if (Node->type == NUM) {
            lex->lexem.push_back(NUM);
            lex->value.push_back(Node->value);
//            cout << "Translating NUM: "<< Node->value<< '\n';
            return;
        } else
        if (Node == NULL) {
            return;
        } else
        if (1) {
            (lex->lexem).push_back(BRA);
            (lex->value).push_back(0);
            TranslateHeap(Node->leftchild, lex, INFEX);
            lex->lexem.push_back(Node->type);
            lex->value.push_back(0);
            TranslateHeap(Node->rightchild, lex, INFEX);
            lex->lexem.push_back(KET);
            lex->lexem.push_back(0);
        }
    }
    return;
}

void FreeLexems(lexems *lex) {
    int N = (lex->lexem).size();
    for (int i=0; i < N; i++) {
        (lex->lexem).pop_back();
        (lex->value).pop_back();
    }
}
int main() {
    int i=0;
    string x;
    getline(cin, x);
    lexems *lex = CreateLexems(x), *lexx = CreateLexems("");
    node *Node = CreateHeap(lex, &i, PREFIX);
    FreeLexems(lex);

    TranslateHeap(Node, lex, INFEX);
    delete Node;

//    for(int i=0; i < (lex->lexem).size(); i++)
//        cout <<"L : "<< (lex->lexem)[i] << "  "<< (lex ->value)[i] << '\n';
    string *y = CreateString(lex);
    cout << *y;
    return 0;
}
