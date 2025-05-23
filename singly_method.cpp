#include <stdlib.h>
#include <iostream>
#include <conio.h>
using namespace std;

struct NodeType {
    char info;
    struct NodeType *next;
};

void Initialize(struct NodeType *plist) {
    plist = nullptr;
}

struct NodeType *GetNode() {
    struct NodeType *p = (struct NodeType *) malloc(sizeof(struct NodeType));
    return p;
}

void FreeNode(struct NodeType *p) {
    free(p);
}

struct NodeType *CreateList(struct NodeType *plist, int n) {
    struct NodeType *p, *ptr;
    char item;
    int i;
    cout << "[+] Enter Item : ";
    cin >> item;
    p = GetNode();
    p->info = item;
    p->next = nullptr;
    ptr = plist;
    for (int i = 2; i <= n; ++i) {
        cout << "[+] Enter Item : ";
        cin >> item;
        p = GetNode();
        p->info = item;
        p->next = nullptr;
        ptr->next = p;
        ptr = p;
    }
    return plist;
}

void Traverse(struct NodeType *plist) {
    struct NodeType *ptr;
    ptr = plist;
    while (ptr != nullptr) {
        cout << ptr->info << " ";
        ptr = ptr->next;
    }
}

int CountNode(struct NodeType *plist) {
    struct NodeType *p;
    int num = 0;
    p = plist;
    while (p != nullptr) {
        num++;
        p = p->next;
    }
    return num;
}

struct NodeType *SearchPos(struct NodeType *plist, char item) {
    struct NodeType *p;
    p = plist;
    while (p != nullptr) {
        if (p->info == item) {
            return (p);
        } else {
            p = p->next;
        }
    }
    if (p == nullptr) {
        return nullptr;
    }
}

void Sort(struct NodeType *plist) {
    struct NodeType *p, *ptr, temp;
    for (p = plist; p != nullptr; p = p->next) {
        for (ptr = p->next; ptr != nullptr; ptr = ptr->next) {
            if (p->info < ptr->info) {
                temp.info = p->info;
                p->info = ptr->info;
                ptr->info = temp.info;
            }
        }
    }
}

void SearchNode(struct NodeType *plist) {
    int found = 0;
    char item;
    struct NodeType *p;
    p = plist;
    cout << "[+] Enter Item : ";
    cin >> item;
    while (p != nullptr) {
        if (p->info == item) {
            found = 1;
            cout << p->info;
        }
        p = p->next;
    }
    if (found == 0) {
        cout << "Not found";
    }
}

struct NodeType *DelNode(struct NodeType *plist, char item) {
    struct NodeType *p, *p1, *p2, *p3, *ptr;
    p = SearchPos(plist, item);
    if (p != nullptr) {
        if (p == plist) {
            cout << "Delete at the beginning NodeP1" << endl;
            p1 = p;
            plist = p1->next;
            FreeNode(p);
        } else if (p->next == nullptr) {
            cout << "Delete NodeP2 at position end" << endl;
            p2 = p;
            ptr = plist;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = p2->next;
            FreeNode(p);
        } else {
            cout << "Delete NodeP3 at position after NodePTR" << endl;
            p3 = p;
            ptr = plist;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = p3->next;
            FreeNode(p);
        }
    }
    return plist;
}

struct NodeType *InsertNode(struct NodeType *plist, char item) {
    struct NodeType *p, *ptr;
    char ch;
    int count, i, pos;
    p = GetNode();
    p->info = item;
    p->next = nullptr;
    if (plist == nullptr) {
        plist = p;
    }else {
        cout << "1. Beginning" << endl;
        cout << "2. End" << endl;
        cout << "3. Positon after NodePTR" << endl;
        do {
            cout << "[+] Choose [B, E, A] or Q to Quite: "; ch = getch();
            switch (ch) {
                case 'B':
                case 'b': {
                    cout << "Insert at beginning NodeP1" << endl;
                    p->next = plist;
                    plist = p;
                    break;
                }
                case 'E':
                case 'e': {
                    cout << "Insert at end of NodeP2" << endl;
                    ptr = plist;
                    while (ptr->next != nullptr) {
                        ptr = ptr->next;
                    }
                    ptr->next = p;
                    break;
                }
                case 'A':
                case 'a': {
                    cout << "Insert at position after NodePTR" << endl;
                    count = CountNode(plist);
                    cout << "[+] Enter positon: "; cin >> pos;
                    if (pos > count) {
                        cout << "[!] Invalid Position" << endl;
                    }else {
                        i = 1;
                        ptr = plist;
                        while (i<count) {
                            ptr = ptr->next;
                            i++;
                        }
                        p->next = ptr->next;
                        ptr->next = p;
                    }
                    break;
                }
                case 'Q':
                case 'q': {
                    cout << "[*] Exit Inserting" << endl;
                    break;
                }
                default: {
                    cout << "[!] Invalid Choice" << endl;
                }
            }
        }while (ch != 'Q' && ch != 'q');
    }
    return plist;
}

int main() {

    return 0;
}
