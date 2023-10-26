#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "BigInteger.h"

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int count(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

struct BigInteger * truncate(struct BigInteger* big_int) {
    struct Node* head = big_int->L;
    struct Node *current = head;
    struct Node* non_zero = NULL;

    while(current!=NULL){
        if(current->data != 0){
            non_zero = current;
        }
        current = current->next;
    }

    if (non_zero != NULL) {
        struct Node* toFree = non_zero->next;
        non_zero->next = NULL;

        while(toFree!=NULL){
            struct Node* temp = toFree;
            toFree = toFree->next;
            free(temp);
        }

        return big_int;
    }
    else{
        struct Node *zero = head;
        struct Node* toFree = zero->next;
        zero->next = NULL;

        while(toFree!=NULL){
            struct Node* temp = toFree;
            toFree = toFree->next;
            free(temp);
        }

        return big_int;
    }
}

int compareLists(struct Node* num1, struct Node* num2) {
    // Compare the lengths of the linked lists
    int count1 = count(num1);
    int count2 = count(num2);

    if (count1 > count2) {
        return 1;
    } else if (count2 > count1) {
        return -1;
    }

    // If lengths are equal, compare digit by digit
    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) {
            return 1;
        } else if (num2->data > num1->data) {
            return -1;
        }

        num1 = num1->next;
        num2 = num2->next;
    }

    // If all digits are equal, the two numbers are equal
    return 0;
}

void display(struct BigInteger big_int) {
    struct Node *current = big_int.L;
    struct Node *copy = NULL;

    while (current != NULL) {
        struct Node *newNode = createNode(current->data);
        newNode->next = copy;
        copy = newNode;
        current = current->next;
    }

    current = copy;

    if(big_int.sign == '-'){
        printf("- ");
    }

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    while (copy != NULL) {
        struct Node *temp = copy;
        copy = copy->next;
        free(temp);
    }

    printf("\n");
}

struct BigInteger initialize(char *s) {
    struct BigInteger p;
    p.L = NULL;

    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        int digit = s[i] - '0'; 
        struct Node *newNode = createNode(digit);

        newNode->next = p.L;
        p.L = newNode;
    }

    struct BigInteger copy = p;
    // printf("Number :: ");display(copy);
    truncate(&p);
    return p;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct Node *head1 = a.L;
    struct Node *head2 = b.L;
    struct BigInteger result;
    result.L = NULL;
    struct Node *temp = NULL;
    int carry = 0;

    while (head1 != NULL || head2 != NULL || carry) {
        int sum = carry;

        if (head1 != NULL) {
            sum += head1->data;
            head1 = head1->next;
        }

        if (head2 != NULL) {
            sum += head2->data;
            head2 = head2->next;
        }

        carry = sum / 10;
        sum %= 10;

        struct Node *newNode = createNode(sum);

        if (result.L == NULL) {
            result.L = newNode;
            temp = result.L;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    // printf("Addition :: ");display(result);
    truncate(&result);
    return result;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    // Ensure a is larger or equal to b by swapping if necessary
    struct BigInteger result;
    result.L = NULL;

    if (compareLists(a.L, b.L) == -1) {
        result.sign = '-';
        struct BigInteger temp = a;
        a = b;
        b = temp;
    }

    if (compareLists(a.L, b.L) == 0){
        result = initialize("0");
        return result;
    }


    struct Node *head1 = a.L;
    struct Node *head2 = b.L;
    struct Node *temp = NULL;
    int borrow = 0;

    while (head1 != NULL || head2 != NULL) {
        int num1 = 0, num2 = 0;
        if (head1 != NULL) {
            num1 = head1->data;
        }
        if (head2 != NULL) {
            num2 = head2->data;
        }

        int diff = num1 - num2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        struct Node *newNode = createNode(diff);

        if (result.L == NULL) {
            result.L = newNode;
            temp = result.L;
        } else {
            temp->next = newNode;
            temp = newNode;
        }

        if (head1 != NULL) {
            head1 = head1->next;
        }
        if (head2 != NULL) {
            head2 = head2->next;
        }
    }

    truncate(&result);
    return result;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct Node *head1 = a.L;
    struct Node *head2 = b.L;
    struct BigInteger result;
    result.L = NULL;
    struct Node *temp1 = head1;
    int position = 0;

    while (temp1 != NULL) {
        int carry = 0;
        struct Node *temp2 = head2;
        struct BigInteger partialResult;
        partialResult.L = NULL;
        struct Node *partialTemp = NULL;

        for (int i = 0; i < position; i++) {
            struct Node *zero = createNode(0);

            if (partialResult.L == NULL) {
                partialResult.L = zero;
                partialTemp = zero;
            } else {
                partialTemp->next = zero;
                partialTemp = zero;
            }
        }

        while (temp2 != NULL) {
            int product = (temp1->data) * (temp2->data) + carry;
            carry = product / 10;
            product = product % 10;

            struct Node *newNode = createNode(product);

            if (partialResult.L == NULL) {
                partialResult.L = newNode;
                partialTemp = newNode;
            } else {
                partialTemp->next = newNode;
                partialTemp = newNode;
            }

            temp2 = temp2->next;
        }

        if (carry > 0) {
            struct Node *carryNode = createNode(carry);
            partialTemp->next = carryNode;
        }

        result = add(result, partialResult);
        position++;
        temp1 = temp1->next;
    }

    // printf("Multiplication :: ");display(result);
    truncate(&result);
    return result;
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
    struct BigInteger res;
    res.L = NULL;
    res.sign = '+';
    res.size = 0;
    if (num2.L == NULL) {
        printf("Division by zero error\n");
        return res;
    }
    if (num1.L == NULL) {
        return res;
    }
    if (compareLists(num1.L, num2.L) == -1) {
        return res;
    }
    // Perform division of two big integers by repeated subtraction
    struct BigInteger temp = num1;
    while (compareLists(temp.L, num2.L) != -1) {
        temp = sub(temp, num2);
        res = add(res, initialize("1"));
    }
    return res;
}

// Function to calculate modulus using struct BigInteger
struct BigInteger mod(struct BigInteger num1, struct BigInteger num2) {
    struct BigInteger res;
    res.L = NULL;
    res.sign = '+';
    res.size = 0;
    if (num2.L == NULL) {
        printf("Division by zero error\n");
        return res;
    }
    if (num1.L == NULL) {
        return res;
    }
    if (compareLists(num1.L, num2.L) == -1) {
        return res;
    }
    // Perform division of two big integers by repeated subtraction
    struct BigInteger temp = num1;
    while (compareLists(temp.L, num2.L) != -1) {
        temp = sub(temp, num2);
        res = add(res, initialize("1"));
    }
    return temp;
}

int main(){
    struct BigInteger a = initialize("0001550");
    struct BigInteger b = initialize("000155");

    printf("Number 1 :: ");display(a);
    printf("Number 2 :: ");display(b);
    
    // struct Node *current = a.L;
    // while (current != NULL) {
    //     printf("%d -> ", current->data);
    //     current = current->next;
    // }
    // printf("NULL\n");

    // current = b.L;
    // while (current != NULL) {
    //     printf("%d -> ", current->data);
    //     current = current->next;
    // }
    // printf("NULL\n");

    struct BigInteger add_result = add(a,b);
    printf("Addition :: ");display(add_result);

    struct BigInteger sub_result = sub(a,b);
    printf("Subtraction :: ");display(sub_result);

    struct BigInteger mul_result = mul(a,b);
    printf("Multiplication :: ");display(mul_result);

    struct BigInteger div_result = div1(a,b);
    printf("Division :: ");display(div_result);

    struct BigInteger mod_result = mod(a,b);
    printf("Modulus :: ");display(mod_result);

    return 0;
}
