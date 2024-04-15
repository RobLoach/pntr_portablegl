# pntr_portablegl

Use OpenGL 3-ish with [PortableGL](https://github.com/rswinkle/PortableGL) in [pntr](https://github.com/robloach/pntr).

## Example

[![Example 2 Screenshot](examples/ex2.png)](examples/ex2.c)

## API

``` c
glContext* pntr_load_glContext(pntr_image* dst);
void pntr_unload_glContext(glContext* context);
```

See [PortableGL](https://github.com/rswinkle/PortableGL) for how to use the `glContext`.

## License

Unless stated otherwise, all works are:

- Copyright (c) 2024 [Rob Loach](https://robloach.net)

... and licensed under:

- [MIT License](LICENSE)
