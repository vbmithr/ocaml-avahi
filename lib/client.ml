type t

type state =
  | AVAHI_CLIENT_S_REGISTERING
  | AVAHI_CLIENT_S_RUNNING
  | AVAHI_CLIENT_S_COLLISION
  | AVAHI_CLIENT_FAILURE
  | AVAHI_CLIENT_CONNECTING

let int_of_state = function
  | AVAHI_CLIENT_S_REGISTERING -> 1
  | AVAHI_CLIENT_S_RUNNING -> 2
  | AVAHI_CLIENT_S_COLLISION -> 3
  | AVAHI_CLIENT_FAILURE -> 100
  | AVAHI_CLIENT_CONNECTING -> 101

let state_of_int = function
  | 1 -> AVAHI_CLIENT_S_REGISTERING
  | 2 -> AVAHI_CLIENT_S_RUNNING
  | 3 -> AVAHI_CLIENT_S_COLLISION
  | 100 -> AVAHI_CLIENT_FAILURE
  | 101 -> AVAHI_CLIENT_CONNECTING
  | _ -> raise (Invalid_argument "Client.state_of_int")

type callback = t -> int -> unit

external create : Watch.poll -> int -> callback -> t = "stub_avahi_client_new"
external free : t -> unit = "stub_avahi_client_free"

external get_version_string : t -> string = "stub_avahi_get_version_string"
external errno : t -> int = "stub_avahi_client_errno"
