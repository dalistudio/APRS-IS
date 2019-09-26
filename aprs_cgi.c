#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

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

int trimspace(char *str, char *newstr)//除去buff前后空格
{
    char *phead = str;
    int i = 0;
    int j = strlen(phead) - 1;
    if (phead == NULL || newstr == NULL)
    {
        return -1;
    }
    while (isspace(phead[i])&& phead[i] != '\0')
    {
        i++;
    }
    while (isspace(phead[j]) && phead[j] != '\0')
    {
        j--;
    }
    int count = j - i + 1;
    strncpy(newstr, phead + i, count);
    newstr[count] = '\0';
    return 1;
}

int getbuff(char *keybuff, char *key, char *buf)
{
    char *p = keybuff;//指针初始化
    //判断是否存在key
    p = strstr(p, key);
    if (p == NULL)
    {
        printf("There is no %s", key);
        return -1;
    }
    //判断等号是否存在
    p = strstr(p, "=");
    if (p == NULL)
    {
        printf("There is no buff for %s", key);
        return -1;
    }
    //除去key对应字符子串的前后空格
    p = keybuff+ strlen(key) + strlen("=");
    int ret=trimspace(p, buf);
    if (ret != 1)
    {
        printf("delete sapace fail");
        return -1;
    }
    return 1;
}


int main(int argc, char* argv[])
{
	char *strQuery;
	strQuery = getenv("QUERY_STRING"); // 获得 GET 方法的字符串
	// 例: http://localhost/cgi-bin/aprs.cgi?call=BH3NEK
	// GET 方法的数据为： call=BH3NEK
	// 需要验证 KEY 是否为 call ，然后在获取 BH3NEK 并计算 dohash()
	char *value;
	getbuff(strQuery,"call",value);
	short aprs = dohash(value);

	printf("Content-type:text/html\n\n");
	printf("Call=%s APRS=%d\n",value,aprs); 
	
	return 0;
}