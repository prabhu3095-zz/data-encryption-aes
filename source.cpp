#include<stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>

using namespace std;

/*LOOK UP TABLE FOR S_BOX VALUES*/

unsigned char S_box[256]={
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/*LOOK UP TABLE FOR REVERSE S_BOX VALUES*/

unsigned char rS_box[256]={
0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

/*LOOK UP TABLE FOR ROUND CONSTANT VALUES

    RC[1] = 0x01
    RC[j] = 0x02 * RC[j - 1]        */

unsigned round_constant[255]={
0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb
};

unsigned char getSboxValue(unsigned char num)
{
    return S_box[num];
}
unsigned char getSboxInvert(unsigned char num)
{
    return rS_box[num];
}

void shift_row(unsigned char *word)
{
    unsigned char c;
    c = word[0];
    for (int i = 0; i < 3; i++)
        word[i] = word[i+1];
    word[3] = c;
}

unsigned char getRconValue(unsigned char num)
{
    return round_constant[num];
}

/* g() function to calculate every (4*n-1)th word(0-based indexing of the words) */

void g(unsigned char *word, int iteration)
{

/* Perform a one-byte left circular rotation on the argument 4-byte word. */

    shift_row(word);

/* apply S-Box substitution on all 4 parts of the 32-bit word */

    for (int i = 0; i < 4; i++)
    {
        word[i] = getSboxValue(word[i]);
    }

/* XOR the output of the round constant operation with i to the first part (leftmost) only
    because  the other 3 bytes are zero and XOR with them gives the same value.*/

    word[0] = word[0]^getRconValue(iteration);

}

/* KeySize gives the total length of the key in bytes */

enum keySize
{
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize Size, size_t expandedKeySize)
{
    //cout<<endl<<Size<<" "<<expandedKeySize<<endl;

    /* current expanded keySize, in bytes */

    int currentSize = 0;
    int rconIteration = 1;       //keeps track of the number of iterations till we get desired length key schedule
    int i;
    unsigned char t[4] = {0};    // temporary 4-byte variable

    /* copy the input key to the expandedKey array as the first 4 words remain the same */

    for (i = 0; i < Size; i++)
        expandedKey[i] = key[i];

    currentSize += Size;

    while (currentSize < expandedKeySize)
    {
        /* assign the previous 4 bytes to the temporary value t */

        for (i = 0; i < 4; i++)
        {
            t[i] = expandedKey[(currentSize - 4) + i];
        }

        /* every 16 bytes we apply the g() function to t
        * and increment rconIteration afterwards
        */

        if(currentSize % Size == 0)
        /* This word is calculated by the formula : W[i+4] = W[i] ^ g(W[i+3]) */
        {
            g(t, rconIteration++);
            //cout<<rconIteration<<endl;
        }
        /* For 256-bit keys, we add an extra sbox to the calculation */

        if(Size == SIZE_32 && ((currentSize % Size) == 16)) {
            for(i = 0; i < 4; i++)
                t[i] = getSboxValue(t[i]);
        }

        /*  We XOR t with the four-byte block 16 bytes before the new expanded key.
            This becomes the next four bytes in the expanded key.
            W[i+4] = W[i] ^ W[i+3] */

        for(i = 0; i < 4; i++) {
            expandedKey[currentSize] = expandedKey[currentSize - Size] ^ t[i];
            //cout<<hex<<(int)expandedKey[currentSize]<<" ";
            currentSize++;
        }


    }
}

void subBytes(unsigned char *state)
{
    /* substitute all the values from the state with the value in the SBox
        using the state value as index for the SBox
    */

    for (int i = 0; i < 16; i++)
        state[i] = getSboxValue(state[i]);
}

void shiftRow(unsigned char *state, unsigned char nbr)
{
    unsigned char tmp;

    /* each iteration shifts the row to the left by 1 */

    for (int i = 0; i < nbr; i++)
    {
        tmp = state[0];
        for (int j = 0; j < 3; j++)
            state[j] = state[j+1];
        state[3] = tmp;
    }
}

void shiftRows(unsigned char *state)
{
    int i;

    /* iterate over the 4 rows and call shiftRow() with that row */

    for (i = 0; i < 4; i++)
        shiftRow(state+i*4, i);
}

/* XOR the state matrix with the Key matrix */

void addRoundKey(unsigned char *state, unsigned char *roundKey)
{
    for (int i = 0; i < 16; i++)
        state[i] = state[i] ^ roundKey[i] ;
}

unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for(counter = 0; counter < 8; counter++) {
        if((b & 1) == 1)
            p ^= a;

        hi_bit_set = (a & 0x80);
        a <<= 1;

        if(hi_bit_set == 0x80)
            a ^= 0x1b;

        b >>= 1;
    }
    return p;
}

/*
                  COLUMN MIXING
                ------------------

    | 02 03 01 01 |     | S[0,0] S[0,1] S[0,2] S[0,3] |
    | 01 02 03 01 |  *  | S[1,0] S[1,1] S[1,2] S[1,3] |
    | 01 01 02 03 |     | S[2,0] S[2,1] S[2,2] S[2,3] |
    | 03 01 01 02 |     | S[3,0] S[3,1] S[3,2] S[3,3] |


*/

void mixColumn(unsigned char *column)
{
    unsigned char cpy[4];
    int i;
    for(i = 0; i < 4; i++)
    {
        cpy[i] = column[i];
    }
    column[0] = galois_multiplication(cpy[0],2) ^
                galois_multiplication(cpy[3],1) ^
                galois_multiplication(cpy[2],1) ^
                galois_multiplication(cpy[1],3);
    column[1] = galois_multiplication(cpy[1],2) ^
                galois_multiplication(cpy[0],1) ^
                galois_multiplication(cpy[3],1) ^
                galois_multiplication(cpy[2],3);
    column[2] = galois_multiplication(cpy[2],2) ^
                galois_multiplication(cpy[1],1) ^
                galois_multiplication(cpy[0],1) ^
                galois_multiplication(cpy[3],3);
    column[3] = galois_multiplication(cpy[3],2) ^
                galois_multiplication(cpy[2],1) ^
                galois_multiplication(cpy[1],1) ^
                galois_multiplication(cpy[0],3);
}

void mixColumns(unsigned char *state)
{
    int i, j;
    unsigned char column[4];

    /* iterate over the 4 columns */

    for (i = 0; i < 4; i++)
    {
        /* construct one column by iterating over the 4 rows */

        for (j = 0; j < 4; j++)
        {
            column[j] = state[(j*4)+i];
        }

        /* apply the mixColumn on one column */

        mixColumn(column);

        /* put the values back into the state */

        for (j = 0; j < 4; j++)
        {
            state[(j*4)+i] = column[j];
        }
    }
}

void aes_round(unsigned char *state, unsigned char *roundKey)
{
    subBytes(state);

    cout<<endl<<"After SubByte: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    shiftRows(state);

    cout<<endl<<"After Row Shifting: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    mixColumns(state);

    cout<<endl<<"After Column Mixing: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);
}

void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey)
{
    int i,j;

    /* iterate over the columns */

    for (i = 0; i < 4; i++)
    {
        /* iterate over the rows */
        for (j = 0; j < 4; j++)
            roundKey[(i+(j*4))] = expandedKey[(i*4)+j];
    }
}

void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    int i = 0;
    unsigned char roundKey[16];

    createRoundKey(expandedKey, roundKey);

    cout<<endl<<"First Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)roundKey[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);

    cout<<endl<<"After Adding Round key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    for (i = 1; i < nbrRounds; i++) {

        createRoundKey(expandedKey + 16*i, roundKey);

        cout<<endl<<"Round Key: ";
        for(int i=0; i<16; i++)
            cout<<hex<<(int)roundKey[i]<<" ";
        cout<<endl;

        aes_round(state, roundKey);

        cout<<endl<<"After Adding Round key: ";
        for(int i=0; i<16; i++)
            cout<<hex<<(int)state[i]<<" ";
        cout<<endl;
    }

    createRoundKey(expandedKey + 16*nbrRounds, roundKey);

    cout<<endl<<"Final Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)roundKey[i]<<" ";
    cout<<endl;

    subBytes(state);

    cout<<endl<<"After SubByte: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    shiftRows(state);

    cout<<endl<<"After Row Shifting: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);

    cout<<endl<<"After Adding Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

}

char aes_encrypt(unsigned char *input, int start, int finish, unsigned char *output, unsigned char *key, enum keySize Size)
{
    /* the expanded keySize */
    int expandedKeySize;

    /* the number of rounds */
    int nbrRounds;

    /* the expanded key */
    unsigned char expandedKey[500];

    /* the 128 bit block to encode */
    unsigned char block[16];
    int i,j;

    /* set the number of rounds */
    switch (Size)
    {
        case SIZE_16:
        nbrRounds = 10;
        break;
        case SIZE_24:
        nbrRounds = 12;
        break;
        case SIZE_32:
        nbrRounds = 14;
        break;
        default:
        //return UNKNOWN_KEYSIZE;
        break;
    }
    //cout<<"abc\n";
    expandedKeySize = (nbrRounds+1)*16;

    unsigned char state[100];

    for(int i=start, j=0; i<=finish; i++, j++)
    {
        state[j]=input[i];
    }

    expandKey(expandedKey, key, Size, expandedKeySize);
    aes_main(state, expandedKey, nbrRounds);

    for(int i=start, j=0; i<=finish; i++, j++)
    {
        input[i]=state[j];
    }

}

//DECRYPTION
void invSubBytes(unsigned char *state)
{
    int i;

    /* substitute all the values from the state with the value in the SBox
    * using the state value as index for the SBox
    */

    for (i = 0; i < 16; i++)
        state[i] = getSboxInvert(state[i]);
}

void invShiftRow(unsigned char *state, unsigned char nbr)
{
    int i, j;
    unsigned char tmp;

    /* each iteration shifts the row to the right by 1 */

    for (i = 0; i < nbr; i++)
    {
        tmp = state[3];
        for (j = 3; j > 0; j--)
            state[j] = state[j-1];
        state[0] = tmp;
    }
}

void invShiftRows(unsigned char *state)
{
    int i;

    /* iterate over the 4 rows and call invShiftRow() with that row */

    for (i = 0; i < 4; i++)
        invShiftRow(state+i*4, i);
}

/*
                  COLUMN MIXING
                ------------------

    | 0E 0B 0D 09 |     | S[0,0] S[0,1] S[0,2] S[0,3] |
    | 09 0E 0B 0D |  *  | S[1,0] S[1,1] S[1,2] S[1,3] |
    | 0D 09 0E 0B |     | S[2,0] S[2,1] S[2,2] S[2,3] |
    | 0B 0D 09 0E |     | S[3,0] S[3,1] S[3,2] S[3,3] |


*/

void invMixColumn(unsigned char *column)
{
    unsigned char cpy[4];
    int i;

    for(i = 0; i < 4; i++)
    {
        cpy[i] = column[i];
    }

    column[0] = galois_multiplication(cpy[0],14) ^
    galois_multiplication(cpy[3],9) ^
    galois_multiplication(cpy[2],13) ^
    galois_multiplication(cpy[1],11);

    column[1] = galois_multiplication(cpy[1],14) ^
    galois_multiplication(cpy[0],9) ^
    galois_multiplication(cpy[3],13) ^
    galois_multiplication(cpy[2],11);

    column[2] = galois_multiplication(cpy[2],14) ^
    galois_multiplication(cpy[1],9) ^
    galois_multiplication(cpy[0],13) ^
    galois_multiplication(cpy[3],11);

    column[3] = galois_multiplication(cpy[3],14) ^
    galois_multiplication(cpy[2],9) ^
    galois_multiplication(cpy[1],13) ^
    galois_multiplication(cpy[0],11);
}

void invMixColumns(unsigned char *state)
{
    int i, j;
    unsigned char column[4];

    /* iterate over the 4 columns */

    for (i = 0; i < 4; i++)
    {
        /* construct one column by iterating over the 4 rows */

        for (j = 0; j < 4; j++)
        {
            column[j] = state[(j*4)+i];
        }

        /* apply the invMixColumn on one column */

        invMixColumn(column);

        /* put the values back into the state */
        for (j = 0; j < 4; j++)
        {
            state[(j*4)+i] = column[j];
        }
    }
}

void aes_invRound(unsigned char *state, unsigned char *roundKey)
{
    invShiftRows(state);

    cout<<endl<<"After Row Shifting (Right): ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    invSubBytes(state);

    cout<<endl<<"After InvSubByte: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);

    cout<<endl<<"After Adding Round key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    invMixColumns(state);

    cout<<endl<<"After Inverse Column Mixing: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;
}

void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    int i = 0;
    unsigned char roundKey[16];

    createRoundKey(expandedKey + 16*nbrRounds, roundKey);

    cout<<endl<<"First Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)roundKey[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);

    cout<<endl<<"After Adding Round key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    for (i = nbrRounds-1; i > 0; i--) {
        createRoundKey(expandedKey + 16*i, roundKey);

        cout<<endl<<"Round Key: ";
        for(int i=0; i<16; i++)
            cout<<hex<<(int)roundKey[i]<<" ";
        cout<<endl;

        aes_invRound(state, roundKey);

    }

    createRoundKey(expandedKey, roundKey);

    cout<<endl<<"Final Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)roundKey[i]<<" ";
    cout<<endl;

    invShiftRows(state);

    cout<<endl<<"After Row Shifting (Right): ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    invSubBytes(state);

    cout<<endl<<"After InvSubByte: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;

    addRoundKey(state, roundKey);

    cout<<endl<<"After Adding Round Key: ";
    for(int i=0; i<16; i++)
        cout<<hex<<(int)state[i]<<" ";
    cout<<endl;
}

void aes_decrypt(unsigned char *input, int start, int finish, unsigned char *output, unsigned char *key, enum keySize Size)
{
    /* the expanded keySize */
    int expandedKeySize;

    /* the number of rounds */
    int nbrRounds;

    /* the expanded key */
    unsigned char expandedKey[500];

    /* the 128 bit block to encode */
    unsigned char block[16];
    int i,j;

    /* set the number of rounds */
    switch (Size)
    {
        case SIZE_16:
        nbrRounds = 10;
        break;
        case SIZE_24:
        nbrRounds = 12;
        break;
        case SIZE_32:
        nbrRounds = 14;
        break;
        default:
        //return UNKNOWN_KEYSIZE;
        break;
    }
    expandedKeySize=(nbrRounds+1)*16;

    unsigned char state[200];
    for(int i=start, j=0; i<=finish; i++, j++)
    {
        state[j]=input[i];
    }

    expandKey(expandedKey, key, Size, expandedKeySize);
    aes_invMain(state, expandedKey, nbrRounds);
    for(int i=start, j=0; i<=finish; i++, j++)
    {
        input[i]=state[j];
    }

}

int main()
{
    int t;
    //freopen("input3.txt", "r", stdin);
    //freopen("output_source3.txt", "w", stdout);

    //TEST FOR KEY-EXPANSION FUCTION
    //------------------------------

    unsigned char key[20];//={0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8 ,0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
    unsigned char expandedKey[500];
    size_t s=176;     //There are 44 words for 128-bit key. We need 11 rounds in total. Hence, size = 11*4 = 44 words = 44*4 = 176 bytes.
    //expandKey(expandedKey, key, SIZE_16 , s);


    int n;

    cin>>n;
    unsigned char input[100];//={11,20,80,30,20,10,30,5,7,6,8,8,80,9,9,2};
    unsigned char output[500];
    int key1[100], input1[100];
    cin>>input;
    cin>>key;
    /*for(int i=0; i<n; i++)
    {
        cin>>input1[i];
        input[i]=input1[i];
    }*/
    int j=n;
    if(n%16!=0)
    {

        while(j%16!=0)
        {
            input[j]=0;
            j++;
        }

    }

    /*for(int i=0; i<16; i++)
    {
        cin>>key1[i];
        key[i]=key1[i];
    }*/

    cout<<"INPUT PLAINTEXT : ";

    for(int i=0; i<n; i++)
    {
        cout<<hex<<(int)input[i]<<" ";
    }
    cout<<endl<<endl<<"INPUT KEY : ";

    for(int i=0; i<16; i++)
    {
        cout<<hex<<(int)key[i]<<" ";
    }
    cout<<endl;

    //expandKey(expandedKey, key, SIZE_16, s);
    cout<<endl<<"BEFORE ENCRYPTION : ";
    cout<<input;
    /*for(int i=0; i<n; i++)
        cout<<hex<<(int)input[i]<<" ";*/
    cout<<endl<<endl;

    for(int i=0; i<j/16; i++)
    {
        aes_encrypt(input, i*16, i*16+15, output, key, SIZE_16);
    }

    cout<<endl<<"AFTER ENCRYPTION : ";
    cout<<input;
    /*for(int i=0; i<n; i++)
        cout<<hex<<(int)input[i]<<" ";*/
    cout<<endl<<endl;

    for(int i=0; i<j/16; i++)
    {
        aes_decrypt(input, i*16, i*16+15, output, key, SIZE_16);
    }

    cout<<endl<<"AFTER DECRYPTION : ";
    cout<<input;
    /*for(int i=0; i<n; i++)
    {
        cout<<hex<<(int)input[i]<<" ";
    }*/

    return 0;
}
