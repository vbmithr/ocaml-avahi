#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/callback.h>

#include <avahi-common/error.h>
#include <avahi-client/client.h>

void client_callback(AvahiClient *s, AvahiClientState state, void *userdata)
{
  caml_callback2((value)userdata, (value)s, (value)state);
}

CAMLprim value stub_avahi_client_new(value poll, value flags, value callback)
{
  CAMLparam3(poll, flags, callback);

  int ret;
  AvahiClient *ac;
  ac = avahi_client_new((const AvahiPoll *)poll,
			(AvahiClientFlags) Int_val(flags),
			client_callback,
			(void *)callback,
			&ret
			);
  if (ac)
    CAMLreturn((value)ac);

  caml_failwith(avahi_strerror(ret));
}

CAMLprim value stub_avahi_client_free(value client)
{
  CAMLparam1(client);
  avahi_client_free((AvahiClient *)client);
  CAMLreturn(Val_unit);
}

CAMLprim value stub_avahi_client_get_version_string(value client)
{
  CAMLparam1(client);
  CAMLreturn(caml_copy_string(avahi_client_get_version_string((AvahiClient *)client)));
}

CAMLprim value stub_avahi_client_errno(value client)
{
  CAMLparam1(client);
  CAMLreturn(Val_int(avahi_client_errno((AvahiClient *)client)));
}
