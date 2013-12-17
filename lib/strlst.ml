type t
external next : t -> t option = "stub_avahi_string_list_get_next"
external text : t -> string = "stub_avahi_string_list_get_text"

let rec to_list sl = match (next sl) with
  | Some n -> (text n) :: to_list n
  | None -> []

external get_service_cookie : t -> int32 = "stub_avahi_string_list_get_service_cookie"
