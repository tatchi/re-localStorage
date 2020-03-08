type t;

let load: (~filename: string) => t;

let setItem: (string, string, t) => unit;

let getItem: (string, t) => option(string);

let persist: t => unit;

/* let getItem: (string, t) => option(string);
   let setItem: (string, string, t) => unit;
   let removeItem: (string, t) => unit; */