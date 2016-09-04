char *itoa(int n, char *str, int radix) {
	static char digit[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	char*p = str;
	char *head = str;

	if(!p || radix<2 || radix>36) {
		return p;
	}
	if (radix != 10 && n< 0) {
		return p;
	}

	if (n == 0) {
		*p++ = '0';
		*p = 0;
		return p;
	}
	if (radix == 10 && n < 0) {
		*p++ = '-';
		n = -n;
	}

	while(n) {
		*p++ = digit[n%radix];
		n /= radix;
	}
	*p = 0;

	for (--p; head < p; ++head, --p) {
		char temp = *head;
		*head = *p;
		*p = temp;
	}
	return str;
}

int strcmp(const char *src, const char * dst) {
	for (; *src == *dst; src++, dst++ ) {
		if (!*src) {
			return 0;
		}
	}
	return *src > *dst ? 1: -1;
}

char *strcpy(char *dest, const char *src) {
	char *ret = dest;
	
	for (;*src;) {
		*dest++= *src++;
	}
	*dest = '\0';
	
	return ret;
}

unsigned strlen(const char *str) {
	const char *temp = str;
	
	for (;*temp; temp++);

	return temp - str;
}

