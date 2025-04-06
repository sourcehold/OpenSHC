project = 'OpenSHC'
author = 'Sourcehold Team'
release = '0.1'

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
]

html_theme = 'furo'

html_title = 'OpenSHC Documentation'
html_logo = '_static/openshc-logo-01.png'
html_static_path = ['_static']
html_theme_options = {
    "footer_icons": [
        {
            "name": "GitHub",
            "url": "https://github.com/sourcehold/OpenSHC",
            "html": """
                <svg stroke="currentColor" fill="currentColor" stroke-width="0" viewBox="0 0 1024 1024" height="1.25em" width="1.25em" xmlns="http://www.w3.org/2000/svg">
                    <path d="M511.6 76.3C264.6 76.3 64 277.5 64 524.8c0 197.7 128.5 365.4 306.7 424.8 22.4 4.2 30.5-9.7 30.5-21.5 0-10.7-.4-46-0.6-83.6-124.8 27.2-151.2-53.6-151.2-53.6-20.4-52-49.9-65.8-49.9-65.8-40.8-27.8 3-27.2 3-27.2 45.2 3.2 69 46.5 69 46.5 40.1 68.8 105.2 48.9 130.8 37.4 4-29.1 15.7-48.9 28.5-60.2-99.6-11.3-204.4-49.8-204.4-221.6 0-48.9 17.4-88.9 45.8-120.2-4.6-11.3-19.9-56.8 4.3-118.4 0 0 37.5-12 123 45.8 35.7-9.9 74-14.9 112.1-15.1 38 .2 76.4 5.2 112.1 15.1 85.4-57.8 122.8-45.8 122.8-45.8 24.4 61.6 9 107.1 4.4 118.4 28.5 31.3 45.8 71.3 45.8 120.2 0 172.4-105.1 210-204.9 221.2 16.2 14 30.5 41.6 30.5 83.8 0 60.4-0.5 109-0.5 123.8 0 11.9 8 25.9 30.7 21.5C831.6 890 960 722.3 960 524.8 960 277.5 759.6 76.3 511.6 76.3z"></path>
                </svg>
            """,
            "class": "",
        },
    ],
    "source_repository": "https://github.com/sourcehold/OpenSHC/",
    "source_branch": "main",
    "source_directory": "docs/",
}

html_context = {
    "copyright": "Copyright 2025 OpenSHC",
}

templates_path = ['_templates']
exclude_patterns = []
