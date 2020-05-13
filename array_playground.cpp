#include <cstdint> //so we can use uint8_t, uint16_t, etc
#include <stdio.h> //printf
#include <string.h> //strlen


/*
 * simply compile with g++ -o array_playground array_playground.cpp
 * and then run ./array_playground
 */

//Lets take a simple array of 8 16-bit (2 byte) integers (written in hex notation)
uint16_t MYARR[8] = {0x4241, 0x4443, 0x0045, 0x4847, 0x0049, 0x4C4B, 0x4E4D, 0x504F};


//Convenience function that returns MYARR as a string
char buff[60];
char* print_myarr() {
    *buff = 0;
    for(uint8_t i=0;i<8;i++) 
        sprintf(buff+strlen(buff), "0x%.4X, ", MYARR[i]);
    return buff;

}

int main(){
    printf("uint16_t MYARR[8]: {%s}\n", print_myarr());

    /*
     * Arrays are actually just pointers to the first element of the array
     * with information on how many elements there are.
     * so we can create a second pointer that points to the same element.
     */
    
    uint16_t *ptr = MYARR;
    printf("\n>uint16_t *ptr = MYARR;\n");
    printf("Value stored at ptr: 0x%.4X\n",*ptr);

    /*
     * Incrementing a pointer makes it point to the next memory address
     * of the same type/size. So in this case, since the pointer is a 16 bit
     * pointer, incrementing it, makes it point to the next 16 bits,
     * which so happens to be the next element of the array as well.
     */
    
    ptr++;
    printf("\n>ptr++;\n");
    printf("Value stored at ptr: 0x%.4X\n",*ptr);
    
    /*
     * But you can also make a smaller pointer. In this case of 8 bits.
     * Now the pointer will only point to 8 bits. Note that in the notation 0x4241
     * the first byte is the right most byte (0x41).
     * Incrementing it will point to the next 8 bits as well.
     * Now we're taking smaller steps than the array allows.
     */
    
    uint8_t* ptr2 = (uint8_t*) MYARR; //make a pointer that points to the same memory address
    // that MYARR points to, but now only to the first 8 bits, not 16.
    printf("\n>uint8_t *ptr2 = (uint8_t*) MYARR;\n");
    printf("Value stored at ptr2: 0x%.2X\n",*ptr2);
   
    ptr2++; //point to the next 8 bits (2nd half of the 1st array element)
    printf(">ptr2++;\n");
    printf("Value stored at ptr2: 0x%.2X\n",*ptr2);

    /* You can also store data in the memory location that a pointer points too.
     * But do remember that multiple pointers can point to that address, so all will be changed
     * In this case, MYARR[1] also points there, so it gets changed as well.
     */
    
    *ptr=0x4444; // store a value in the memory location that ptr points to.
    printf("\n>*ptr = 0x4444;\n");
    printf("Value stored at ptr: 0x%.4X\n",*ptr);
    printf("MYARR: %s\n", print_myarr());
    
    
    /*
     * You can also increment and assign values to a pointer in one go.
     * This first assigns a value to the memory that ptr points to, and then increments the pointer
     */

    *ptr++ = 0x4545;
    printf("\n>*ptr++ = 0x4545;\n");
    printf("Value stored at ptr: 0x%.4X\n",*ptr);
    printf("MYARR: %s\n", print_myarr());
    
    /*
     * You can do the oposite too. In this case first the pointer is incremented, and then a value
     * is assigned to the memory it now points to.
     */

    *++ptr = 0x4646;
    printf("\n>*++ptr = 0x4646;\n");
    printf("Value stored at ptr: 0x%.4X\n",*ptr);
    printf("MYARR: %s\n", print_myarr());
    
}
