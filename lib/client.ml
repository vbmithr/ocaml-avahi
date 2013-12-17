type t

type callback = t -> int -> unit

external create : Watch.poll -> int -> callback -> t = "stub_avahi_client_new"
external free : t -> unit = "stub_avahi_client_free"

external get_version_string : t -> string = "stub_avahi_get_version_string"
external errno : t -> int = "stub_avahi_client_errno"
