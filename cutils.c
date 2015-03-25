#include "cutils.h"

int isStartWith(const char *buf, const char *match, int sensitive)
{
#if defined(TEST)
    printf("%s is start with %s(sensitive:%d)", buf, match, sensitive);
#endif
    if (buf == NULL || match == NULL)
    {
        return -1;
    }

    int len_buf = strlen(buf); 
    int len_match = strlen(match);

    if (len_match > len_buf) {
        return 0;
    }

    if (sensitive) {
        return (0 == strncmp(buf, match, len_match));
    } else {
        return (0 == strncasecmp(buf, match, len_match));
    }
}

int isEndWith(const char* buf, const char* match, int sensitive)
{
#if defined(TEST)
    printf("%s is start with %s(sensitive:%d)", buf, match, sensitive);
#endif
    if (NULL == buf || NULL == match) {
        return -1;
    }

    int len_buf = strlen(buf); 
    int len_match = strlen(match);

    if (len_match > len_buf) {
        return 0;
    }

    const char *ptr = buf + len_buf - len_match;
    if (sensitive) {
        return (0 == strcmp(ptr, match));
    } else {
        return (0 == strcasecmp(ptr, match));
    }
}

char* replaceStr (const char *strbuf, const char *strold, const char *strnew) {
    char *strret, *p = NULL;
    char *posnews, *posold;
    size_t szold, sznew, n = 1;

#if defined(TEST)
    printf("replace all \"%s\" in \"%s\" with \"%s\"\n", strold, strbuf, strnew);
#endif

    if (!strbuf) return NULL;
    if (!strold || !strnew || !(p = strstr(strbuf, strold)))
        return strdup(strbuf);

    while (n > 0) {
        if (!(p = strstr(p+1, strold))) break;
        else n++;
    }

    szold = strlen(strold);
    sznew = strlen(strnew);

    strret = (char *) malloc(strlen(strbuf) - (n * szold )+ (n * sznew) + 1);
    p = strstr(strbuf, strold);
    strncpy(strret, strbuf, (p-strbuf));
    strret[p-strbuf] = 0;
    posold = p+szold;
    posnews = strret+(p-strbuf);
    strcpy(posnews, strnew);
    posnews += sznew;

    while (n > 0) {
        if (!(p = strstr(posold, strold)))
            break;
        strncpy(posnews, posold, p-posold);
        posnews[p-posold] = 0;
        posnews += (p-posold);
        strcpy(posnews, strnew);
        posnews += sznew;
        posold = p+szold;
    }

    strcpy(posnews, posold);
    return strret;
}

