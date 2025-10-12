# pawn-plus-timer

Credits:
XCore/Zxuan
Improve code from: 4sheed (part: PPTasks_(Start/Stop)PlayerTasks)

English: (Translate)
To be honest, I have made a timer for global/player, but it still uses a lot of native samples.
So now I use 4sheed's code for the player part.

NOTE: this doesn't work with arrays. just bool/int/float

Indonesian: 
Sejujurnya saya telah membuat timer untuk global/player, tapi masih mengunakan banyak native samp.
Jadi sekarang saya mengunakan kode milik 4sheed untuk bagian player nya.

CATATAN: ini belum bisa mengunakan array. hanya bool/int/float

## Installation
Include in your code and begin using the library:

```pawn
#include <Timer.inc>
```

## Usage

### Tasks

use `task` for an automatic timer

```pawn

task Name[1000]() 
{
    // code
}
```
> [!WARNING]
> Tasks can only take `playerid` for `ptask`. Adding any other parameters will cause compiler errors because the system runs them automatically and cannot handle extra arguments.

### Player Tasks

Use the `ptask` macro to define player-specific tasks. These run at the specified interval for each connected player.

```pawn
#include <pp-tasks>

ptask PlayerTaskName[interval](playerid)
{
    // This task executes for each connected player every <interval> milliseconds.
}
```
## Thanks to
- [4sheed](//github.com/r4sheed) - for the player code section that improves (//github.com/r4sheed/pawn-plus-tasks)
- [IllidanS4](//github.com/IllidanS4) — for creating [PawnPlus](//github.com/IS4Code/PawnPlus), the core library behind this include.
