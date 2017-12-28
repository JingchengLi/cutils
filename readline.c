//int recv(char* buf, int len);
//
//read_line(): "123"
//    recv(): "123\n45\n6789"
//read_line(): "45"
//read_line(): "6789abcde"
//    recv(): "abc"
//    recv(): "de\n"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 16

const char* content = "123\n45\nabcde\n123456789012345\n88888888\n666666\n7\n" ;
char save[BUFLEN + 1];
static char buf[BUFLEN];

void printbuf(char* buf, int buf_len) {
    int i = buf_len;
    char* p = buf;
    while(i > 0) {
        printf("%c", *p++);
        i--;
    }
    printf("\n");
}

int recv(char* buf, int buf_len) {
    static int pos = 0;
    int count;
    int len = strlen(content);
    if (len-pos <= 0)
        return 0;

    printf("content len:%d\n", len);
    if (buf_len < len-pos) {
        memcpy(buf, content+pos, buf_len);
        pos += buf_len;
        printf("left:%d\n", len-pos);
        return buf_len;
    } else {
        memcpy(buf, content+pos, len-pos);
        count = len - pos;
        pos = len;
        printf("left:0, count:%d\n", count);
        return count;
    }
}

char* read_line() {
    char *p, *pos;
    int i = 0;

    for (;;) {
        if (*(buf + BUFLEN - 1) == '\0') {
            int unused;

            p = buf;
            if (buf[0] == '\0') {
                while (*p == '\0' && p < buf + BUFLEN) {
                    p++;
                }
                if (p == buf+BUFLEN) {
                    p = buf;
                } else {
                    // content end
                    while (*p != '\0' && *p != '\n') {
                        save[i++] = *p;
                        *p = '\0';
                        p++;
                    }
                    if (*p == '\n') *p = '\0';
                    save[i] = '\0';
                    return save;
                }
            }

            while (*p != '\0') {
                p++;
            }

            unused = recv(p, BUFLEN - (p - buf));
            if (unused == 0) {
                printf("end\n");
                exit(0);
            }
            while (unused > 0 && *p != '\n') {
                save[i++] = *p;
                *p = '\0';
                p++;
                unused--;
            }
            if (*p != '\n') {
                if (p < buf + BUFLEN - 1)
                    continue;
                else {
                    // too long
                    // todo
                    printf("too long\n");
                    exit(1);
                }
            }

            *p = save[i] = '\0';
            return save;
        } else {
            p = buf;
            while (*p == '\0') {
                p++;
            }
            pos = p;
            while (*p != '\n' && p < buf + BUFLEN) {
                save[i++] = *p;
                *p = '\0';
                p++;
            }
            if (p < buf + BUFLEN && *p == '\n') {
                *p = save[i] = '\0';
                return save;
            }
            if (p == buf + BUFLEN) {
                if (pos != buf) {
                    continue;
                } else {
                    // too long
                    // todo
                    printf("too long\n");
                    exit(1);
                }
            }
        }
    }
}

int main() {
    char* s;
    int i = 10, j = 0;

    while (i--) {
        s = read_line();
        printf("%d:   %s\n", j++, s);
        printbuf(buf, 16);
    }
}
