#!/bin/bash
rm -rf ./EspException* && wget https://github.com/me-no-dev/EspExceptionDecoder/releases/download/1.1.0/EspExceptionDecoder-1.1.0.zip -O espexp.zip && unzip  espexp.zip && mv ./EspExceptionDecoder/**/*.jar ./bin/ && rm decode && ln -s ./bin/EspExceptionDecoder.jar decode
