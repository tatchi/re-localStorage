open TestFramework;
open Library;

describe("LocalStorage", ({test, _}) => {
  let storage = Library.LocalStorage.create("test");
  test("add/get item", ({expect}) => {
    Lwt_main.run(
      {
        let%lwt _ = Library.LocalStorage.setItem("myKey", "value", storage);
        let%lwt maybeValue = Library.LocalStorage.getItem("myKey", storage);
        expect.option(maybeValue).toBe(Some("value"));
        Lwt.return();
      },
    )
  });
  test("remove item", ({expect}) => {
    Lwt_main.run(
      {
        let%lwt _ = Library.LocalStorage.removeItem("myKey", storage);
        let%lwt maybeValue = Library.LocalStorage.getItem("myKey", storage);
        expect.option(maybeValue).toBe(None);
        Lwt.return();
      },
    )
  });
});