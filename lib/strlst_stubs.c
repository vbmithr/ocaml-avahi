#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/callback.h>

#include <avahi-common/strlst.h>

CAMLprim value stub_avahi_string_list_get_next(value l)
{
  CAMLparam1(l);
  CAMLlocal1(r);
  AvahiStringList *next;
  next = avahi_string_list_get_next((AvahiStringList *)l);
  if (next == NULL)
    {
      r = caml_alloc(1, 0);
      Store_field(r, 0, (value)next);
      CAMLreturn(r);
    }
  else CAMLreturn(Val_int(0));
}

CAMLprim value stub_avahi_string_list_get_text(value l)
{
  CAMLparam1(l);
  CAMLreturn(caml_copy_string((const char *)avahi_string_list_get_text((AvahiStringList *)l)));
}

CAMLprim value stub_avahi_string_list_get_service_cookie(value l)
{
  CAMLparam1(l);
  CAMLreturn(caml_copy_int32(avahi_string_list_get_service_cookie((AvahiStringList *)l)));
}
