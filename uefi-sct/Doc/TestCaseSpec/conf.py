# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Self Certification Test (SCT) II'
copyright = '2024, Prachotan Bathi'
author = 'Prachotan Bathi'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["myst_parser","sphinx_rtd_theme","sphinx.ext.autosectionlabel"]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_book_theme'
html_static_path = ['_static']
html_css_files = [
    'custom.css',
]

html_js_files = [
    'custom.js',
]

html_logo="https://upload.wikimedia.org/wikipedia/commons/8/89/Logo_of_the_UEFI_Forum.svg"
# html_theme_options = {
#     "collapse_navigation": "true",
#     "max_navbar_depth": 2,
#     "show_navbar_depth": 2,
    
# }

html_title = "Self Certification Test (SCT) II"