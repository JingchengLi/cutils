#include "cutils.h"

inline void EXPECT_INT(int result, int expect) {
    if ((result) == (expect)) 
    { 
        printf(" result is \"%d\", expect is \"%d\"(SUCCESS)\n\n", (result), (expect)); 
    } else { 
        printf(" result is \"%d\", expect is \"%d\"(FAILED)\n\n", (result), (expect));
    }
}

inline void EXPECT_STRING(const char* result, const char* expect) {
    if ((NULL == (result) && (result) == (expect)) || 
        ((result) && (expect) || 0 == strcmp((result), (expect)))) 
    { 
        printf(" result is \"%s\", expect is \"%s\"(SUCCESS)\n\n", (result), (expect)); 
    } else { 
        printf(" result is \"%s\", expect is \"%s\"(FAILED)\n\n", (result), (expect)); 
    }
}

void test_replaceStr()
{
    char* str = NULL;
    str = replaceStr("aaacccaaaddd", "aaa", "bbb");
    EXPECT_STRING(str, "bbbcccbbbddd");
    free(str);

    str = replaceStr("123456&abc&", "&", "@"); 
    EXPECT_STRING(str, "123456@abc@");
    free(str);

    str = replaceStr("&abc&123&", "&", "@");
    EXPECT_STRING(str, "@abc@123@");
    free(str);
}

void test_isStartWith()
{
    EXPECT_INT(isStartWith("aaaabbb", "aaa", 0), 1);
    EXPECT_INT(isStartWith("aaaabbb", "AAA", 1), 0);
    EXPECT_INT(isStartWith("aaaabbb", "BBB", 0), 0);
}

int main()
{
    test_replaceStr();
    test_isStartWith();
}

//gcc test_framework.c cutils.c -DTEST -o test
