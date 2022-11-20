# Filament Release Guide

- $VERSION = the current version that has been released (e.g. 1.10.7)
- $NEXT_VERSION = the next version we plan to release (e.g. 1.10.8)
- $PATCH_VERSION = the minor version on top of filament version (e.g. 1.10.7-__p0__)

## Release a new filament version for olympus

### 1. keep track of our changes in the current release

- compare the current olympus release branch `elisemorysc/filament:olympus-$VERSION` with the upstream filament release `google/filament:v$VERSION` (e.g. https://github.com/google/filament/compare/v1.10.7...elisemorysc:olympus-1.10.7)
- we should see the hunterization commit marked `[Hunter]`
- we should see the olympus changes marked `[Olympus]`

### 2. create new release branch

- create a new branch `elisemorysc/filament:olympus-$NEXT_VERSION` from the upstream filament version (e.g. `google/filament:v1.10.8` -> `elisemorysc/filament:olympus-1.10.8`)
- cherry pick in hunter and olympus changes from the last step
- solve any conflicts

### 3. cut new release

- cut a new release `olympus-$NEXT_VERSION-$PATH_VERSION` (e.g. `olympus-1.10.8-p0`) from the new branch

## Release a new filament version for hunter

- create a new branch `elisemorysc/filament:hunter-$NEXT_VERSION` from the upstream filament version (e.g. `google/filament:v1.10.8` -> `elisemorysc/filament:hunter-1.10.8`)
- cherry pick in the hunterization commit marked `[Hunter]` from the current olympus release `elisemorysc/filament:olympus-$VERSION`
- solve any conflicts
- put up a PR against the hunter repo for filament `cpp-pm/filament:hunter-$NEXT_VERSION`