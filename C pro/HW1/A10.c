#include <stdio.h>
#include <stdint.h>

struct pack_array {
    uint32_t array;
    uint32_t count0 : 8;
    uint32_t count1 : 8;
};

void array2struct(int arr[], struct pack_array *p) {
    p->array = 0;
    p->count0 = 0;
    p->count1 = 0;
    
    for (int i = 0; i < 32; i++) {
        if (arr[i] == 1) {
            p->count1++;
            p->array |= (1U << (31 - i));
        } else {
            p->count0++;
        }
    }
}

int main(void) {
    int arr[32];
    struct pack_array packed;
    
    for (int i = 0; i < 32; i++) {
        scanf("%d", &arr[i]);
    }
    
    array2struct(arr, &packed);
    
    printf("%u %u %u\n", packed.array, packed.count0, packed.count1);
    
    return 0;
}
