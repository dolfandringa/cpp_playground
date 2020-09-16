#include <iostream>
#include <stdint.h>

using namespace std;

int main() {
uint16_t a = 0x6463;
    uint16_t *a_ptr = &a;
    uint8_t b = 8;
    uint8_t *ptr = (uint8_t*) malloc(sizeof(uint8_t));
    *ptr = (uint8_t) *a_ptr;
    cout<<"Hello World: " << hex << ((a & 0x00FF) | (b << 8)) << endl;
    cout<<"Hello World: " << hex <<  *ptr << endl;
    *ptr = (*a_ptr >> 8);
    cout<<"Hello World: " << hex <<  *ptr << endl;
    return 0;
}
