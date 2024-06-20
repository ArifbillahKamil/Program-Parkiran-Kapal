#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct parkirankapal {
    char tipekapal[20];
    char jenismuatan[20];
    char bebanmuatan[10];
    int noparkiran;
};

typedef struct Node {
    struct parkirankapal data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef Node* address;//addres = tipe data

// Linked List
typedef struct {
    address first;
    address last;
} list_integer;

// Fungsi untuk membuat node baru
address createNode(struct parkirankapal data) {
    address newNode = (address)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode; // Circular linked list
    return newNode;
}

// Fungsi untuk mengecek apakah nomor parkiran sudah ada dalam list
int isDuplicate(list_integer *l, int noparkiran) {
    if (l->first == NULL) return 0;
    address temp = l->first;
    do {
        if (temp->data.noparkiran == noparkiran) {
            return 1;
        }
        temp = temp->next;
    } while (temp != l->first);
    return 0;
}

void insertFirst(list_integer *l, address newNode) {
    if ((l->first == NULL) && (l->last == NULL)) {
        l->first = newNode;
        l->last = newNode;
        newNode->next = l->first;
        newNode->prev = l->last;
    } else {
        newNode->next = l->first;
        l->first->prev = newNode;
        l->first = newNode;
        l->first->prev = l->last;
        l->last->next = l->first;
    }
}

void insertLast(list_integer *l, address newNode) {
    if ((l->first == NULL) && (l->last == NULL)) {
        l->first = newNode;
        l->last = newNode;
        newNode->next = l->first;
        newNode->prev = l->last;
    } else {
        newNode->prev = l->last;
        l->last->next = newNode;
        l->last = newNode;
        l->first->prev = l->last;
        l->last->next = l->first;
    }
}

void insertAfter(list_integer *l, address newNode, int noparkiran) {
    if (l->first == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (isDuplicate(l, newNode->data.noparkiran)) {
        printf("No. Parkiran %d sudah ada.\n", newNode->data.noparkiran);
        return;
    }
    address q = l->first;
    do {
        if (q->data.noparkiran == noparkiran) {
            newNode->next = q->next;
            newNode->prev = q;
            q->next->prev = newNode;
            q->next = newNode;
            if (q == l->last) {
                l->last = newNode; // Update last if we are inserting after the current last
            }
            return;
        }
        q = q->next;
    } while (q != l->first);

    printf("Node dengan noparkiran %d tidak ditemukan.\n", noparkiran);
}

void insertBefore(list_integer *l, address newNode, int noparkiran) {
    if (l->first == NULL) {
        printf("List is empty.\n");
        return;
    }
    if (isDuplicate(l, newNode->data.noparkiran)) {
        printf("No. Parkiran %d sudah ada.\n", newNode->data.noparkiran);
        return;
    }
    address current = l->first;
    do {
        if (current->data.noparkiran == noparkiran) {
            address prevNode = current->prev;

            newNode->next = current;
            newNode->prev = prevNode;
            prevNode->next = newNode;
            current->prev = newNode;

            if (current == l->first) {
                l->first = newNode; // Update first if we are inserting before the current first
            }
            return;
        }
        current = current->next;
    } while (current != l->first);

    printf("Node dengan noparkiran %d tidak ditemukan.\n", noparkiran);
}

void deleteFirst(list_integer *l) {
    if (l->first == NULL) {
        printf("List is empty.\n");
        return;
    }
    address newNode = l->first;
    if (l->first == l->last) {
        l->first = NULL;
        l->last = NULL;
    } else {
        l->first = newNode->next;
        l->first->prev = l->last;
        l->last->next = l->first;
    }
    free(newNode);
    printf("Data Pertama Berhasil Dihapus\n");
}

void deleteLast(list_integer *l) {
    if (l->first == NULL) {
        printf("List is empty.\n");
        return;
    }
    address newNode = l->last;
    if (l->first == l->last) {
        l->first = NULL;
        l->last = NULL;
    } else {
        l->last = newNode->prev;
        l->last->next = l->first;
        l->first->prev = l->last;
    }
    free(newNode);
    printf("Data Terakhir Berhasil Dihapus\n");
}

void display(list_integer l) {
    if (l.first == NULL) {
        printf("List is empty.\n");
        return;
    }

    address temp = l.first;
    do {
        printf("Tipe Kapal: %s, Jenis Muatan: %s, Beban Muatan: %s, No.Parkiran: %d\n",
               temp->data.tipekapal, temp->data.jenismuatan, temp->data.bebanmuatan, temp->data.noparkiran);
        temp = temp->next;
    } while (temp != l.first);
    printf("\n");
}

int main() {
    list_integer l = {NULL, NULL};
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Insert First\n");
        printf("2. Insert Last\n");
        printf("3. Insert After\n");
        printf("4. Insert Before\n");
        printf("5. Delete First\n");
        printf("6. Delete Last\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        struct parkirankapal kapal;
        int noparkiran;

        switch (choice) {
            case 1:
                printf("Enter Tipe Kapal: ");
                scanf("%s", kapal.tipekapal);
                printf("Enter Jenis Muatan: ");
                scanf("%s", kapal.jenismuatan);
                printf("Enter Beban Muatan: ");
                scanf("%s", kapal.bebanmuatan);
                printf("Enter No. Parkiran: ");
                scanf("%d", &kapal.noparkiran);
                if (!isDuplicate(&l, kapal.noparkiran)) {
                    insertFirst(&l, createNode(kapal));
                } else {
                    printf("No. Parkiran %d sudah ada.\n", kapal.noparkiran);
                }
                break;
            case 2:
                printf("Enter Tipe Kapal: ");
                scanf("%s", kapal.tipekapal);
                printf("Enter Jenis Muatan: ");
                scanf("%s", kapal.jenismuatan);
                printf("Enter Beban Muatan: ");
                scanf("%s", kapal.bebanmuatan);
                printf("Enter No. Parkiran: ");
                scanf("%d", &kapal.noparkiran);
                if (!isDuplicate(&l, kapal.noparkiran)) {
                    insertLast(&l, createNode(kapal));
                } else {
                    printf("No. Parkiran %d sudah ada.\n", kapal.noparkiran);
                }
                break;
            case 3:
                printf("Enter Tipe Kapal: ");
                scanf("%s", kapal.tipekapal);
                printf("Enter Jenis Muatan: ");
                scanf("%s", kapal.jenismuatan);
                printf("Enter Beban Muatan: ");
                scanf("%s", kapal.bebanmuatan);
                printf("Enter No. Parkiran: ");
                scanf("%d", &kapal.noparkiran);
                printf("Insert after No. Parkiran: ");
                scanf("%d", &noparkiran);
                if (!isDuplicate(&l, kapal.noparkiran)) {
                    insertAfter(&l, createNode(kapal), noparkiran);
                } else {
                    printf("No. Parkiran %d sudah ada.\n", kapal.noparkiran);
                }
                break;
            case 4:
                printf("Enter Tipe Kapal: ");
                scanf("%s", kapal.tipekapal);
                printf("Enter Jenis Muatan: ");
                scanf("%s", kapal.jenismuatan);
                printf("Enter Beban Muatan: ");
                scanf("%s", kapal.bebanmuatan);
                printf("Enter No. Parkiran: ");
                scanf("%d", &kapal.noparkiran);
                printf("Insert before No. Parkiran: ");
                scanf("%d", &noparkiran);
                if (!isDuplicate(&l, kapal.noparkiran)) {
                    insertBefore(&l, createNode(kapal), noparkiran);
                } else {
                    printf("No. Parkiran %d sudah ada.\n", kapal.noparkiran);
                }
                break;
            case 5:
                deleteFirst(&l);
                break;
            case 6:
                deleteLast(&l);
                break;
            case 7:
                display(l);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 8);

    return 0;
}
