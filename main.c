#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "definitions.h" /* byte, disasm_fsig */

typedef struct {
    FILE* buffer;
    byte  active;
    disasm_fsig fileSignature;
} disasm_f;

int main() {
    disasm_f* disasm = (disasm_f*)malloc(sizeof(disasm_f));

    disasm->buffer = fopen("dasm", "rb");
    disasm->active = getc(disasm->buffer);

    bool signature = false; /* found signature boolean */
    int     safety = 500;
    int     index  = 0;

    while (index < safety && !signature) {
        printf("%02x ", disasm->active); /* print previous byte before iteration */
        disasm->fileSignature.signature[index++] = (byte)disasm->active;
        for (int i = 0; i < 100; i++) {
            int knownsize = sizeof(signatures[i].signature);
            int currentsize = sizeof(disasm->fileSignature.signature);

            if (!memcmp(signatures[i].signature, disasm->fileSignature.signature, knownsize < currentsize ? knownsize : currentsize)) {
                printf("\nez gg brutha %s\n", signatures[i].filetype);
                signature = true;
                break;
            }
        }
        disasm->active = getc(disasm->buffer);
    }

    fclose(disasm->buffer);

    return 0;
}
