//FORBIDDEN cout
//FORBIDDEN cerr
//FORBIDDEN printf
//FORBIDDEN puts
//FORBIDDEN putchar
//FORBIDDEN putc
#include "util.h"
#include "c.h"

int cnt = 0; // utilisez cette variable globale

void f0() noexcept {
   enter("f0");
// AJOUTEZ VOTRE CODE ICI ...
   static C a = C(++cnt);
   C c = C(++cnt);
// ... FIN DE VOTRE CODE
   leave("f0");
}

C* f1() {
   enter("f1");
   C* p;
// AJOUTEZ VOTRE CODE ICI ...
   p = new C(++cnt);
// ... FIN DE VOTRE CODE
   leave("f1");
   return p;
}

C* f2() {
   enter("f2");
   C* p;
// AJOUTEZ VOTRE CODE ICI ...
   p = new C[2]{++cnt, ++cnt};
// ... FIN DE VOTRE CODE
   leave("f2");
   return p;
}

void f3(C* p) noexcept {
   enter("f3");
// AJOUTEZ VOTRE CODE ICI ..
   new(p) C(++cnt);
// ... FIN DE VOTRE CODE
   leave("f3");
}

void f4(C* p, size_t n) noexcept {
   enter("f4");
// AJOUTEZ VOTRE CODE ICI ...
   for(size_t i = 0; i < n; ++i)
      new(p+i) C(++cnt);
// ... FIN DE VOTRE CODE
   leave("f4");
}

int main() {
   enter("main");
// AJOUTEZ VOTRE CODE ICI ...
   const size_t size_1 = 2, size_2 = 1;

   C a = C(++cnt);
   f0();
   f0();
   C* b = f1();
   C* c = f2();
   C* d = (C*) ::operator new(sizeof(C));

   f3(d);

   delete[](c);
   c = nullptr;

   delete(b);
   b = nullptr;

   C* e = (C*) ::operator new(sizeof(C) * size_1, std::nothrow);

   f4(e, size_1);

   delete(d);
   d = nullptr;

   C* f = (C*) ::operator new(sizeof(C) * size_2, std::nothrow);

   f4(f, size_2);

   for(size_t i = 0; i < size_1; ++i)
      (e+i) -> ~C();

   ::operator delete(e, sizeof(C) * size_1);

   for(size_t i = 0; i < size_2; ++i)
      (f+i) -> ~C();

   ::operator delete(f, sizeof(C) * size_2);

// ... FIN DE VOTRE CODE
   leave("main");
}
