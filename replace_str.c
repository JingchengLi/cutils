#include "cutils.h"

char* replace_str (const char *strbuf, const char *strold, const char *strnew) {
    char *strret, *p = NULL;
    char *posnews, *posold;
    size_t szold = strlen(strold);
    size_t sznew = strlen(strnew);
    size_t n = 1;

    if (!strbuf) return NULL;
    if (!strold || !strnew || !(p = strstr(strbuf, strold)))
        return strdup(strbuf);

    while (n > 0) {
        if (!(p = strstr(p+1, strold))) break;
        else n++;
    }

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
