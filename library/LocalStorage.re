open Lwt.Infix;

type t = {filename: string};

let create = (filename: string) => {
  {filename: filename ++ ".bin"};
};

let readFromFile = (filename: string): Lwt.t(Hashtbl.t(string, string)) => {
  try%lwt(
    Lwt_io.open_file(~mode=Input, ~flags=[O_RDONLY, O_NONBLOCK], filename)
    >>= Lwt_io.read_value
  ) {
  | _ => Lwt.return(Hashtbl.create(0))
  };
};

let writeToFile = (filename: string, content) => {
  Lwt_io.open_file(
    ~mode=Output,
    ~flags=[O_WRONLY, O_NONBLOCK, O_CREAT],
    filename,
  )
  >>= (
    file =>
      Lwt.finalize(
        _ => Lwt_io.write_value(file, content),
        _ => Lwt_io.close(file),
      )
  );
};

let setItem = (key: string, value: string, {filename}) => {
  readFromFile(filename)
  >>= (
    hashtbl => {
      Hashtbl.replace(hashtbl, key, value);
      writeToFile(filename, hashtbl);
    }
  );
};
let getItem = (key, {filename}) => {
  readFromFile(filename)
  >|= (
    hashtbl => {
      switch (Hashtbl.find(hashtbl, key)) {
      | value => Some(value)
      | exception Not_found => None
      };
    }
  );
};

let removeItem = (key, {filename}) => {
  readFromFile(filename)
  >|= (
    hashtbl => {
      Hashtbl.remove(hashtbl, key);
      writeToFile(filename, hashtbl);
    }
  );
};