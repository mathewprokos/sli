#include <stdio.h>
#include "scheme.h"
#include "scheme-private.h"
#include "dynload.h"

#define car(p)           ((p)->_object._cons._car)
#define cdr(p)           ((p)->_object._cons._cdr)
#define caar(p)          car(car(p))
#define cadr(p)          car(cdr(p))
#define cdar(p)          cdr(car(p))
#define cddr(p)          cdr(cdr(p))
#define cadar(p)         car(cdr(car(p)))
#define caddr(p)         car(cdr(cdr(p)))
#define cdaar(p)         cdr(car(car(p)))
#define cadaar(p)        car(cdr(car(car(p))))
#define cadddr(p)        car(cdr(cdr(cdr(p))))
#define cddddr(p)        cdr(cdr(cdr(cdr(p))))

pointer mult(struct scheme *sc, pointer args) {
   int v1=0;
   int v2=0;
   if(args!=sc->NIL) {
      if(is_number((pointer)car(args))) {
         v1=ivalue((pointer)car(args));
         if(is_number((pointer)cadr(args))) {
            v2=ivalue(cadr(args));
            }
         return mk_real(sc,v1*v2);
      }
   }
   return sc->NIL;
}

int main() {
   FILE *init_scm;
   struct scheme sc;

   init_scm = fopen("init.scm","r");

   if(init_scm == 0) {
      printf("Unable to open init.scm\n");
      return 1;
   }

   scheme_init(&sc);
   scheme_set_output_port_file(&sc, stdout);
   scheme_set_input_port_file(&sc, stdin);
   scheme_define(&sc,sc.global_env,mk_symbol(&sc,"load-extension"),mk_foreign_func(&sc, scm_load_ext));
   scheme_define(&sc,
                 sc.global_env,
                 mk_symbol(&sc,"mult"),
                 mk_foreign_func(&sc, mult));
   scheme_load_file(&sc, init_scm);
   scheme_load_named_file(&sc,stdin,0);
   scheme_deinit(&sc);

   return 0;
}
