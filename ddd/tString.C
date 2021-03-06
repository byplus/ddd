// This may look like C code, but it is really -*- C++ -*-
 
/*
 A test file for strings
*/

#include "strclass.h"
#include "assert.h"
#include "config.h"

#include <iostream>

// can't nicely echo assertions because they contain quotes

#define tassert(ex) {if (!(ex)) \
                     { std::cerr << "failed assertion at " << __LINE__ << "\n"; \
                       abort(); } }

  const string X0 = "I say: Hello";
  const string X = X0.from('H');

  const string Y0 = "the world";
  const string Y = Y0.after("the ");

  const string N = "123";
  string c;
  const char*  s = ",";

#if RUNTIME_REGEX
  regex  r = "e[a-z]*o";
#endif

void decltest()
{
  string x;
  std::cout << "an empty string:" << x << "\n";
  assert(x.OK());
  assert(x == "");
  assert(x.empty());

  string y = "Hello";
  std::cout << "A string initialized to Hello:" << y << "\n";
  assert(y.OK());
  assert(y == "Hello");

  if (y[y.length()-1] == 'o')
	y = y + '\n';
  assert(y == "Hello\n");
  y = "Hello";

  string a = y;
  std::cout << "A string initialized to previous string:" << a << "\n";
  assert(a.OK());
  assert(a == "Hello");
  assert(a == y);

  string b (a.at(1, 2));
  std::cout << "A string initialized to previous string.at(1, 2):" << b << "\n";
  assert(b.OK());
  assert(b == "el");

  char ch = '@';
  string z(ch); 
  std::cout << "A string initialized to @:" << z << "\n";
  assert(z.OK());
  assert(z == "@");

  string n = "20";
  std::cout << "A string initialized to 20:" << n << "\n";
  assert(n.OK());
  assert(n == "20");

  int i = atoi(n.chars());
  double f = atof(n.chars());
  std::cout << "n = " << n << " atoi(n) = " << i << " atof(n) = " << f << "\n";
  assert(i == 20);
  assert(f == 20);

  assert(X.OK());
  assert(Y.OK());
  assert(x.OK());
  assert(y.OK());
  assert(z.OK());
  assert(n.OK());

#if RUNTIME_REGEX
  assert(r.OK());
#endif
}

void cattest()
{
  string x = X;
  string y = Y;
  string z = x + y;
  std::cout << "z = x + y = " << z << "\n";
  assert(x.OK());
  assert(y.OK());
  assert(z.OK());
  assert(z == "Helloworld");

  x += y;
  std::cout << "x += y; x = " << x << "\n";
  assert(x.OK());
  assert(y.OK());
  assert(x == "Helloworld");

  y = Y;
  x = X;
  y.prepend(x);
  std::cout << "y.prepend(x); y = " << y << "\n";
  assert(y == "Helloworld");

#if 0
  y = Y;
  x = X;
  cat(x, y, x, x);
  std::cout << "cat(x, y, x, x); x = " << x << "\n";
  assert(x == "HelloworldHello");

  y = Y;
  x = X;
  cat(y, x, x, x);
  std::cout << "cat(y, x, x, x); x = " << x << "\n";
  assert(x == "worldHelloHello");
#endif

  x = X;
  y = Y;
  z = x + s + ' ' + y.at("w") + y.after("w") + ".";
  std::cout << "z = x + s +  + y.at(w) + y.after(w) + . = " << z << "\n";
  assert(z.OK());
  assert(z == "Hello, world.");

}

void comparetest()
{  
  string x = X;
  string y = Y;
  string n = N;
  string z = x + y;

  assert(x != y);
  assert(x == "Hello");
  assert(x != z.at(0, 4));
  assert (x < y);
  assert(!(x >= z.at(0, 6)));
  assert(x.contains("He"));
  assert (z.contains(x));

#if RUNTIME_REGEX
  assert(x.contains(r));
  assert(!(x.matches(r)));
#endif

#if RUNTIME_REGEX
  assert(x.matches(rxalpha));
  assert(!(n.matches(rxalpha)));
  assert(n.matches(rxint));
  assert(n.matches(rxdouble));
#endif

  assert(x.index("lo") == 3);
  assert(x.index("l", 2) == 2);
  assert(x.index("l", -1) == 3);

#if RUNTIME_REGEX
  assert(x.index(r)  == 1);
  assert(x.index(r, -2) == 1);
#endif

  assert(x.contains("el", 1));
  assert(x.contains("el"));

  assert(common_prefix(x, "Help") == "Hel");
  assert(common_suffix(x, "to") == "o");

  assert(fcompare(x, "hELlo") == 0);
  assert(fcompare(x, "hElp") < 0);
}

void substrtest()
{
  string x = X;

  char ch = x[0];
  std::cout << "ch = x[0] = " << ch << "\n";
  assert(ch == 'H');

  string z = x.at(2, 3);
  std::cout << "z = x.at(2, 3) = " << z << "\n";
  assert(z.OK());
  assert(z == "llo");

  x.at(2, 2) = "r";
  std::cout << "x.at(2, 2) = r; x = " << x << "\n";
  assert(x.OK());
  assert(x.at(2,2).OK());
  assert(x == "Hero");

  x = X;
  x.at(0, 1) = "j";
  std::cout << "x.at(0, 1) = j; x = " << x << "\n";
  assert(x.OK());
  assert(x == "jello");

  x = X;
  x.at("He") = "je";
  std::cout << "x.at(He) = je; x = " << x << "\n";
  assert(x.OK());
  assert(x == "jello");

  x = X;
  x.at("l", -1) = "i";
  std::cout << "x.at(l, -1) = i; x = " << x << "\n";
  assert(x.OK());
  assert(x == "Helio");
  
#if RUNTIME_REGEX
  x = X;
  z = x.at(r);
  std::cout << "z = x.at(r) = " << z << "\n";
  assert(z.OK());
  assert(z == "ello");
#endif

  x = X;
  z = x.before("o");
  std::cout << "z = x.before(o) = " << z << "\n";
  assert(z.OK());
  assert(z == "Hell");

  x = X;
  x = x.before("o");
  std::cout << "x = x.before(o) = " << x << "\n";
  assert(x.OK());
  assert(x == "Hell");

  x = X;
  x = x.from("e");
  std::cout << "x = x.from(e) = " << x << "\n";
  assert(x.OK());
  assert(x == "ello");

  x = X;
  x.before("ll") = "Bri";
  std::cout << "x.before(ll) = Bri; x = " << x << "\n";
  assert(x.OK());
  assert(x == "Brillo");

  x = X;
  z = x.before(2);
  std::cout << "z = x.before(2) = " << z << "\n";
  assert(z.OK());
  assert(z == "He");

  x = X;
  z = x.after("Hel");
  std::cout << "z = x.after(Hel) = " << z << "\n";
  assert(z.OK());
  assert(z == "lo");

  x = X;
  x.after("Hel") = "p";  
  std::cout << "x.after(Hel) = p; x = " << x << "\n";
  assert(x.OK());
  assert(x == "Help");

  x = X;
  z = x.after(3);
  std::cout << "z = x.after(3) = " << z << "\n";
  assert(z.OK());
  assert(z == "o");

#if RUNTIME_REGEX
  z = "  a bc";
  z  = z.after(rxwhite);
  std::cout << "z =   a bc; z = z.after(rxwhite); z =" << z << "\n";
  assert(z.OK());
  assert(z == "a bc");
#endif
}


void utiltest()
{
  string x = X;
  int matches = x.gsub("l", "ll");
  std::cout << "x.gsub(l, ll); x = " << x << "\n";
  assert(x.OK());
  assert(matches == 2);
  assert(x == "Hellllo");

#if RUNTIME_REGEX
  x = X;
  assert(x.OK());
  matches = x.gsub(r, "ello should have been replaced by this string");
  assert(x.OK());
  std::cout << "x.gsub(r, ...); x = " << x << "\n";
  assert(x.OK());
  assert(matches == 1);
  assert(x == "Hello should have been replaced by this string");
#endif

#if RUNTIME_REGEX
  matches = x.gsub(rxwhite, "#");
  std::cout << "x.gsub(rxwhite, #); x = " << x << "\n";
  assert(matches == 7);
  assert(x.OK());
#endif

  string z = X + Y;
  z.del("loworl");
  std::cout << "z = x+y; z.del(loworl); z = " << z << "\n";
  assert(z.OK());
  assert(z == "Held");

  x = X;
  z = reverse(x);
  std::cout << "reverse(x) = " << z << "\n";
  assert(z.OK());
  assert(z == "olleH");

  x.reverse();
  std::cout << "x.reverse() = " << x << "\n";
  assert(x.OK());
  assert(x == z);

  x = X;
  z = upcase(x);
  std::cout << "upcase(x) = " << z << "\n";
  assert(z.OK());
  assert(z == "HELLO");

  z = downcase(x);
  std::cout << "downcase(x) = " << z << "\n";
  assert(z.OK());
  assert(z == "hello");

  z = capitalize(x);
  std::cout << "capitalize(x) = " << z << "\n";
  assert(z.OK());
  assert(z == "Hello");

  /* Let's see how apostrophe is handled. */
  z = "he asked:'this is nathan's book?'. 'no, it's not',i said.";
  std::cout << "capitalize(z) = " << capitalize (z) << "\n";
  
  z = replicate('*', 10);
  std::cout << "z = replicate(*, 10) = " << z << "\n";
  assert(z.OK());
  assert(z == "**********");
  assert(z.length() == 10);
}

void splittest()
{
#if RUNTIME_REGEX
  string z = "This string\thas\nfive words";
  std::cout << "z = " << z << "\n";
  string w[10];
  int nw = split(z, w, 10, rxwhite);
  assert(nw == 5);
  std::cout << "from split(z, rxwhite, w, 10), n words = " << nw << ":\n";
  for (int i = 0; i < nw; ++i)
  {
    assert(w[i].OK());
    std::cout << w[i] << "\n";
  }
  assert(w[0] == "This");
  assert(w[1] == "string");
  assert(w[2] == "has");
  assert(w[3] == "five");
  assert(w[4] == "words");
  assert(w[5] == (char *)0);

  z = join(w, nw, "/");
  std::cout << "z = join(w, nw, /); z =" << z << "\n";
  assert(z.OK());
  assert(z == "This/string/has/five/words");
#endif
}


void iotest()
{
  string z;
  std::cout << "enter a word:";
  std::cin >> z;
  std::cout << "word =" << z << " ";
  std::cout << "length = " << z.length() << "\n";
}

void identitytest(string a, string b)
{
  string x = a;
  string y = b;
  x += b;
  y.prepend(a);
  assert((a + b) == x);
  assert((a + b) == y);
  assert(x == y);
  assert(x.after(a) == b);
  assert(x.before(b, -1) == a);
  assert(x.from(a) == x);
  assert(x.through(b, -1) == x);
  assert(x.at(a) == a);
  assert(x.at(b) == b);

  assert(reverse(x) == reverse(b) + reverse(a));
  
  assert((a + b + a) == (a + (b + a)));

  x.del(b, -1);
  assert(x == a);

  y.before(b, -1) = b;
  assert(y == (b + b));
  y.at(b) = a;
  assert(y == (a + b));

  x = a + reverse(a);
  for (int i = 0; i < 7; ++i)
  {
    y = x;
    x += x;
    assert(x.OK());
    assert(x == reverse(x));
    assert(x.index(y) == 0);
    assert(x.index(y, -1) == int(x.length() / 2));
  }
}

void freqtest()
{
  string x = "Hello World";
  subString y = x.at(0,5);
  assert(x.freq('l') == 3);	// char
  assert(x.freq("lo") == 1);	// char*
  assert(x.freq(x) == 1);	// string
  assert(x.freq(y) == 1);	// Substring
}

int main()
{
  decltest();
  cattest();
  comparetest();
  substrtest();
  utiltest();
  splittest();
  freqtest();
  identitytest(X, X);
  identitytest(X, Y);
  identitytest(X+Y+N+X+Y+N, "A string that will be used in identitytest but is otherwise just another useless string.");
  iotest();
  std::cout << "\nEnd of test\n";
  return 0;
}
