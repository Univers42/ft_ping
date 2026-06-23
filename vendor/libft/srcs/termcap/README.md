# Termcap Library

## What is Termcap?

**Termcap** (short for "terminal capability") is a software library and database that provides a uniform interface for programs to interact with a wide variety of text terminals. It allows applications to use terminal features (such as cursor movement, screen clearing, color, and more) in a device-independent way.

Termcap originated in early UNIX systems and was later superseded by the more feature-rich [terminfo](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/tic.html) system, but termcap remains widely supported for compatibility.

- **Official POSIX reference:**  
  [The Open Group Base Specifications Issue 7, IEEE Std 1003.1-2017, Section 13.2 Termcap Functions](https://pubs.opengroup.org/onlinepubs/9699919799/functions/tgetent.html)
- **Historical documentation:**  
  [BSD termcap(5) man page](https://man.openbsd.org/termcap.5)  
  [GNU termcap manual](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)

## Purpose of Termcap in Shells

In the ctx of a shell (like `sh`, `bash`, or your own shell project), **termcap** is used to provide advanced, portable terminal interaction features. This includes:

- Moving the cursor to arbitrary positions (for line editing, prompts, etc.)
- Clearing the screen or parts of it
- Handling insert/delete line/character operations
- Supporting features like bold, underline, standout mode, etc.
- Adapting to any terminal type specified by the user’s `TERM` environment variable

**Why is this important?**  
Shells are interactive programs that must work on many different terminal types, each with its own control sequences. Hardcoding escape sequences would break portability. Termcap allows the shell to query the correct sequences at runtime, ensuring compatibility and a better user experience.

**Typical shell use cases:**

- Command-line editing (moving the cursor left/right, clearing lines)
- Displaying prompts with colors or special effects
- Implementing features like reverse search, history navigation, or screen redraws
## Core terminal behaviors we want to recreate
### Cursor movement
When the user edits a command, our shell has to move the cursor left/right, jump to the start/end, etc.
termcapt provided escape sequences like:
- move cursor left
- move cursor right
- move cursor to a given row/col
- save/restore cursor position

### Clearing parts of the screen
Interactive mode in shell need to clean up the screen elegantly:
- Clear entier screen 
- Clear from cursor to end of line
- Clear from cursor to end of screen

Used for things like:
- redrawing the prompt
- implementing `Ctrl + L`
- updating completions menus

### Terminal size detection
our shell mst know the terminal width to wrap line correctly
termcap has entries for number of columns/rows.

### Key sequence decoding
old terminal like the one of ash or dash sent weird escapes sequences.
Modern shells still decode sequences for:
- left arrow
- Right arrow
- up arrow (history)
- down arrow
- Home/end/delete
- ctrl-key combos

termcap is just a way to map sequences that are unreadable to value that behaves of somes way..
### Bold/color mode togglses
if we want a nice modern shell:
- enter bold mode
- exit bold mode
- enter color mode
- reset all attributes

Termcap stored theses as capabilities like `md`(bold) and `me`(reset)
### Line editing awarenes
Not exactly a capability, but termcap-style care:

don’t break the screen when line wraps

redraw the prompt + current line cleanly

handle resizing

handle multi-line input smoothly

This is basically what readline does internally.
## How Does Termcap Work?

- The **termcap database** is a text file (traditionally `/etc/termcap`) containing entries for many terminal types.
- Each entry describes the terminal's capabilities using a compact syntax:
  - **Boolean**: e.g. `am` (automatic margins)
  - **Numeric**: e.g. `co#80` (80 columns)
  - **String**: e.g. `cl=\E[H\E[2J` (clear screen sequence)
- Applications use the **termcap library** to:
  1. Load the entry for the current terminal type (usually from the `TERM` environment variable).
  2. Query capabilities by name.
  3. Output the appropriate control sequences for the terminal.

## Example: A Termcap Entry

For `xterm-256color`:
