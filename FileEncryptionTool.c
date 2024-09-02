#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void encryptXOR(const char *inputFileName, const char *outputFileName, const char *key);
void decryptXOR(const char *inputFileName, const char *outputFileName, const char *key);
void encryptCaesar(const char *inputFileName, const char *outputFileName, int shift);
void decryptCaesar(const char *inputFileName, const char *outputFileName, int shift);
void encryptVigenere(const char *inputFileName, const char *outputFileName, const char *key);
void decryptVigenere(const char *inputFileName, const char *outputFileName, const char *key);

int main() {
    int choice, shift;
    char inputFileName[100], outputFileName[100], key[100];

    printf("File Encryption and Decryption Tool\n");
    printf("1. Encrypt File using XOR\n");
    printf("2. Decrypt File using XOR\n");
    printf("3. Encrypt File using Caesar Cipher\n");
    printf("4. Decrypt File using Caesar Cipher\n");
    printf("5. Encrypt File using Vigenere Cipher\n");
    printf("6. Decrypt File using Vigenere Cipher\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6) {
        printf("Enter input file name: ");
        scanf("%s", inputFileName);
        printf("Enter output file name: ");
        scanf("%s", outputFileName);
    }

    switch (choice) {
        case 1:
            printf("Enter key: ");
            scanf("%s", key);
            encryptXOR(inputFileName, outputFileName, key);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%s", key);
            decryptXOR(inputFileName, outputFileName, key);
            break;
        case 3:
            printf("Enter shift value: ");
            scanf("%d", &shift);
            encryptCaesar(inputFileName, outputFileName, shift);
            break;
        case 4:
            printf("Enter shift value: ");
            scanf("%d", &shift);
            decryptCaesar(inputFileName, outputFileName, shift);
            break;
        case 5:
            printf("Enter key: ");
            scanf("%s", key);
            encryptVigenere(inputFileName, outputFileName, key);
            break;
        case 6:
            printf("Enter key: ");
            scanf("%s", key);
            decryptVigenere(inputFileName, outputFileName, key);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

void encryptCaesar(const char *inputFileName, const char *outputFileName, int shift) {
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    while (fread(&ch, 1, 1, inputFile)) {
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + shift) % 26 + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + shift) % 26 + 'A';
        }
        fwrite(&ch, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File encrypted with Caesar Cipher successfully!\n");
}

void decryptCaesar(const char *inputFileName, const char *outputFileName, int shift) {
    encryptCaesar(inputFileName, outputFileName, 26 - shift);
    printf("File decrypted with Caesar Cipher successfully!\n");
}
void encryptXOR(const char *inputFileName, const char *outputFileName, const char *key) {
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int keyLen = strlen(key);
    int i = 0;
    char ch;

    while (fread(&ch, 1, 1, inputFile)) {
        ch ^= key[i % keyLen];  // XOR operation
        fwrite(&ch, 1, 1, outputFile);
        i++;
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File encrypted/decrypted with XOR Cipher successfully!\n");
}

void decryptXOR(const char *inputFileName, const char *outputFileName, const char *key) {
    // XOR decryption is the same as encryption
    encryptXOR(inputFileName, outputFileName, key);
}
void encryptVigenere(const char *inputFileName, const char *outputFileName, const char *key) {
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int keyLen = strlen(key);
    int i = 0;
    char ch;

    while (fread(&ch, 1, 1, inputFile)) {
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + (key[i % keyLen] - 'a')) % 26 + 'a';
            i++;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + (key[i % keyLen] - 'A')) % 26 + 'A';
            i++;
        }
        fwrite(&ch, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File encrypted with Vigenere Cipher successfully!\n");
}

void decryptVigenere(const char *inputFileName, const char *outputFileName, const char *key) {
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int keyLen = strlen(key);
    int i = 0;
    char ch;

    while (fread(&ch, 1, 1, inputFile)) {
        if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' - (key[i % keyLen] - 'a') + 26) % 26 + 'a';
            i++;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' - (key[i % keyLen] - 'A') + 26) % 26 + 'A';
            i++;
        }
        fwrite(&ch, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File decrypted with Vigenere Cipher successfully!\n");
}
