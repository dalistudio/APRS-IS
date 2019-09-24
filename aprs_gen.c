#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define kkey 0x73e2            // this is the key for the data
short dohash(const char* thecall)
{
  char rootcall[10];     // need to copy call to remove ssid from parse
  char *p1 = rootcall;

  while ((*thecall != '-') && (*thecall != 0)) *p1++ = toupper(*thecall++);
    *p1 = 0;

  short hash = kkey;     // initialize with the key value
  short i = 0;
  short len = strlen(rootcall);
  char *ptr = rootcall;
 
  while (i < len) {         // loop through the string two bytes at a time
    hash ^= (*ptr++)<<8;   // xor high byte with accumulated hash
    hash ^= (*ptr++);     // xor low byte with accumulated hash
    i += 2;
  }
  return hash & 0x7fff;     // mask off the high bit so number is always positive
}

int main(int argc, char *argv[ ])
{
    if(argc!=2)
    {
        printf("Used: aprs_gen Call_ID\n");
    }
    short APRS_IS = dohash(argv[1 ]);
    printf("Call-Sign=%s ; APRS-IS No=%d\n", argv[1 ], APRS_IS);
    return 0;
}