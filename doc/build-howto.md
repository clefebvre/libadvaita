Title: Compiling with Libadvaita
Slug: building

# Compiling with Libadvaita

If you need to build Libadvaita, get the source from
[here](https://gitlab.gnome.org/GNOME/libadvaita/) and see the `README.md` file.

## Using `pkg-config`

Like other GNOME libraries, Libadvaita uses `pkg-config` to provide compiler
options. The package name is `libadvaita-1`.

When using the Meson build system you can declare a dependency like:

```meson
dependency('libadvaita-1')
```

The `1` in the package name is the "API version" (indicating "the version of the
Libadvaita API that first appeared in version 1") and is essentially just part
of the package name.

## Bundling the Library

### Using Flatpak

If you're using the GNOME SDK of the version 42 or later, Libadvaita is already
included and there's no need to do anything.

If you're using an older version or a different SDK, add the following modules
to your manifest:

```json
{
    "name" : "libadvaita",
    "buildsystem" : "meson",
    "config-opts" : [
        "-Dexamples=false",
        "-Dtests=false"
    ],
    "sources" : [
        {
            "type" : "git",
            "url" : "https://gitlab.gnome.org/GNOME/libadvaita.git",
            "branch" : "main"
        }
    ],
    "modules" : [
        {
            "name" : "libsass",
            "buildsystem" : "meson",
            "cleanup" : [
                "*"
            ],
            "sources" : [
                {
                    "type" : "git",
                    "url" : "https://github.com/lazka/libsass.git",
                    "branch" : "meson"
                }
            ]
        },
        {
            "name" : "sassc",
            "buildsystem" : "meson",
            "cleanup" : [
                "*"
            ],
            "sources" : [
                {
                    "type" : "git",
                    "url" : "https://github.com/lazka/sassc.git",
                    "branch" : "meson"
                }
            ]
        }
    ]
}
```

### Using a Subproject

If you're not using Flatpak, Libadvaita can be used as a Meson subproject.
Create a `subprojects/libadvaita.wrap` file with the following contents:

```ini
[wrap-git]
directory=libadvaita
url=https://gitlab.gnome.org/GNOME/libadvaita.git
revision=main
depth=1
```

Add this to your `meson.build`:

```meson
libadvaita = dependency(
  'libadvaita-1',
  version: '>= 1.0.0',
  fallback: ['libadvaita', 'libadvaita_dep'],
  default_options: [
    'examples=false',
    'introspection=disabled',
    'tests=false',
    'vapi=false',
  ]
)
```

Then the `libadvaita` variable can be used as a dependency.

## Building on macOS

To build on macOS you need to install the build-dependencies first. This can
e.g. be done via [`brew`](https://brew.sh):

```bash
brew install pkg-config gtk4 meson gobject-introspection vala
```

After running the command above, one may now build the library:

```bash
git clone https://gitlab.gnome.org/GNOME/libadvaita.git
cd libadvaita
meson _build
ninja -C _build
ninja -C _build install
```

Working with the library on macOS is pretty much the same as on Linux. To link
it, use `pkg-config`:

```bash
gcc $(pkg-config --cflags --libs gtk4) $(pkg-config --cflags --libs libadvaita-1) main.c -o main
```

# Next Steps

Once libadvaita has been compiled and included into your project, it needs to be
initialized. See [Initialization](initialization.html).
