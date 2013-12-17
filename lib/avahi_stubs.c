#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>

#include <avahi-common/error.h>

CAMLprim value stub_avahi_strerror(value errno)
{
  CAMLparam1(errno);
  CAMLreturn(caml_copy_string(avahi_strerror(Int_val(errno))));
}
