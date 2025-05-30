#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <fstream>

using namespace std;

/**
 *  Royals University of Phnom Penh
 *  Department: IT
 *  Major: Computer Science
 *  Second Year Generation 27
 *  Team members:
 *  <li>
 *      Me
 *  </li>
 *
 */
const string TEAM_MEMBERS[] = {
    "Sareach Putbormey",
    "Lem Ansoleaphea",
    "Kung Sovannda",
    "Piseth Oudom",
    "Hiem Sreynit",
    "Soeng Yanut"
};

const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";

struct NodeType {
    char info;
    struct NodeType *next;
};

void writeToFile(struct NodeType *plist) {
    fstream file;
    file.open("char-list.bin", ios::binary|ios::out);
    if (!file) {
        cout << RED << "[!] Error opening file for writing." << RESET << endl;
    }
    struct NodeType *p = plist;
    while (p != NULL) {
        file.write((char*)&p->info, sizeof(char));
        p = p->next;
    }
    file.close();
}



void Initialize(struct NodeType *plist) {
    plist = nullptr;
}

struct NodeType *GetNode() {
    struct NodeType *p = (struct NodeType *) malloc(sizeof(struct NodeType));
    return p;
}

struct NodeType *readFromFile() {
    fstream file;
    file.open("char-list.bin", ios::binary|ios::in);
    if (!file) {
        cout << RED << "[!] Error opening file for reading." << RESET << endl;
    }
    char info;
    struct NodeType *p, *ptr, *plist;
    file.read((char*)&info, sizeof(char));
    p = GetNode();
    p->info = info;
    p->next = nullptr;
    plist = p;
    ptr = plist;
    while (file.read((char*)&info, sizeof(char))) {
        p = GetNode();
        p->info = info;
        p->next = nullptr;
        ptr->next = p;
        ptr = p;

    }
    return plist;
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
    plist = p;
    ptr = plist;
    for (i = 2; i <= n; i++) {
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
    cout << endl;
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
    return nullptr;
}

void Sort(struct NodeType *plist) {
    struct NodeType *p, *ptr, temp;
    for (p = plist; p != nullptr; p = p->next) {
        for (ptr = p->next; ptr != nullptr; ptr = ptr->next) {
            if (p->info > ptr->info) {
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
    cout << "[*] Item : ";
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
    cout << endl;
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
            cout << endl;
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

int ProgramMenu() {
    int choice = 0;
    cout << "===< Singly Linked List >====" << endl;
    cout << "1. Create List" << endl;
    cout << "2. Traverse" << endl;
    cout << "3. Search Node" << endl;
    cout << "4. Delete Node" << endl;
    cout << "5. Insert Node" << endl;
    cout << "6. Sort Node" << endl;
    cout << "7. Exit" << endl;
    cout << "[+] Enter Choice : "; cin >> choice;cin.ignore();
    return choice;
}

int ProgramExit() {
    system("cls");
    const int timeSleep = 900000;
    for (int i = 0; i < sizeof(TEAM_MEMBERS)/sizeof(string); i++) {
        cout << TEAM_MEMBERS[i] << endl;
        usleep(timeSleep);
    }
    cout << "Program Exit! Bye bye ";
    for (int i = 0; i< 3; i++) {
        cout << ".";
        usleep(timeSleep);
    }
    exit(0);
}
int main() {
    struct NodeType *plist = nullptr;
    Initialize(plist);
    int numberOfNodes = 0;
    do {
        plist = readFromFile();
        numberOfNodes = CountNode(plist);
        switch (ProgramMenu()) {
            case 1: {
                int n;
                cout << "[+] Enter number of items : "; cin >> n;
                if (n>0) {
                    plist = CreateList(plist, n);
                    cout << GREEN << "[+] List Created" << RESET << endl;
                }else {
                    cout << RED <<  "[!] Invalid Input" << RESET << endl;
                }
                break;
            }
            case 2: {
                if (numberOfNodes == 0) {
                    cout << YELLOW << "[!] The List Is Empty" << RESET << endl;
                }else {
                    cout << "[*] List Item : ";
                    Traverse(plist);
                }
                break;
            }
            case 3: {
                if (numberOfNodes == 0) {
                    cout << YELLOW << "[!] The List Is Empty" << RESET << endl;
                }else {
                    SearchNode(plist);
                }
                break;
            }
            case 4: {
                if (numberOfNodes == 0) {
                    cout << YELLOW << "[!] The List Is Empty" << RESET << endl;
                }else {
                    char item;
                    cout << "[+] Enter Item : "; cin >> item;
                    plist = DelNode(plist,item);
                }
                break;
            }
            case 5: {
                if (numberOfNodes == 0) {
                    cout << YELLOW << "[!] The List Is Empty" << RESET << endl;
                }else {
                    char item;
                    cout << "[+] Enter Item : "; cin >> item;
                    plist = InsertNode(plist, item);
                }
                break;
            }
            case 6: {
                if (numberOfNodes == 0) {
                    cout << YELLOW << "[!] The List Is Empty" << RESET << endl;
                }else {
                    Sort(plist);
                }
                break;
            }

            case 7: {
                ProgramExit();
            }
            default: {
                cout << RED << "[!] Invalid Choice" << RESET << endl;
            }
        }
        writeToFile(plist);
        cout << "[+] Any key to continue..."; getch();
        system("cls");

    }while (true);
}
