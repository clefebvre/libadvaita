# Advaita

Building blocks for modern GNOME applications.

## License

Libadvaita is licensed under the LGPL-2.1+.

## Building

We use the Meson (and thereby Ninja) build system for libadvaita. The quickest
way to get going is to do the following:

```sh
meson . _build
ninja -C _build
ninja -C _build install
```

For build options see [meson_options.txt](./meson_options.txt). E.g. to enable documentation:

```sh
meson . _build -Dgtk_doc=true
ninja -C _build
```

## Usage

There's a C example:

```sh
_build/run _build/demo/advaita-1-demo
```

## Documentation

The documentation can be found online
[here](https://gnome.pages.gitlab.gnome.org/libadvaita/doc/).

## Getting in Touch

Matrix room: [#libadvaita:gnome.org](https://matrix.to/#/#libadvaita:gnome.org)
