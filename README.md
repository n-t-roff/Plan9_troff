This is the troff version of Plan 9 ported to UNIX (tested on OpenBSD, NetBSD and Linux amd64).
To keep the code changes to a minimum parts of Plan 9 libraries (mainly libc) had also been portet.

The repository can be downloaded with the "Download ZIP" button or with
```bash
git clone https://github.com/n-t-roff/Plan9_troff.git
```
Installation paths are set up in the `Makefile`.
The Software is then build with `make` and installed with `make install`.
Generated files are removed with `make clean`.
The repository is kept up-to-date with `git pull`.

If there are any problems please report them to the [issue tracker](https://github.com/n-t-roff/Plan9_troff/issues)
or send a mail to &lt;troff at arcor dot de&gt;.
