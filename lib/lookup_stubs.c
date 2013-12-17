#include <stdlib.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/callback.h>

#include <avahi-client/lookup.h>

void sb_callback(AvahiServiceBrowser *b,
	       AvahiIfIndex interface,
	       AvahiProtocol protocol,
	       AvahiBrowserEvent event,
	       const char *name,
	       const char *type,
	       const char *domain,
	       AvahiLookupResultFlags flags,
	       void *userdata)
{
  value args[] =
    { (value)b, (value)interface, (value)protocol, Val_int(event), caml_copy_string(name),
      caml_copy_string(type), caml_copy_string(domain), Val_int(flags) };

  caml_callbackN((value)userdata, 8, args);
}

CAMLprim value stub_avahi_service_browser_new_native(value client, value interface,
					      value protocol, value srvtype,
					      value domain, value flags, value callback)
{
  CAMLparam5(client, interface, protocol, srvtype, domain);
  CAMLxparam2(flags, callback);

  AvahiServiceBrowser *asb;

  char *c_domain = NULL;
  if (Is_block(domain))
    {
      size_t c_domain_size = caml_string_length(Field(domain, 0)) + 1;
      c_domain = malloc(c_domain_size);
      strncpy(c_domain, String_val(Field(domain, 0)), c_domain_size);
    }

  asb = avahi_service_browser_new(
				  (AvahiClient *)client,
				  Int_val(interface),
				  Int_val(protocol),
				  String_val(srvtype),
				  (const char *)domain,
				  Int_val(flags),
				  sb_callback,
				  (void*)callback
				  );

  if (asb)
    CAMLreturn((value)asb);

  caml_failwith("avahi_service_browser_new returned NULL");
}

CAMLprim value stub_avahi_service_browser_new_byte(value *argv, int argn)
{
  return stub_avahi_service_browser_new_native(argv[0], argv[1], argv[2],
					       argv[3], argv[4], argv[5],
					       argv[6]);
}

CAMLprim value stub_avahi_service_browser_get_client(value sb)
{
  CAMLparam1(sb);
  AvahiClient *c;
  c = avahi_service_browser_get_client((AvahiServiceBrowser *)sb);
  if (c)
    CAMLreturn((value)c);
  else
    caml_failwith("avahi_service_browser_get_client returned NULL");
}


void sr_callback(AvahiServiceResolver *r,
		 AvahiIfIndex interface,
		 AvahiProtocol protocol,
		 AvahiResolverEvent event,
		 const char *name,
		 const char *type,
		 const char *domain,
		 const char *host_name,
		 const AvahiAddress *a,
		 uint16_t port,
		 AvahiStringList *txt,
		 AvahiLookupResultFlags flags,
		 void *userdata)
{
  char a_str[AVAHI_ADDRESS_STR_MAX] = {0};
  avahi_address_snprint(a_str, sizeof(a_str), a);
  value args[] = {(value)r, Val_int(interface), Val_int(protocol),
		  Val_int(event), caml_copy_string(name), caml_copy_string(type),
		  caml_copy_string(domain), caml_copy_string(host_name),
		  caml_copy_string(a_str), Val_int(port), (value)txt,
		  Val_int(flags)};
  caml_callbackN((value)userdata, 12, args);
}

CAMLprim value stub_avahi_service_resolver_new_native(value client, value interface,
						      value protocol, value name,
						      value type, value domain,
						      value aprotocol, value flags,
						      value callback
						      )
{
  CAMLparam5(client, interface, protocol, name, type);
  CAMLxparam4(domain, aprotocol, flags, callback);

  AvahiServiceResolver *asr;
  asr = avahi_service_resolver_new((AvahiClient *)client,
				   Int_val(interface),
				   Int_val(protocol),
				   String_val(name),
				   String_val(type),
				   String_val(domain),
				   Int_val(aprotocol),
				   Int_val(flags),
				   sr_callback,
				   (void *)callback
				   );
  if (asr)
    CAMLreturn((value)asr);

  caml_failwith("avahi_service_resolver_new returned NULL");
}

CAMLprim value stub_avahi_service_resolver_new_byte(value *argv, int argn)
{
  return stub_avahi_service_resolver_new_native(argv[0], argv[1], argv[2],
						argv[3], argv[4], argv[5],
						argv[6], argv[7], argv[8]);
}

CAMLprim value stub_avahi_service_resolver_get_client(value sr)
{
  CAMLparam1(sr);
  AvahiClient *c;
  c = avahi_service_resolver_get_client((AvahiServiceResolver *)sr);
  if (c)
    CAMLreturn((value)c);
  else
    caml_failwith("avahi_service_resolver_get_client returned NULL");
}
