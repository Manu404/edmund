#!/bin/bash

cd ../../

bash ./gollum.sh install:gollum

gollum install:devenv

gollum init

cd scripts/env/
