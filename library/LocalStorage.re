open Lwt.Infix;

type t = {
  filename: string,
  data: Hashtbl.t(string, string),
};
let readFromFile = (~filename) => {
  switch (Pervasives.open_in(filename)) {
  | input =>
    let hashtbl: Hashtbl.t(string, string) = Pervasives.input_value(input);
    Pervasives.close_in(input);
    hashtbl;
  | exception (Sys_error(message)) => Hashtbl.create(0)
  };
};

let writeToFile = (~filename, data) => {
  let output = Pervasives.open_out(filename);
  Pervasives.output_value(output, data);
  Pervasives.close_out(output);
};

let load = (~filename) => {
  {filename, data: readFromFile(~filename)};
};

let setItem = (key: string, value: string, storage: t) => {
  Hashtbl.replace(storage.data, key, value);
};

let getItem = (key: string, storage: t): option(string) => {
  switch (Hashtbl.find(storage.data, key)) {
  | value => Some(value)
  | exception Not_found => None
  };
};

let persist = storage =>
  writeToFile(~filename=storage.filename, storage.data);