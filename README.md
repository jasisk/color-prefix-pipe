% PRECOLOR(1) Version 1.0.0 | Colorize terminal output prefixes

NAME
====

**precolor** — pipe stdin to stdout, colorizing the first field separated by delimiter (tab by default)

SYNOPSIS
========

| **precolor** \[**-d** _delimiter_]

DESCRIPTION
===========

Pipes **stdin** to **stdout**, but adds a color to each unique line-prefix. Useful to quickly visualize related entries in a sea of output such as that from **parallel --tag**.

Options
-------

-d

:   Specify a delimiter (default is "\\t").

		The delimiter must be a single character.

EXAMPLES
========

```
$ seq 1 9 | parallel -j1 'printf "%d\t%d\n" $(({} % 3)) {}' | precolor
[red]1[/red]         1
[green]2[/green]     2
[yellow]3[/yellow]   3
[red]1[/red]         4
[green]2[/green]     5
[yellow]3[/yellow]   6
[red]1[/red]         7
[green]2[/green]     8
[yellow]3[/yellow]   9
```

BUGS
====

See GitHub Issues: <https://github.com/jasisk/precolor/issues>

AUTHOR
======

jasisk@gmail.com <jasisk@gmail.com>

LICENSE
=======

Copyright (C) 2018 Jean-Charles Sisk. MIT licensed.
