#include <stdio.h>
#include <stdlib.h>

// define the node
typedef struct node {
    int number;
    struct node *next;
} node;

// function to create a node
node* createNode(int number) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    newNode->number = number;
    newNode->next = NULL;
    return newNode;
}

// insert node at the end
void insertAtEnd(node **head, int number) {
    node *newNode = createNode(number);
    if (*head == NULL) {
        *head = newNode;
    } else {
        node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Inserted %d into the list.\n", number);
}

// display the list
void displayList(node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    printf("Linked List: ");
    node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->number);
        temp = temp->next;
    }
    printf("NULL\n");
}

// update node by value
void updateNode(node *head, int oldValue, int newValue) {
    node *temp = head;
    while (temp != NULL) {
        if (temp->number == oldValue) {
            temp->number = newValue;
            printf("Updated node from %d to %d.\n", oldValue, newValue);
            return;
        }
        temp = temp->next;
    }
    printf("Value %d not found in the list.\n", oldValue);
}

// update node at a specific position
void updateNodeAt(node **head, int position, int newvalue) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    node *temp = *head;

    while (position > 1 && temp != NULL) {
        temp = temp->next;
        position--;
    }

    if (temp != NULL) {
        temp->number = newvalue;  // Update node value
        printf("Updated node at position.\n");
    } else {
        printf("Position out of range.\n");
    }
}

// delete a node by value
void deleteNode(node **head, int value) {
    if (*head == NULL) {
        printf("The list is empty. Nothing to delete.\n");
        return;
    }
    
    node *temp = *head, *prev = NULL;
    
    // check if the head node holds the value
    if (temp != NULL && temp->number == value) {
        *head = temp->next;
        free(temp);
        printf("Deleted node with value %d.\n", value);
        return;
    }
    
    // search for the node to delete, keeping track of the previous node
    while (temp != NULL && temp->number != value) {
        prev = temp;
        temp = temp->next;
    }
    
    // if the value was not found
    if (temp == NULL) {
        printf("Value %d not found in the list.\n", value);
        return;
    }
    
    // unlink the node and free its memory
    prev->next = temp->next;
    free(temp);
    printf("Deleted node with value %d.\n", value);
}

// free the entire linked list
void freeList(node *head) {
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    node *list = NULL;  // Initialize the list as empty
    int choice, value, oldValue, newValue, position;
    
    while (1) {
        // display menu options
        printf("\n--- Linked List CRUD Operations ---\n");
        printf("1. Insert a node\n");
        printf("2. Display list\n");
        printf("3. Update a node\n");
        printf("4. Delete a node\n");
        printf("5. Update a node at a specific position\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        
        switch (choice) {
            case 1:
                printf("Enter a number to insert: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                insertAtEnd(&list, value);
                break;
                
            case 2:
                displayList(list);
                break;
                
            case 3:
                printf("Enter the value you want to update: ");
                if (scanf("%d", &oldValue) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                printf("Enter the new value: ");
                if (scanf("%d", &newValue) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                updateNode(list, oldValue, newValue);
                break;
                
            case 4:
                printf("Enter the value to delete: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                deleteNode(&list, value);
                break;
                
            case 5:
                printf("Enter the position to update: ");
                if (scanf("%d", &position) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                printf("Enter the new value: ");
                if (scanf("%d", &newValue) != 1) {
                    printf("Invalid input. Please try again.\n");
                    break;
                }
                updateNodeAt(&list, position, newValue);
                break;

            case 6:
                printf("Exiting the program.\n");
                freeList(list);
                return 0;
                
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }
    
    freeList(list);
    return 0;
}
