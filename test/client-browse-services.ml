let resolve_callback
    resolver
    interface protocol event
    name type_ domain host_name addr port txt flags =
  match event with
  | AVAHI_RESOLVER_FAILURE ->
    let error_str = Lookup.ServiceResolver.get_client resolver
                    |> Client.errno
                    |> Avahi.strerror in
    Printf.fprintf stderr
      "(Resolver) Failed to resolve service '%s' of type '%s' in domain '%s': %s\n"
      name type_ domain error_str
  | AVAHI_RESOLVER_FOUND ->
    Printf.fprintf stderr
      "Service '%s' of type '%s' in domain '%s':\n" name type_ domain;
    

