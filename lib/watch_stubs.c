#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>

#include <avahi-common/simple-watch.h>

CAMLprim value stub_avahi_simple_poll_new(value unit)
{
  CAMLparam1(unit);

  AvahiSimplePoll *sp;
  sp = avahi_simple_poll_new();
  if (sp)
    CAMLreturn((value)sp);

  caml_failwith("avahi_simple_poll_new returned NULL");
}

CAMLprim value stub_avahi_simple_poll_get(value sp)
{
  CAMLparam1(sp);
  const AvahiPoll *ap;
  ap = avahi_simple_poll_get((AvahiSimplePoll *)sp);
  if (ap)
    CAMLreturn((value)ap);

  caml_failwith("avahi_simple_poll_get returned NULL");
}
