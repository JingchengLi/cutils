#include "cutils.h"

int test_replace_str(const char* buffer, const char* old, const char* new, const char* expect_result)
{
    char* str = replace_str(buffer, old, new);

    printf("INPUT:%s ====> OUTPUT:%s", buffer, str);
    if (0 == strcmp(expect_result, str))
        printf("(SUCCESS)");
    else
        printf("(FAILED)");
    printf("\n");
        
    free(str);
}

int main()
{
    test_replace_str("aaacccaaaddd", "aaa", "bbb", "bbbcccbbbddd");
    test_replace_str("123456&abc&", "&", "@", "123456@abc@"); 
    test_replace_str("&abc&123&", "&", "@", "@abc@123@");
}

/* 
INPUT:aaacccaaaddd ====> OUTPUT:bbbcccbbbddd(SUCCESS)
INPUT:123456&abc& ====> OUTPUT:123456@abc@(SUCCESS)
INPUT:&abc&123& ====> OUTPUT:@abc@123@(SUCCESS)
*/

