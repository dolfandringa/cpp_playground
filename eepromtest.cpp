#include <cstdint>
#include <stdio.h>
#include <string.h>
using namespace std;

//Lets get a simple struct
struct MyStruct {
    uint16_t a; // 16 bit integer
    uint8_t b;  // 8 bit integer
    char c[3];  // Array of 3 bytes (characters). 
                // In C++, the last character is a NULL byte (0x00)
                // so it can only contain 2 actual characters.
    uint8_t d;  // 8 bit integer
};

struct MyStruct2 {
    uint8_t a;
    uint8_t b;
    char c[3];
    float d;  
};

//EEPROM is really just an block of memory, where the address is just a pointer to a location in memory
//So a simple representation of EEPROM memory can just be an array.
//The array index is the address. In this case the EEPROM stores 16 bits (2 bytes) per address.
uint16_t EEPROM[8] = {0x4241, 0x4443, 0x0045, 0x4847, 0x0049, 0x4C4B, 0x4E4D, 0x504F};

//A simple read function then just copies the data at the address from the array to the desination.
void read(uint8_t address, uint16_t *data) {
    *data = EEPROM[address];
}
void write(uint8_t address, uint16_t *data) {
    EEPROM[address] = *data;
}

//Create a template function that gets a type (i.e. a struct) from eeprom and returns it.
template< typename T> const T &get(int address, T &t)
{

    /*
     * Templates are just a way to be lazy. They allow you to define a single function that
     * does exactly the same for multiple types, without having to know ahead of time which
     * types it will be called with. The type is denoted between <>. The pre-compiler
     * checks which types the function/template is called with
     * and just duplicates the function for each of those.
     * So if we call this from our code:
     * MyStruct t; get<MyStruct>(0, t);
     * The precompiler turns the template into this function for us:
     * const MyStruct &get(int address, MyStruct &t)
     * If we call the template with more types/structs, it just repeats the function for each.
     */

    //We generate a pointer to the same memory location that variable t starts.
    //We make the pointer 16 bits long, because our read function also returns 16 bits at a time.
    uint16_t *ptr = (uint16_t*) &t; 

    //the number of bytes that T needs. Not # elements, or variables, but bytes.
    //For MyStruct, it will print 8. But if you count, it should only use 7 bytes
    //(one 16bit int, 2x8bit int, and a 3 byte char array). This is due to padding
    //of structs. The last byte isn't actually used, but allocated nonetheless.
    printf("MyStruct size: %d\n", sizeof(T));

    //Now lets "read" all the data that type T needs from EEPROM.
    //count starts at the size of T, and as longs as it is >0, gets decreased by 2.
    //Why 2? because we get 16bits=2bytes at a time with "read", and count is in bytes.
    //Then we read the 2 bytes from EEPROM, and store it at the memory that ptr points to.
    //Then we increase pointer.
    for(int count = sizeof(T);count;count-=2, address++) {
        read(address, ptr);
        printf("Value %d: 0x%.4X\n", address, *ptr);
        ptr++; //Move the pointer up by 16 bits;
    }
    return t;
}

template< typename T> void put(int address, T &t)
{

    uint16_t *ptr = (uint16_t*) &t; 
    printf("MyStruct size: %d\n", sizeof(T));
    for(int count = sizeof(T);count;count-=2, address++) {
        write(address, ptr);
        printf("Wrote value %d: 0x%.4X\n", address, *ptr);
        ptr++; //Move the pointer up by 16 bits;
    }
}


//Convenience functions to print an array.
char buff[60];
char* print_eeprom() {
    *buff = 0;
    for(uint8_t i=0;i<8;i++) 
        sprintf(buff+strlen(buff), "0x%.4X, ", EEPROM[i]);
    return buff;

}

int main(){
    
    MyStruct ms; //declare (and allocate memory) for the stuct variable
    
    printf("EEPROM: {%s}\n", print_eeprom());

    get<MyStruct>(0, ms); //Fill the struct with data from EEPROM.
    printf(">get<MyStruct>(0, ms);\n");
    printf("ms.a (uint16_t): 0x%.4X\n", ms.a);
    printf("ms.b (uint8_t): 0x%.2X\n", ms.b);
    printf("ms.c (char[3]): %s\n", ms.c);
    printf("ms.d (uint8_t): 0x%.2X\n", ms.d);
    printf("Since ms.c is a char[3] array, the values stored with it are printed as characters.\n\
            Characters are just 8 bits (1 byte), and therefore have an integer/hex presentation as well.\n\
            You can find them in any ASCII table. Of course I chose the HEX numbers of the EEPROM array\n\
            so they make sense. Since C strings (character arrays) are terminated by a NULL byte (0x00),\n\
            I placed those strategically in the array as well. Try to find them in the array!\n");
    
    printf("\n\n");
    printf("EEPROM: {%s}\n", print_eeprom());
   

    //Now do the same, but start at address 2 instead of 0
    get<MyStruct>(2, ms);
    printf("get<MyStruct>(2, ms);\n");
    printf("ms.a (uint16_t): 0x%.4X\n", ms.a);
    printf("ms.b (uint8_t): 0x%.2X\n", ms.b);
    printf("ms.c (char[3]): %s\n", ms.c);
    printf("ms.d (uint8_t): 0x%.2X\n", ms.d);

    //A little more complex becuase of the float value and struct padding with 0x00 after ms.c
    MyStruct2 ms2;
    ms2.a=1;
    ms2.b=2;
    strcpy(ms2.c, "Hi");
    ms2.d=15.6;
    put<MyStruct2>(0, ms2);
    get<MyStruct2>(0, ms2);

    printf("get<MyStruct>(2, ms);\n");
    printf("ms.a (uint8_t): 0x%.2X\n", ms2.a);
    printf("ms.b (uint8_t): 0x%.2X\n", ms2.b);
    printf("ms.c (char[3]): %s\n", ms2.c);
    printf("ms.d (float): %f\n", ms2.d);
}
