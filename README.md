## Usage

`ccfake` is a fake framework for developer testing under c++.

```sh
$ chmod a+x ./ccup.sh

# start project from docker env
# make sure docker is pre-installed on the system.
./ccup.sh -e

# update depends and execute cmake generating
./ccup.sh -u

# build
./ccup.sh -b

# update & build
./ccup.sh -ub

# run tests
./ccup.sh -t

# build & test
./ccup.sh -bt

# update & build & test
./ccup.sh -ubt

# run executable
./ccup.sh -r

# install
./ccup.sh -i

# build & install
./ccup.sh -bi

# update & build & install
./ccup.sh -ubi

# clean build
./ccup.sh -c

# clean all
./ccup.sh -C

# help
./ccup.sh -h
```

## TODO

- [x]: remove node type ?
- [x]: refact interface and macro
- [ ]: test example
- [ ]: lifecycle, right reference?
- [ ]: visitor
- [ ]: dump
- [ ]: activate
- [ ]: manager
- [ ]: fake system