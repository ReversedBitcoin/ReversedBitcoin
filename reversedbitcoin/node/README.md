# reversedbitcoin/node/

The [`reversedbitcoin/node/`](./) directory contains code that needs to access node state
(state in `CChain`, `CBlockIndex`, `CCoinsView`, `CTxMemPool`, and similar
classes).

Code in [`reversedbitcoin/node/`](./) is meant to be segregated from code in
[`reversedbitcoin/wallet/`](../wallet/) and [`reversedbitcoin/qt/`](../qt/), to ensure wallet and GUI
code changes don't interfere with node operation, to allow wallet and GUI code
to run in separate processes, and to perhaps eventually allow wallet and GUI
code to be maintained in separate source repositories.

As a rule of thumb, code in one of the [`reversedbitcoin/node/`](./),
[`reversedbitcoin/wallet/`](../wallet/), or [`reversedbitcoin/qt/`](../qt/) directories should avoid
calling code in the other directories directly, and only invoke it indirectly
through the more limited [`reversedbitcoin/interfaces/`](../interfaces/) classes.

The [`reversedbitcoin/node/`](./) directory is a new directory introduced in
[#14978](https://github.com/bitcoin/bitcoin/pull/14978) and at the moment is
sparsely populated. Eventually more substantial files like
[`reversedbitcoin/reversedblockchain.cpp`](../reversedblockchain.cpp) and
[`reversedbitcoin/txmempool.cpp`](../txmempool.cpp) might be moved there.
