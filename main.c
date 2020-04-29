#include <stdio.h>
#include <malloc.h>
#define LENBUF 10

typedef struct list_node {
    struct list_node *next;
    char* command;
    //char* tel_number;
} list_node_t;

typedef struct list {
    int size;
    list_node_t *head;
    list_node_t *tail;
} list_t;

list_t *create_list(void) {
    list_t *lst = malloc(sizeof(list_t));
    lst->size = 0;
    lst->head = NULL;
    lst->tail = lst->head;
    return lst;
}

void node_push(list_t *lst, char *cmd) {
    list_node_t *node = malloc(sizeof(list_node_t));
    node->command = cmd;
    node->next = lst->head;
    lst->head = node;
    lst->size += 1;
}

char* node_pop(list_t *lst) {
    if (lst->size == 0)
    {
        return NULL;
    }
    list_node_t* node = lst->head;
    lst->head = node->next;
    char* data = node->command;
    free(node);
    lst->size -= 1;
    if (lst->size == 0)
    {
        lst->head = NULL;
        lst->tail = NULL;
    }
    return data;
}

char* input_data() {
    char* buf = (char*) malloc(LENBUF * sizeof(char));
    char ch;
    int i = 0;
    while (1)
    {
        ch = getchar();
        if (ch == '\n')
        {
            if (!i)
            {
                return NULL;
            }
            buf[i] = '\0';
            return buf;
        }
        buf[i] = ch;
        ++i;
        if (i == (LENBUF - 1))
        {
            buf[i] = '\0';
            return buf;
        }
    }
}

int main()
{
    list_t* list_msg = create_list();
    char* ptr_data;

    while (1)
    {
        puts("Input char:");
        ptr_data = input_data();
        if (ptr_data == NULL)
        {
            break;
        }
        node_push(list_msg, ptr_data);
    }
    while (1)
    {
        ptr_data = node_pop(list_msg);
        if (ptr_data != NULL)
        {
            puts(ptr_data);
        }
        else
        {
            break;
        }
    }
    return 0;
}
