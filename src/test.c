typedef unsigned char   uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;

void outc(char c);
void outhex(uint8_t i);
void outhex32(uint32_t i);
void outnl();
void outshort(short i);
void outlong(long i);
void outstr(char *c);
void pass();
void fail();

#define S1 12345
#define S2 1000

#define L1 1234567890L
#define L2 10000L

#ifdef LINUX
int main() {
#else
int program() {
#endif
   outshort(0);
   outnl();
   outshort(12345);
   outnl();
   outshort(-12345);
   outnl();
   outlong(0L);
   outnl();
   outlong(1234567890L);
   outnl();
   outlong(-1234567890L);
   outnl();

   volatile short s1 = S1;
   volatile short s2 = S2;
   volatile short sr;

   outstr("Signed short\r\n");

   sr = s1 / s2;
   outshort(s1);
   outc('/');
   outshort(s2);
   outc('=');
   outshort(sr);
   if (sr == (S1/S2)) {
      pass();
   } else {
      fail();
   }

   sr = s1 % s2;
   outshort(s1);
   outc('%');
   outshort(s2);
   outc('=');
   outshort(sr);
   if (sr == (S1%S2)) {
      pass();
   } else {
      fail();
   }

   volatile unsigned short us1 = S1;
   volatile unsigned short us2 = S2;
   volatile unsigned short usr;

   outstr("Unsigned short\r\n");

   usr = us1 / us2;
   outshort(us1);
   outc('/');
   outshort(us2);
   outc('=');
   outshort(usr);
   if (usr == (S1/S2)) {
      pass();
   } else {
      fail();
   }

   usr = us1 % us2;
   outshort(us1);
   outc('%');
   outshort(us2);
   outc('=');
   outshort(usr);
   if (usr == (S1%S2)) {
      pass();
   } else {
      fail();
   }

   volatile long l1 = L1;
   volatile long l2 = L2;
   volatile long lr;

   outstr("signed long\r\n");

   lr = l1 / l2;
   outlong(l1);
   outc('/');
   outlong(l2);
   outc('=');
   outlong(lr);
   if (lr == (L1/L2)) {
      pass();
   } else {
      fail();
   }

   lr = l1 % l2;
   outlong(l1);
   outc('%');
   outlong(l2);
   outc('=');
   outlong(lr);
   if (lr == (L1%L2)) {
      pass();
   } else {
      fail();
   }

   volatile unsigned long ul1 = L1;
   volatile unsigned long ul2 = L2;
   volatile unsigned long ulr;

   outstr("unsigned long\r\n");

   ulr = ul1 / ul2;
   outlong(ul1);
   outc('/');
   outlong(ul2);
   outc('=');
   outlong(ulr);
   if (ulr == (L1/L2)) {
      pass();
   } else {
      fail();
   }

   ulr = ul1 % ul2;
   outlong(ul1);
   outc('%');
   outlong(ul2);
   outc('=');
   outlong(ulr);
   if (ulr == (L1%L2)) {
      pass();
   } else {
      fail();
   }
}

 void pass() {
   outstr(" pass\r\n");
}

void fail() {
   outstr(" fail\r\n");
}

// Use constants to avoid division
static const short ps[] = {
   10000,
   1000,
   100,
   10,
   1,
   0};

void outshort(short i) {
   if (i < 0) {
      outc('-');
      i = -i;
   }
   const short *pp = &ps[0];
   while (*pp) {
      char digit = '0';
      while (i >= *pp) {
         i = i - *pp;
         digit++;
      }
      outc(digit);
      pp++;
   };
}

// Use constants to avoid division
static const long pl[]
= {1000000000L,
   100000000L,
   10000000L,
   1000000L,
   100000L,
   10000L,
   1000L,
   100L,
   10L,
   1L,
   0L};

void outhex(uint8_t i) {
   i &= 15;
   if (i > 9) {
      outc(i + ('A' - 10));
   } else {
      outc(i + '0');
   }
}

void outhex32(uint32_t i) {
   for (uint8_t d = 0; d < 8; d++) {
      // Note: this uses ASHC which is a signed shift
      outhex(i >> 28);
      i <<= 4;
   }
}

void outlong(long i) {
   if (i < 0) {
      outc('-');
      i = -i;
   }
   const uint32_t *pp = &pl[0];
   while (*pp) {
      char digit = '0';
      while (i >= *pp) {
         i = i - *pp;
         digit++;
      }
      outc(digit);
      pp++;
   };
}

void outstr(char *c) {
   while (*c) {
      outc(*c++);
   }
}

void outnl() {
   outc(10);
   outc(13);
}

#ifdef LINUX
void outc(char c) {
   putchar(c);
}
#else
void outc(char c) {
   asm("mov %0, r0" :  : "r" (c) : "r0");
   asm("emt 4");
}
#endif
