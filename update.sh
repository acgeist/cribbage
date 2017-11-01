#!/bin/sh
git add .
git commit -m "automated commit $(date +Y%m%d)"
git push origin master

