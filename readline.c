//int recv(char* buf, int len);
//
//read_line(): "123"
//    recv(): "123\n45\n6789"
//read_line(): "45"
//read_line(): "6789abcde"
//    recv(): "abc"
//    recv(): "de\n"


char* read_line() {
    char* p, *pos;
    static char* buf = calloc(1024, 1);
    char save[1024+1];
    int i = 0;

    for (;;) {
	if (*(buf+1023) == '\0') {
	    int unused;

	    p = buf;
	    while (*p != '\0') {
		p++;
	    }

	    unused = recv(p, 1024-(p-buf));
	    while (unused > 0 && *p != '\n' && i < unused) {
		p++;
		save[i++] = *p; 
		*p = '\0';
	    }
	    if (*p != '\n') {
		if (p < buf+1023) 
		    continue;
		else {	
		    // too long
		    // todo
		    break;
		}
	    }

	    save[i] = '\0';    
	    return save;
	} else {
	    p = buf;
	    while (*p == '\0') {
		p++;
	    }
	    pos = p;
	    while (*p != '\n' && p < buf+1024) {
		save[i++] = *p;
		*p = '\0';
		p++;
	    }
	    if (*p == '\n') {
		save[i] = '\0';
		return save;
	    }
	    if (p == buf+1023) { 
		if (pos != buf) {
		    int len = 1024-(pos-buf);
		    memmove(buf, pos, len);
		    p = buf+len;
		    while (p < buf+1024) {
			*p = '\0';
		    }
		    continue;
		} else {
		    // too long
		    // todo
		    break;
		}
	    }
	}
    }

    return buf;
}
