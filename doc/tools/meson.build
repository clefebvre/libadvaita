screenshot_resources = gnome.compile_resources(
   'screenshot-resources',
   'screenshot.gresources.xml',

   c_name: 'adw',
)

screenshot_sources = [
  screenshot_resources,
  'screenshot.c',
  libadvaita_generated_headers,
]

screenshot = executable('screenshot'.format(apiversion),
  screenshot_sources,
  dependencies: libadvaita_deps + [libadvaita_dep],
)
