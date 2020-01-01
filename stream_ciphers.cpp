/*
 * proj2.cpp
 *
 *  Created on: Nov. 5, 2019
 *      Author: Raksha
 */
#include<iostream>
#include<cmath>
char *encode(char *plaintext, unsigned long key);
char *decode(char *ciphertext, unsigned long key);
#ifndef MARMOSET_TESTING
int main() {
	char str1[]{ "Hello world!" };
	char str0[]{ "study" };
	std::cout << "\"" << str0 << "\"" << std::endl;
	char *ciphertext{ encode( str0, 3408 ) };
	std::cout<< "\"" << ciphertext << "\"" << std::endl;
	char *plaintext{ decode( ciphertext, 3408 ) };
	std::cout << "\"" << plaintext << "\"" << std::endl;
	delete[] plaintext;
	plaintext= nullptr;
	delete[] ciphertext;
	ciphertext= nullptr;
	std::cout << "\"" << str1<< "\"" << std::endl;
	ciphertext = encode( str1, 51323 );
	std::cout << "\"" << ciphertext << "\"" << std::endl;
	plaintext = decode( ciphertext, 51323 );
	std::cout << "\"" << plaintext << "\"" << std::endl;
	delete[] plaintext;
	plaintext= nullptr;
	delete[] ciphertext;
	ciphertext= nullptr;
	return 0;
}
#endif

char* encode(char *plaintext, unsigned long key) {
	unsigned char s[256];
	int k = 0;
	int i = 0;
	int j = 0;

	unsigned char t { };
	int r { };
	unsigned char R { };

	for (int n = 0; n <= 255; n++) {
		s[n] = n;
	}

	std::size_t size;
	for (size = 0; plaintext[size] != '\0'; size++) {
	}

	std::size_t sizer = size;
	if (size % 4 != 0)
		sizer = sizer + (4 - (size % 4));

	unsigned char *cipher { nullptr };
	cipher = new unsigned char[sizer];

	for (int n = 0; n < sizer; n++) {
		if (n >= size) {
			cipher[n] = '\0';
		} else {
			cipher[n] = plaintext[n];
		}
	}

	for (int n = 0; n < 256; n++) {
		k = i % 64;
		j = (j + s[i] + ((key & (1 << k)) >> k)) % 256;
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		i = (i + 1) % 256;
	}

	for (int n = 0; n < sizer; n++) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		r = (s[i] + s[j]) % 256;
		R = s[r];
		cipher[n] = cipher[n] ^ R;
	}

	char *ciph { nullptr };
	ciph = new char[5 * (sizer / 4) + 1];

	for (int n = 0; n < (sizer / 4); n++) {
		unsigned int c {0};

		c = (static_cast<unsigned int>( cipher[4 * n] ) << 24) + (static_cast<unsigned int>( cipher[4 * n + 1] ) << 16)
				+ (static_cast<unsigned int>( cipher[4 * n + 2] ) << 8) + (static_cast<unsigned int>( cipher[4 * n + 3] ));


		ciph[5 * n + 4] = (c % 85) + 33;
		c = c / 85;

		ciph[5 * n + 3] = (c % 85) + 33;
		c = c / 85;

		ciph[5 * n + 2] = (c % 85) + 33;
		c = c / 85;

		ciph[5 * n + 1] = (c % 85) + 33;
		c = c / 85;

		ciph[5 * n] = (c % 85) + 33;
	}

	ciph[5 * (sizer / 4)] = '\0';

	delete[] cipher;
	cipher = nullptr;
	return ciph;

}
char*decode(char *ciphertext, unsigned long key) {
	int k = 0;
	int i = 0;
	int j = 0;

	unsigned char t { };
	int r { };
	unsigned char R { };

	unsigned char s[256];

	for (int n = 0; n <= 255; n++) {
		s[n] = n;
	}
	std::size_t size;

	for (size = 0; ciphertext[size] != '\0'; size++) {}

	std::size_t sizer=4*(size/5);
	char *plain{nullptr};
	plain=new char[sizer+1];

	for (int n=0; n<(sizer)/4; n++)
	{
		unsigned int c{};

		for (int z=0;z<=4;z++)
		{c = (static_cast<unsigned int>(ciphertext[5*n+z])-33)*pow(85,4-z) + c;
		}

	plain[4*n]=c>>24;
	c=c<<8;
	plain[4*n+1]=c>>24;
	c=c<<8;
	plain[4*n+2]=c>>24;
	c=c<<8;
	plain[4*n+3]=c>>24;
	}

	for (int n = 0; n < 256; n++) {
			k = i % 64;
			j = (j + s[i] + ((key & (1 << k)) >> k)) % 256;
			t = s[i];
			s[i] = s[j];
			s[j] = t;
			i = (i + 1) % 256;
		}


		for (int n = 0; n < sizer; n++) {
			i = (i + 1) % 256;
			j = (j + s[i]) % 256;
			t = s[i];
			s[i] = s[j];
			s[j] = t;
			r = (s[i] + s[j]) % 256;
			R = s[r];
			plain[n] = plain[n] ^ R;
		}
		plain[sizer]='\0';

return plain;
}






