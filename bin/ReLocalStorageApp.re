let storage = Library.LocalStorage.load("sync.bin");

Console.log(
  switch (Library.LocalStorage.getItem("myKey", storage)) {
  | None => "None"
  | Some(v) => v
  },
);

Library.LocalStorage.setItem("myKey", "value", storage);

Console.log(
  switch (Library.LocalStorage.getItem("myKey", storage)) {
  | None => "None"
  | Some(v) => v
  },
);

Library.LocalStorage.persist(storage);

Console.log(
  switch (Library.LocalStorage.getItem("myKey", storage)) {
  | None => "None"
  | Some(v) => v
  },
);