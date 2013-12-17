type watch
type timeout
type poll

module SimplePoll = struct
  type t
  external create : unit -> t = "stub_avahi_simple_poll_new"
  external get : t -> poll = "stub_avahi_simple_poll_get"
end
