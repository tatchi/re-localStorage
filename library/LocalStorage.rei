type t;

let create: string => t;

let getItem: (string, t) => Lwt.t(option(string));
let setItem: (string, string, t) => Lwt.t(unit);
let removeItem: (string, t) => Lwt.t(unit);