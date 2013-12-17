let resolve_callback
    resolver
    interface protocol event
    name type_ domain host_name addr port txt flags =
  let open Lookup.ServiceResolver in
  match event with
  | AVAHI_RESOLVER_FAILURE ->
    let error_str = get_client resolver
                    |> Client.errno
                    |> Avahi.strerror in
    Printf.fprintf stderr
      "(Resolver) Failed to resolve service '%s' of type '%s' in domain '%s': %s\n"
      name type_ domain error_str
  | AVAHI_RESOLVER_FOUND ->
    Printf.fprintf stderr
      "Service '%s' of type '%s' in domain '%s':\n" name type_ domain

let browse_callback
    sb interface protocol event
    name type_ domain
    flags =
  let open Lookup.ServiceBrowser in
  match event with
  | AVAHI_BROWSER_FAILURE ->
    Printf.fprintf stderr
      "(Browser) %s\n" (get_client sb |> Client.errno |> Avahi.strerror)
  | AVAHI_BROWSER_NEW ->
    Printf.fprintf stderr
      "(Browser) NEW: service '%s' of type '%s' in domain '%s'\n"
      name type_ domain
  | AVAHI_BROWSER_REMOVE ->
    Printf.fprintf stderr
      "(Browser) REMOVE: service '%s' of type '%s' in domain '%s'\n"
      name type_ domain
  | AVAHI_BROWSER_ALL_FOR_NOW -> prerr_string "(Browser) ALL_FOR_NOW\n"
  | AVAHI_BROWSER_CACHE_EXHAUSTED -> prerr_string "(Browser) CACHE_EXHAUSTED\n"


let client_callback client state_int = match (Client.state_of_int state_int) with
  | AVAHI_CLIENT_FAILURE ->
    Printf.fprintf stderr "Server connection failure: %s\n"
      (client |> Client.errno |> Avahi.strerror)
  | _ -> ()

let _ =
  let simple_poll = Watch.SimplePoll.create () in
  let client = Client.create simple_poll 0 client_callback in
  let sb = Lookup.ServiceBrowser.create client
