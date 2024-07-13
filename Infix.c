#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_BOYUTU 100
typedef struct {
    char elemanlar[MAX_STACK_BOYUTU];
    int üst;
} Stack;

void stackiBaslat(Stack* stack) {
    stack->üst = -1;
}

int stackDoluMu(Stack* stack) {
    return stack->üst == MAX_STACK_BOYUTU - 1;
}

int stackBosMu(Stack* stack) {
    return stack->üst == -1;
}

void stackeEkle(Stack* stack, char veri) {
    if (!stackDoluMu(stack)) {
        stack->elemanlar[++stack->üst] = veri;
    }
}

char stacktenCikar(Stack* stack) {
    if (!stackBosMu(stack)) {
        return stack->elemanlar[stack->üst--];
    }
    return '\0'; 
}

char stackeBak(Stack* stack) {
    if (!stackBosMu(stack)) {
        return stack->elemanlar[stack->üst];
    }
    return '\0';  
}

int operatorOnceligi(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    return 0;
}

int operatorMu(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void infixToPostfix(char* infix) {
    Stack stack;
    stackiBaslat(&stack);
    int i = 0;

    printf("Postfix İfade: ");
    while (infix[i] != '\0') {
        if (isalnum(infix[i])) {
            printf("%c", infix[i]);
        } else if (infix[i] == '(') {
            stackeEkle(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!stackBosMu(&stack) && stackeBak(&stack) != '(') {
                printf("%c", stacktenCikar(&stack));
            }
            if (!stackBosMu(&stack) && stackeBak(&stack) != '(') {
                printf("Geçersiz ifade\n");
                return;
            } else {
                stacktenCikar(&stack);
            }
        } else if (operatorMu(infix[i])) {
            while (!stackBosMu(&stack) && operatorOnceligi(infix[i]) <= operatorOnceligi(stackeBak(&stack))) {
                printf("%c", stacktenCikar(&stack));
            }
            stackeEkle(&stack, infix[i]);
        }
        i++;
    }

    while (!stackBosMu(&stack)) {
        printf("%c", stacktenCikar(&stack));
    }
    printf("\n");
}

int main() {
    int secim;
    char infix[100];

    do {
        printf("\nMenü\n");
        printf("1. Infix ifadeyi dönüştür\n");
        printf("2. Çıkış\n");
        printf("Seçiminizi yapın: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Infix ifade girin: ");
                scanf("%s", infix);
                infixToPostfix(infix);
                break;
            case 2:
                printf("Programdan çıkıldı");
                break;
            default:
                printf("Geçersiz seçenek, lütfen tekrar deneyin.\n");
        }
    } while (secim != 2);

    return 0;
}
