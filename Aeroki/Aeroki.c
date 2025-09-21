// In Aeroki We just prototype functions not define yet.
#include "Aeroki.h"

// Define what function do
// Now I just define it as doing nothing
void __Ark_Shell(){}

int main(int argc, char *argv[]){
    if (argc == 1){
        __Ark_Shell();
        printf("Exited Shell Mode\n");
        return 0;
    }

    for (size_t Idx = 0; Idx < argc; ++Idx){
    
    }

    return 0;
}
