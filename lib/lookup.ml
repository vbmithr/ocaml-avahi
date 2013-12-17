module ServiceBrowser = struct
  type t
  type event =
    | AVAHI_BROWSER_NEW
    | AVAHI_BROWSER_REMOVE
    | AVAHI_BROWSER_CACHE_EXHAUSTED
    | AVAHI_BROWSER_ALL_FOR_NOW
    | AVAHI_BROWSER_FAILURE
  type callback = t -> event -> string -> string -> string -> int -> unit
  external create : Client.t -> int -> int -> callback -> t = "stub_avahi_service_browser_new"
  external get_client : t -> Client.t = "stub_avahi_service_browser_get_client"
end

module ServiceResolver = struct
  type t
  type event =
    | AVAHI_RESOLVER_FOUND
    | AVAHI_RESOLVER_FAILURE
  type callback = t -> int -> int -> event -> string -> string -> string -> string -> string -> int -> Strlst.t -> int -> unit
  external create : Client.t -> int -> int -> string -> string -> string -> int -> int -> callback = "stub_avahi_service_resolver_new_byte" "stub_avahi_service_resolver_new_native"
  external get_client : t -> Client.t = "stub_avahi_service_resolver_get_client"
end
