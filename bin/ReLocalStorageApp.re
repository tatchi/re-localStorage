Lwt_main.run(
  {
    let storage = Library.LocalStorage.create("test");
    // Lwt.Infix.(Library.LocalStorage.write("myKey", "coucou"));
    Lwt.Infix.(
      Library.LocalStorage.setItem("myKey", "the value new", storage)
      >>= (
        _ => {
          Library.LocalStorage.getItem("myKey", storage)
          >|= (
            res => {
              Console.log(
                switch (res) {
                | None => "Value not found"
                | Some(v) => v
                },
              );
            }
          );
        }
      )
    );
  },
);