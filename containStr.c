#include <stdio.h>
#include <assert.h>

int containStr(const char* src, const char* substring) {
    const char* p, *q, *pos;

    if (!src || !substring) {
        return 0;
    }
    pos = NULL;
    p = src;
    q = substring;
    while (*p) {
        while (*p == *q) {
            p++;
            q++;

            if (*p == *substring) pos = p;

            if ('\0' == *q) {
                return 1;
            } else if ('\0' == *p) {
                return 0;
            } else if (*p != *q) {
                if (pos) {
                    q = substring;
                    p = pos;
                } else
                    break;
            }
        }
        p++;
    }
    return 0;

}

int main() {
    assert(1 == containStr("sssssstr", "str"));
    assert(1 == containStr("ssstrsss", "strsss"));
    assert(1 == containStr("ssstrsss", "str"));
    assert(0 == containStr("sssssstr", "ttt"));
    assert(0 == containStr("sssssstr", "ttt"));
    printf("xx=================================");
    return 0;
}