## About

cutehttpd is simple http server based on Qt. It's perfect for situations, when you need to send something fast and without additional apps.

## Features

### Implemented features
* Listen music directly from browser
* View images directly from browser
* View text files directly from browser
* Source code highlight for text viewer
* Multithreading

### To be implemented features
* File uploading

## Supported Browsers:
Any browser higher than IE 8 is welcome. IE 8 has very basic support now (file downloading and directory navigation works fine)

## Libs used
* [highlight.js](https://github.com/isagalaev/highlight.js)
* [addEventListener-polyfill.js](https://gist.github.com/eirikbacker/2864711/946225eb3822c203e8d6218095d888aac5e1748e)

## Compile

    git clone https://github.com/Solant/cutehttpd.git
    cd cutehttpd
    qmake
    make
