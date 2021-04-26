#!/bin/bash

rm -rf ./EspException* && wget https://github.com/littleyoda/EspStrackTraceDecoder/releases/latest/download/EspStackTraceDecoder.jar && mv ./EspStackTraceDecoder.jar ./bin/ && ln -fs ./bin/EspStackTraceDecoder.jar decode
