fs = import('fs')

stylesheet_deps = []

yaru_accent_colors_sassc = []

if get_option('yaru-accent-colors')
  YARU_ACCENTS = [
      'default',
      'bark',
      'sage',
      'olive',
      'viridian',
      'prussiangreen',
      'blue',
      'purple',
      'magenta',
      'red',
  ]

  yaru_accent_colors_sassc += configure_file(
    command: [
      'sh', '-c',
        ';'.join([
          'echo "\$is_yaru: true;"',
          'sed s,palette,palette-yaru,g "$1"',
        ]), '--', '@INPUT@',
    ],
    capture: true,
    input: 'base.scss',
    output: 'base-yaru.scss',
  )

  yaru_accent_colors = 'yaru_accent_colors.scss'
  foreach accent: YARU_ACCENTS
    foreach variant: ['light', 'dark']
      yaru_accent_colors_sassc += configure_file(
        configuration: {
          'yaru_dark_variant': variant == 'dark' ? 'true' : 'false',
          'yaru_accent_color': accent,
          'yaru_theme_entry_point': (meson.project_source_root() /
            '@0@'.format(files('defaults-@0@.scss'.format(variant))[0])),
        },
        input: yaru_accent_colors,
        output: 'defaults-@0@-yaru-@1@.scss'.format(variant, accent),
      )
    endforeach
  endforeach
endif

build_yaru_accent_colors = yaru_accent_colors_sassc.length() > 0

# For git checkouts, but not for tarballs...
if not fs.exists('base.css') or build_yaru_accent_colors
  sassc = find_program('sassc', required: false)
  if not sassc.found()
    subproject('sassc', default_options: ['warning_level=0', 'werror=false'])
    sassc = find_program('sassc')
  endif

  if build_yaru_accent_colors
    assert(sassc.found(), 'No SSSC found, needed for accent colors!')
  endif

  if sassc.found()
    sassc_opts = [ '-a', '-M', '-t', 'compact' ]

    scss_deps = files([
      '_colors.scss',
      '_common.scss',
      '_compat-colors.scss',
      '_defaults.scss',
      '_drawing.scss',
      '_functions.scss',
      '_widgets.scss',

      'widgets/_avatar.scss',
      'widgets/_bottom-sheet.scss',
      'widgets/_buttons.scss',
      'widgets/_calendar.scss',
      'widgets/_checks.scss',
      'widgets/_color-chooser.scss',
      'widgets/_column-view.scss',
      'widgets/_deprecated.scss',
      'widgets/_dialogs.scss',
      'widgets/_dropdowns.scss',
      'widgets/_emoji-chooser.scss',
      'widgets/_entries.scss',
      'widgets/_expanders.scss',
      'widgets/_file-chooser.scss',
      'widgets/_header-bar.scss',
      'widgets/_labels.scss',
      'widgets/_level-bar.scss',
      'widgets/_linked.scss',
      'widgets/_links.scss',
      'widgets/_lists.scss',
      'widgets/_menus.scss',
      'widgets/_message-dialog.scss',
      'widgets/_misc.scss',
      'widgets/_notebook.scss',
      'widgets/_paned.scss',
      'widgets/_popovers.scss',
      'widgets/_preferences.scss',
      'widgets/_progress-bar.scss',
      'widgets/_scale.scss',
      'widgets/_scrolling.scss',
      'widgets/_shortcuts-window.scss',
      'widgets/_sidebars.scss',
      'widgets/_spinner.scss',
      'widgets/_spin-button.scss',
      'widgets/_switch.scss',
      'widgets/_tab-view.scss',
      'widgets/_text-selection.scss',
      'widgets/_toolbars.scss',
      'widgets/_tooltip.scss',
      'widgets/_views.scss',
      'widgets/_view-switcher.scss',
      'widgets/_window.scss',
    ])

    scss_files = [
      'base',
      'base-hc',
      'defaults-light',
      'defaults-dark',
    ]

    if build_yaru_accent_colors
      foreach accent_definition: yaru_accent_colors_sassc
        scss_deps += accent_definition
        scss_files += accent_definition
      endforeach

      scss_deps += yaru_accent_colors
      sassc_opts += [ '-I', meson.project_build_root() ]
      sassc_opts += [ '-I', meson.current_source_dir() ]
    endif

    foreach scss: scss_files
      stylesheet_deps += custom_target('@0@.scss'.format(fs.name(scss)),
        input: '@0@'.format(scss).endswith('.scss') ? scss : '@0@.scss'.format(scss),
        output: '@0@.css'.format(fs.stem(scss)),
        command: [
          sassc, sassc_opts, '@INPUT@', '@OUTPUT@',
        ],
        depend_files: scss_deps,
      )
    endforeach
  endif
endif

accents_css = []
foreach accent_definition: yaru_accent_colors_sassc
  accents_css += '<file alias="@0@">@1@/@2@</file>'.format(
    fs.stem(accent_definition) + '.css', meson.project_build_root(),
    fs.replace_suffix(accent_definition, '.css'))
endforeach

gresource_file = configure_file(
  input: 'advaita-stylesheet.gresources.xml',
  output: '@BASENAME@',
  configuration: {
    'ACCENTS_CSS': accents_css.length() > 0 ? '\n'.join(accents_css) : '',
  }
)

libadvaita_stylesheet_resources = gnome.compile_resources(
  'advaita-stylesheet-resources',
  gresource_file,

  source_dir: [
    # List in order of preference
    meson.current_build_dir(),
    meson.current_source_dir(),
  ],
  dependencies: stylesheet_deps,
  c_name: 'adw_stylesheet',
)
