This folder contains lint scripts.

check-doc.py
============
Check for missing documentation of command line options.

commit-script-check.sh
======================
Verification of [scripted diffs](/doc/developer-notes.md#scripted-diffs).

git-subtree-check.sh
====================
Run this script from the root of the repository to verify that a subtree matches the contents of
the commit it claims to have been updated to.

To use, make sure that you have fetched the upstream repository branch in which the subtree is
maintained:
* for `reversedbitcoin/secp256k1`: https://github.com/bitcoin-core/secp256k1.git (branch master)
* for `reversedbitcoin/leveldb`: https://github.com/bitcoin-core/leveldb.git (branch bitcoin-fork)
* for `reversedbitcoin/univalue`: https://github.com/bitcoin-core/univalue.git (branch master)
* for `reversedbitcoin/crypto/ctaes`: https://github.com/bitcoin-core/ctaes.git (branch master)

Usage: `git-subtree-check.sh DIR (COMMIT)`

`COMMIT` may be omitted, in which case `HEAD` is used.

lint-all.sh
===========
Calls other scripts with the `lint-` prefix.
