#include <stdio.h>
#include <stdlib.h>

/* Flags about data */
typedef struct flag {
    unsigned int type:3;
}flag;

/* Node contains data */
typedef struct node_t{
    void *data;
    int size;
    struct node_t *prev;
    struct node_t *next;
    struct flag *flag;
    
}node_t;

/* List of nodes */
typedef struct list_t{
    struct node_t* first;
    struct node_t* last;
    int count;
}list_t;

/* Student struct */
typedef struct student{
    int id;
    int age;
    char *name;
}student;

/* Create Node */

node_t* create_node(void* data, int size, unsigned int type) {
    node_t* node = malloc(sizeof(node_t));
    node->data = data;
    node->size = size;
    node->flag = malloc(sizeof(flag));
    node->flag->type = type;
    return node;
}

/* Create List */

// int init_count(node_t* f_node, node_t* l_node) {
//     if(f_node == NULL && l_node == NULL) {
//         return 0;
//     } else if (f_node == NULL && l_node != NULL) {
//         return 1;
//     } else if (f_node != NULL && l_node == NULL) {
//         return 1;
//     } else {
//         return 2;
//     }
// }

list_t* create_list(node_t* f_node, node_t* l_node) {
    list_t* list = malloc(sizeof(list_t));
    list->first = f_node;
    list->last = l_node;
    list->first->next = l_node;
    list->last->prev = f_node;
    list->count = 2;
}

/* Insert (First,Last) */

void insert_list_first(list_t* list, node_t* node) {
    if(list->first != NULL) {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
        list->count++;
    }
}

void insert_list_last(list_t* list, node_t* node) {
    if(list->last != NULL) {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
        list->count++;
    }
}

/* Delete nodes */

void delete_first(list_t* list) {
    node_t* n = list->first;
    list->first = list->first->next;
    list->count--;
    free(n);
}

void delete_last(list_t* list) {
    node_t* n = list->last;
    list->last = list->last->prev;
    list->last->next = NULL;
    list->count--;
    free(n);
}

void delete_all(list_t* list) {
    node_t* n = list->first;
    node_t* n_to_delete = n;
    while (n != NULL) {
        n = n->next;
        free(n_to_delete);
        n_to_delete = n;
    }
    free(list);
}

/* Print (list) */

void print_list(list_t* list) {
    node_t* n = list->first;
    printf("List Count: %d\n",list->count);
    while (n != NULL) {
        printf("Node Address: %p\n Node Data Address: %p\n Size of Node: %d\n Flag type: %d\n",
        n,n->data,n->size,n->flag->type);
        n = n->next;
    }   
}

/* Create Student */

student* create_student(int id, int age, char* name) {
    student* s = malloc(sizeof(student));
    s->id = id;
    s->age = age;
    s->name = name;
    return s;
}

int main() {
   
    // New node (1)
    student* st1 = create_student(1,22,"Ahmed Mohammed");
    node_t* node1 = create_node(st1,sizeof(student), 0x01);

    // New node (2)
    int num = 1;
    node_t* node2 = create_node(&num,sizeof(int), 0x02);

    // New node (3)
    student* st2 = create_student(2,26,"Bader Saad");
    node_t* node3 = create_node(st2,sizeof(student), 0x03);

    // New Node (4)
    char d = 'd';
    node_t* node4 = create_node(&d,sizeof(char),0x04);

    // New list
    list_t* list = create_list(node1,node3);

    insert_list_first(list,node2);
    insert_list_last(list,node4);

    print_list(list);

    printf("----------------------------------\n");

    delete_last(list);

    print_list(list);

    return 0;
}