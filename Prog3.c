#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coef;
    int exp;
    struct Node* next;
};

typedef struct Node Node;

void insert(Node** poly, int coef, int exp) {
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->coef = coef;
    temp->exp = exp;
    temp->next = NULL;
    
    if (*poly == NULL) {
        *poly = temp;
        return;
    }
    
    Node* current = *poly;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = temp;
}

void displayPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    
    Node* current = poly;
    
    while (current != NULL) {
        printf("%dx^%d", current->coef, current->exp);
        if (current->next != NULL) {
            printf(" + ");
        }
        current = current->next;
    }
    
    printf("\n");
}

Node* addPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp == poly2->exp) {
            insert(&result, poly1->coef + poly2->coef, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insert(&result, poly1->coef, poly1->exp);
            poly1 = poly1->next;
        } else {
            insert(&result, poly2->coef, poly2->exp);
            poly2 = poly2->next;
        }
    }
    
    while (poly1 != NULL) {
        insert(&result, poly1->coef, poly1->exp);
        poly1 = poly1->next;
    }
    
    while (poly2 != NULL) {
        insert(&result, poly2->coef, poly2->exp);
        poly2 = poly2->next;
    }
    
    return result;
}

int main() 
{
    struct Node* poly1=NULL;
    struct Node* poly2=NULL;
    int maxPower1, maxPower2;
    printf("Polynomial-1:\n");
    printf("Enter the Maximum power of x: ");
    scanf("%d", &maxPower1);
    for (int i = maxPower1; i >= 0; i--) {
        int coeff;
        printf("Enter the coefficient of degree %d: ", i);
        scanf("%d", &coeff);
        insert(&poly1, coeff, i);
    }
    printf("Polynomial-2:\n");
    printf("Enter the Maximum power of x: ");
    scanf("%d", &maxPower2);
    for (int i = maxPower2; i >= 0; i--) {
        int coeff;
        printf("Enter the coefficient of degree %d: ", i);
        scanf("%d", &coeff);
        insert(&poly2, coeff, i);
    }
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* result = addPoly(poly1, poly2);
    printf("Resultant Polynomial: ");
    displayPolynomial(result);
    
    return 0;
}