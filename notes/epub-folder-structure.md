manga.epub  (a zip file, but with one special rule below)
├── mimetype                      <- must be first, must be STORED not compressed
├── META-INF/
│   └── container.xml             <- where the "package" file is
└── OEBPS/
    ├── content.opf               <- manifest: lists every file + reading order
    ├── nav.xhtml                 <- table of contents (epub3)
    ├── images/
    │   ├── page001.jpg
    │   ├── page002.jpg
    │   └── ...
    └── text/
        ├── page001.xhtml         <- one tiny html wrapper per image
        ├── page002.xhtml
        └── ...