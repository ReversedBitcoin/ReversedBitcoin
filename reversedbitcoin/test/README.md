# Unit tests

The sources in this directory are unit test cases. Boost includes a
unit testing framework, and since Bitcoin Core already uses Boost, it makes
sense to simply use this framework rather than require developers to
configure some other framework (we want as few impediments to creating
unit tests as possible).

The build system is set up to compile an executable called `test_reversedbitcoin`
that runs all of the unit tests. The main source file is called
`setup_common.cpp`.

### Compiling/running unit tests

Unit tests will be automatically compiled if dependencies were met in `./configure`
and tests weren't explicitly disabled.

After configuring, they can be run with `make check`.

To run reversedbitcoind tests manually, launch `reversedbitcoin/test/test_reversedbitcoin`. To recompile
after a test file was modified, run `make` and then run the test again. If you
modify a non-test file, use `make -C reversedbitcoin/test` to recompile only what's needed
to run reversedbitcoind tests.

To add more reversedbitcoind tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the `test/` directory or add new .cpp files that
implement new `BOOST_AUTO_TEST_SUITE` sections.

To run ReversedBitcoin-qt tests manually, launch `reversedbitcoin/qt/test/test_reversedbitcoin-qt`

To add more reversedbitcoin-qt tests, add them to the `reversedbitcoin/qt/test/` directory and
the `reversedbitcoin/qt/test/test_main.cpp` file.

### Running individual tests

test_reversedbitcoin has some built-in command-line arguments; for
example, to run just the getarg_tests verbosely:

    test_reversedbitcoin --log_level=all --run_test=getarg_tests

... or to run just the doubledash test:

    test_reversedbitcoin --run_test=getarg_tests/doubledash

Run `test_reversedbitcoin --help` for the full list.

### Adding test cases

To add a new unit test file to our test suite you need
to add the file to `reversedbitcoin/Makefile.test.include`. The pattern is to create
one test file for each class or source file for which you want to create
unit tests. The file naming convention is `<source_filename>_tests.cpp`
and such files should wrap their tests in a test suite
called `<source_filename>_tests`. For an example of this pattern,
see `uint256_tests.cpp`.

### Logging and debugging in unit tests

To write to logs from unit tests you need to use specific message methods
provided by Boost. The simplest is `BOOST_TEST_MESSAGE`.

For debugging you can launch the test_reversedbitcoin executable with `gdb`or `lldb` and
start debugging, just like you would with reversedbitcoind:

```bash
gdb reversedbitcoin/test/test_reversedbitcoin
```